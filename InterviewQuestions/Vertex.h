#pragma once
#include <map>
using namespace std;
template<class T>
class Vertex
{
public:
	Vertex();
	Vertex(T tag);
	Vertex(T tag, map<T, Vertex>);
	virtual ~Vertex();
protected:
	T tag_;
	map<T, Vertex<T>*> neighbours_;
};