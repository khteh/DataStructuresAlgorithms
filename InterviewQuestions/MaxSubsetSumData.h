#pragma once
class MaxSubsetSumData
{
private:
	size_t _index;
	long _value;
public:
	MaxSubsetSumData();
	MaxSubsetSumData(size_t i, long v);
	long Value() const;
	size_t Index() const;
	bool operator< (const MaxSubsetSumData& other) const;
	bool operator> (const MaxSubsetSumData& other) const;
};