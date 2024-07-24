#include "pch.h"
/* Only used in Visual Studio 2022 on Windows */
int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}