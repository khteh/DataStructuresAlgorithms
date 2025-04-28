#pragma once
/*
* PCG Random Number Generation for C++
*
* Copyright 2014-2017 Melissa O'Neill <oneill@pcg-random.org>,
*                     and the PCG Project contributors.
*
* SPDX-License-Identifier: (Apache-2.0 OR MIT)
*
* Licensed under the Apache License, Version 2.0 (provided in
* LICENSE-APACHE.txt and at http://www.apache.org/licenses/LICENSE-2.0)
* or under the MIT license (provided in LICENSE-MIT.txt and at
* http://opensource.org/licenses/MIT), at your option. This file may not
* be copied, modified, or distributed except according to those terms.
*
* Distributed on an "AS IS" BASIS, WITHOUT WARRANTY OF ANY KIND, either
* express or implied.  See your chosen license for details.
*
* For additional information about the PCG random number generation scheme,
* visit http://www.pcg-random.org/.
*/

/*
* This file provides support code that is useful for random-number generation
* but not specific to the PCG generation scheme, including:
*      - 128-bit int support for platforms where it isn't available natively
*      - bit twiddling operations
*      - I/O of 128-bit and 8-bit integers
*      - Handling the evilness of SeedSeq
*      - Support for efficiently producing random numbers less than a given
*        bound
*/

/*
 * Abstractions for compiler-specific directives
 */

 #ifdef __GNUC__
 #define PCG_NOINLINE __attribute__((noinline))
#else
 #define PCG_NOINLINE
#endif

#ifdef _MSC_VER
#define PCG_ALWAYS_INLINE __forceinline
#elif __GNUC__
#define PCG_ALWAYS_INLINE __attribute__((always_inline))
#else
#define PCG_ALWAYS_INLINE inline
#endif


/*
* Some members of the PCG library use 128-bit math.  When compiling on 64-bit
* platforms, both GCC and Clang provide 128-bit integer types that are ideal
* for the job.
*
* On 32-bit platforms (or with other compilers), we fall back to a C++
* class that provides 128-bit unsigned integers instead.  It may seem
* like we're reinventing the wheel here, because libraries already exist
* that support large integers, but most existing libraries provide a very
* generic multiprecision code, but here we're operating at a fixed size.
* Also, most other libraries are fairly heavyweight.  So we use a direct
* implementation.  Sadly, it's much slower than hand-coded assembly or
* direct CPU support.
*
*/
#if __SIZEOF_INT128__ && !PCG_FORCE_EMULATED_128BIT_MATH
namespace pcg_extras {
     using  pcg128_t = __uint128_t;
 }
 #define PCG_128BIT_CONSTANT(high,low) \
         ((pcg_extras::pcg128_t(high) << 64) + (low))
#elif __has_include(<__msvc_int128.hpp>)
 #include <__msvc_int128.hpp>
 namespace pcg_extras {
     using pcg128_t = std::_Unsigned128;
 }
 #define PCG_128BIT_CONSTANT(high,low) \
         pcg_extras::pcg128_t(low, high)
#else
 #include "pcg_uint128.hpp"
 #define PCG_128BIT_CONSTANT(high,low) \
         pcg_extras::pcg128_t(high,low)
 #define PCG_EMULATED_128BIT_MATH 1
#endif

#include <type_traits>
#include <iterator>

namespace pcg_extras {

/*
 * We often need to represent a "number of bits".  When used normally, these
 * numbers are never greater than 128, so an unsigned char is plenty.
 * If you're using a nonstandard generator of a larger size, you can set
 * PCG_BITCOUNT_T to have it define it as a larger size.  (Some compilers
 * might produce faster code if you set it to an unsigned int.)
 */

#ifndef PCG_BITCOUNT_T
    using bitcount_t = uint8_t;
#else
    using bitcount_t = PCG_BITCOUNT_T;
#endif

/*
 * Useful bitwise operations.
 */

/*
 * XorShifts are invertible, but they are something of a pain to invert.
 * This function backs them out.  It's used by the whacky "inside out"
 * generator defined later.
 */

 template <typename itype>
 constexpr itype unxorshift(itype x, bitcount_t bits, bitcount_t shift)
 {
     if (2*shift >= bits) {
         return x ^ (x >> shift);
     }
     itype lowmask1 = (itype(1U) << (bits - shift*2)) - 1;
     itype highmask1 = ~lowmask1;
     itype top1 = x;
     itype bottom1 = x & lowmask1;
     top1 ^= top1 >> shift;
     top1 &= highmask1;
     x = top1 | bottom1;
     itype lowmask2 = (itype(1U) << (bits - shift)) - 1;
     itype bottom2 = x & lowmask2;
     bottom2 = unxorshift(bottom2, bits - shift, shift);
     bottom2 &= lowmask1;
     return top1 | bottom2;
 }
 
 /*
  * Rotate left and right.
  *
  * In ideal world, compilers would spot idiomatic rotate code and convert it
  * to a rotate instruction.  Of course, opinions vary on what the correct
  * idiom is and how to spot it.  For clang, sometimes it generates better
  * (but still crappy) code if you define PCG_USE_ZEROCHECK_ROTATE_IDIOM.
  */
 
 template <typename itype>
 constexpr itype rotl(itype value, bitcount_t rot)
 {
     constexpr bitcount_t bits = sizeof(itype) * 8;
     constexpr bitcount_t mask = bits - 1;
 #if PCG_USE_ZEROCHECK_ROTATE_IDIOM
     return rot ? (value << rot) | (value >> (bits - rot)) : value;
 #else
     return (value << rot) | (value >> ((- rot) & mask));
 #endif
 }
 
 template <typename itype>
 constexpr itype rotr(itype value, bitcount_t rot)
 {
     constexpr bitcount_t bits = sizeof(itype) * 8;
     constexpr bitcount_t mask = bits - 1;
 #if PCG_USE_ZEROCHECK_ROTATE_IDIOM
     return rot ? (value >> rot) | (value << (bits - rot)) : value;
 #else
     return (value >> rot) | (value << ((- rot) & mask));
 #endif
 }
 
 /* Unfortunately, both Clang and GCC sometimes perform poorly when it comes
  * to properly recognizing idiomatic rotate code, so for we also provide
  * assembler directives (enabled with PCG_USE_INLINE_ASM).  Boo, hiss.
  * (I hope that these compilers get better so that this code can die.)
  *
  * These overloads will be preferred over the general template code above.
  */
 #if PCG_USE_INLINE_ASM && __GNUC__ && (__x86_64__  || __i386__)
 
 inline uint8_t rotr(uint8_t value, bitcount_t rot)
 {
     asm ("rorb   %%cl, %0" : "=r" (value) : "0" (value), "c" (rot));
     return value;
 }
 
 inline uint16_t rotr(uint16_t value, bitcount_t rot)
 {
     asm ("rorw   %%cl, %0" : "=r" (value) : "0" (value), "c" (rot));
     return value;
 }
 
 inline uint32_t rotr(uint32_t value, bitcount_t rot)
 {
     asm ("rorl   %%cl, %0" : "=r" (value) : "0" (value), "c" (rot));
     return value;
 }
 
 #if __x86_64__
 inline uint64_t rotr(uint64_t value, bitcount_t rot)
 {
     asm ("rorq   %%cl, %0" : "=r" (value) : "0" (value), "c" (rot));
     return value;
 }
 #endif // __x86_64__
 
 #elif defined(_MSC_VER)
   // Use MSVC++ bit rotation intrinsics
 
 #pragma intrinsic(_rotr, _rotr64, _rotr8, _rotr16)
 
 inline uint8_t rotr(uint8_t value, bitcount_t rot)
 {
     return _rotr8(value, rot);
 }
 
 inline uint16_t rotr(uint16_t value, bitcount_t rot)
 {
     return _rotr16(value, rot);
 }
 
 inline uint32_t rotr(uint32_t value, bitcount_t rot)
 {
     return _rotr(value, rot);
 }
 
 inline uint64_t rotr(uint64_t value, bitcount_t rot)
 {
     return _rotr64(value, rot);
 }
 
 #endif // PCG_USE_INLINE_ASM



/*
 * The C++ SeedSeq concept (modelled by seed_seq) can fill an array of
 * 32-bit integers with seed data, but sometimes we want to produce
 * larger or smaller integers.
 *
 * The following code handles this annoyance.
 *
 * uneven_copy will copy an array of 32-bit ints to an array of larger or
 * smaller ints (actually, the code is general it only needing forward
 * iterators).  The copy is identical to the one that would be performed if
 * we just did memcpy on a standard little-endian machine, but works
 * regardless of the endian of the machine (or the weirdness of the ints
 * involved).
 *
 * generate_to initializes an array of integers using a SeedSeq
 * object.  It is given the size as a static constant at compile time and
 * tries to avoid memory allocation.  If we're filling in 32-bit constants
 * we just do it directly.  If we need a separate buffer and it's small,
 * we allocate it on the stack.  Otherwise, we fall back to heap allocation.
 * Ugh.
 *
 * generate_one produces a single value of some integral type using a
 * SeedSeq object.
 */

 /* uneven_copy helper, case where destination ints are less than 32 bit. */

template<class SrcIter, class DestIter>
constexpr SrcIter uneven_copy_impl(
    SrcIter src_first, DestIter dest_first, DestIter dest_last,
    std::true_type)
{
    using src_t  = typename std::iterator_traits<SrcIter>::value_type;
    using dest_t = typename std::iterator_traits<DestIter>::value_type;

    constexpr bitcount_t SRC_SIZE  = sizeof(src_t);
    constexpr bitcount_t DEST_SIZE = sizeof(dest_t);
    constexpr bitcount_t DEST_BITS = DEST_SIZE * 8;
    constexpr bitcount_t SCALE     = SRC_SIZE / DEST_SIZE;

    size_t count = 0;
    src_t value = 0;

    while (dest_first != dest_last) {
        if ((count++ % SCALE) == 0)
            value = *src_first++;       // Get more bits
        else
            value >>= DEST_BITS;        // Move down bits

        *dest_first++ = dest_t(value);  // Truncates, ignores high bits.
    }
    return src_first;
}

 /* uneven_copy helper, case where destination ints are more than 32 bit. */

template<class SrcIter, class DestIter>
constexpr SrcIter uneven_copy_impl(
    SrcIter src_first, DestIter dest_first, DestIter dest_last,
    std::false_type)
{
    using src_t  = typename std::iterator_traits<SrcIter>::value_type;
    using dest_t = typename std::iterator_traits<DestIter>::value_type;

    constexpr auto SRC_SIZE  = sizeof(src_t);
    constexpr auto SRC_BITS  = SRC_SIZE * 8;
    constexpr auto DEST_SIZE = sizeof(dest_t);
    constexpr auto SCALE     = (DEST_SIZE+SRC_SIZE-1) / SRC_SIZE;

    while (dest_first != dest_last) {
        dest_t value(0UL);
        unsigned int shift = 0;

        for (size_t i = 0; i < SCALE; ++i) {
            value |= dest_t(*src_first++) << shift;
            shift += SRC_BITS;
        }

        *dest_first++ = value;
    }
    return src_first;
}

/* uneven_copy, call the right code for larger vs. smaller */

template<class SrcIter, class DestIter>
constexpr SrcIter uneven_copy(SrcIter src_first,
                           DestIter dest_first, DestIter dest_last)
{
    using src_t  = typename std::iterator_traits<SrcIter>::value_type;
    using dest_t = typename std::iterator_traits<DestIter>::value_type;

    constexpr bool DEST_IS_SMALLER = sizeof(dest_t) < sizeof(src_t);

    return uneven_copy_impl(src_first, dest_first, dest_last,
                            std::integral_constant<bool, DEST_IS_SMALLER>{});
}

/* generate_to, fill in a fixed-size array of integral type using a SeedSeq
 * (actually works for any random-access iterator)
 */

template <size_t size, typename SeedSeq, typename DestIter>
constexpr void generate_to_impl(SeedSeq&& generator, DestIter dest,
                             std::true_type)
{
    generator.generate(dest, dest+size);
}

template <size_t size, typename SeedSeq, typename DestIter>
constexpr void generate_to_impl(SeedSeq&& generator, DestIter dest,
                      std::false_type)
{
    using dest_t = typename std::iterator_traits<DestIter>::value_type;
    constexpr auto DEST_SIZE = sizeof(dest_t);
    constexpr auto GEN_SIZE  = sizeof(uint32_t);

    constexpr bool GEN_IS_SMALLER = GEN_SIZE < DEST_SIZE;
    constexpr size_t FROM_ELEMS =
        GEN_IS_SMALLER
            ? size * ((DEST_SIZE+GEN_SIZE-1) / GEN_SIZE)
            : (size + (GEN_SIZE / DEST_SIZE) - 1)
                / ((GEN_SIZE / DEST_SIZE) + GEN_IS_SMALLER);
                        //  this odd code ^^^^^^^^^^^^^^^^^ is work-around for
                        //  a bug: http://llvm.org/bugs/show_bug.cgi?id=21287

    if constexpr (FROM_ELEMS <= 1024) {
        uint32_t buffer[FROM_ELEMS];
        generator.generate(buffer, buffer+FROM_ELEMS);
        uneven_copy(buffer, dest, dest+size);
    } else {
        uint32_t* buffer = static_cast<uint32_t*>(malloc(GEN_SIZE * FROM_ELEMS));
        generator.generate(buffer, buffer+FROM_ELEMS);
        uneven_copy(buffer, dest, dest+size);
        free(static_cast<void*>(buffer));
    }
}

template <size_t size, typename SeedSeq, typename DestIter>
constexpr void generate_to(SeedSeq&& generator, DestIter dest)
{
    using dest_t = typename std::iterator_traits<DestIter>::value_type;
    constexpr bool IS_32BIT = sizeof(dest_t) == sizeof(uint32_t);

    generate_to_impl<size>(std::forward<SeedSeq>(generator), dest,
                           std::integral_constant<bool, IS_32BIT>{});
}

/* generate_one, produce a value of integral type using a SeedSeq
 * (optionally, we can have it produce more than one and pick which one
 * we want)
 */

template <typename UInt, size_t i = 0UL, size_t N = i + 1UL, typename SeedSeq>
constexpr UInt generate_one(SeedSeq&& generator)
{
    UInt result[N];
    generate_to<N>(std::forward<SeedSeq>(generator), result);
    return result[i];
}


template <typename RngType>
constexpr auto bounded_rand(RngType& rng, typename RngType::result_type upper_bound)
-> typename RngType::result_type
{
	using rtype = typename RngType::result_type;
	const rtype threshold = (RngType::max() - RngType::min() + rtype(1) - upper_bound)
		% upper_bound;
	for (;;) {
		const rtype r = rng() - RngType::min();
		if (r >= threshold)
			return r % upper_bound;
	}
}

}
