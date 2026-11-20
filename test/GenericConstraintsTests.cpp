#include "pch.h"
using namespace std;
// Concepts are checked at compile time: a failing static_assert stops the build. The TESTs only make them show up in the test report.
TEST(GenericConstraintsTests, WideIntegralTypeTest)
{
	// At least 64 bits, signed or unsigned
	static_assert(wide_integral_type<int64_t>);
	static_assert(wide_integral_type<uint64_t>);
	static_assert(wide_integral_type<long long>);
	static_assert(wide_integral_type<unsigned long long>);
	static_assert(wide_integral_type<int64_t const>); // cv-qualified too
	static_assert(wide_integral_type<long> == (sizeof(long) * CHAR_BIT >= 64)); // 64-bit on Linux, 32-bit on MSVC
	// Narrower integers, and anything that isn't an integer
	static_assert(!wide_integral_type<int>);
	static_assert(!wide_integral_type<int32_t>);
	static_assert(!wide_integral_type<uint32_t>);
	static_assert(!wide_integral_type<short>);
	static_assert(!wide_integral_type<char>);
	static_assert(!wide_integral_type<bool>);
	static_assert(!wide_integral_type<double>);
	static_assert(!wide_integral_type<string>);
	// Signed only
	static_assert(wide_signed_integral_type<int64_t>);
	static_assert(!wide_signed_integral_type<uint64_t>);
	static_assert(!wide_signed_integral_type<int32_t>);
#ifdef __SIZEOF_INT128__
	static_assert(wide_integral_type<int128_t>);
	static_assert(wide_integral_type<uint128_t>);
	static_assert(wide_signed_integral_type<int128_t>);
	static_assert(!wide_signed_integral_type<uint128_t>);
#endif
	SUCCEED();
}
TEST(GenericConstraintsTests, WidestIntegralTypeTest)
{
	// The aliases pick the widest integers the compiler offers, and the concept accepts exactly those widths
	static_assert(signed_integral_type<widest_signed_int>);
	static_assert(integral_type<widest_unsigned_int> && !signed_integral_type<widest_unsigned_int>);
	static_assert(sizeof(widest_signed_int) == sizeof(widest_unsigned_int));
	static_assert(widest_integral_bits == sizeof(widest_signed_int) * CHAR_BIT);
	static_assert(widest_integral_type<widest_signed_int>);
	static_assert(widest_integral_type<widest_unsigned_int>);
	static_assert(!widest_integral_type<int>);
#ifdef __SIZEOF_INT128__
	static_assert(same_as<widest_signed_int, int128_t> && same_as<widest_unsigned_int, uint128_t>);
	static_assert(widest_integral_bits == 128);
	static_assert(!widest_integral_type<int64_t>); // 64 bits isn't the widest when 128-bit integers exist
#else
	static_assert(same_as<widest_signed_int, int64_t> && same_as<widest_unsigned_int, uint64_t>);
	static_assert(widest_integral_bits == 64);
	static_assert(widest_integral_type<int64_t>);
#endif
	// The widest types hold more than 64-bit ones where 128-bit integers exist
	ASSERT_EQ((widest_unsigned_int)numeric_limits<uint64_t>::max() + 1 > numeric_limits<uint64_t>::max(), widest_integral_bits > 64);
}
