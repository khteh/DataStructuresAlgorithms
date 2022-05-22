#include "stdafx.h"
#include "MaxSubsetSumData.h"
MaxSubsetSumData::MaxSubsetSumData() 
{
	_index = 0;
	_value = 0;
}
MaxSubsetSumData::MaxSubsetSumData(size_t i, long v) 
{
	_index = i;
	_value = v;
}
long MaxSubsetSumData::Value() const { return _value; }
size_t MaxSubsetSumData::Index() const { return _index; }
bool MaxSubsetSumData::operator< (const MaxSubsetSumData& other) const {
	return _value < other.Value();
}
bool MaxSubsetSumData::operator> (const MaxSubsetSumData& other) const {
	return _value > other.Value();
}