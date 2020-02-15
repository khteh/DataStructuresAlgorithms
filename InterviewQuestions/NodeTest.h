#pragma once
#include <vector>
#include <string>
using namespace std;
class NodeTest
{
private:
	string _value;
	vector<NodeTest*> _children;
	NodeTest* _right;
public:
	NodeTest();
	virtual ~NodeTest();
};

