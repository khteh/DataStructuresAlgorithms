#include "pch.h"
using namespace std;
class CircularLinkedListTestFixture : public testing::TestWithParam<tuple<long, vector<long>>>
{
public:
	void SetUp() override
	{
		_expected = get<0>(GetParam());
		_data = get<1>(GetParam());
		_cll = CircularLinkedList<long>(_data);
	}
	long LoopStartTest()
	{
		shared_ptr<Node<long>> head = _cll.Head();
		return _cll.LoopStart(head);
	}

protected:
	long _expected;
	CircularLinkedList<long> _cll;
	vector<long> _data;
};
TEST_P(CircularLinkedListTestFixture, LoopStartTests)
{
	ASSERT_EQ(this->_expected, this->LoopStartTest());
}
INSTANTIATE_TEST_SUITE_P(
	LoopStartTests,
	CircularLinkedListTestFixture,
	::testing::Values(make_tuple(0, vector<long>{-1, 0, 1, 2, 3, 4, 5, 0}), make_tuple(0, vector<long>{-2, -1, 0, 1, 2, 3, 4, 5, 0}), make_tuple(0, vector<long>{-3, -2, -1, 0, 1, 2, 3, 4, 5, 0}), make_tuple(numeric_limits<long>::max(), vector<long>{-3, -2, -1, 0, 1, 2, 3, 4, 5}),
					  make_tuple(numeric_limits<long>::max(), vector<long>{1, 2}), make_tuple(1, vector<long>{1, 2, 1}), make_tuple(numeric_limits<long>::max(), vector<long>{1})));