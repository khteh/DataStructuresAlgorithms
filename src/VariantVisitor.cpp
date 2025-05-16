#include "pch.h"
#include "VariantVisitor.h"
template void VariantVisitor::print<int>(int);
template void VariantVisitor::print<long>(long);
template void VariantVisitor::print<string>(string);
template void VariantVisitor::print<float>(float);
template void VariantVisitor::print<double>(double);
template <typename T>
void VariantVisitor::print(T arg)
{
	cout << "Type: " << typeid(arg).name() << ", value: " << arg << endl;
}