#pragma once
#include <iostream>
#include <variant>
using namespace std;
class VariantVisitor
{
private:
	template <typename T>
	void print(T arg);

public:
	template <typename... Args>
	auto operator()(Args... args)
	{
		(print(args), ...); // https://stackoverflow.com/questions/33868486/parameter-packs-not-expanded-with
	}
};