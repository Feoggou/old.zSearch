#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ZCore
{
	TEST_CLASS(utest_WinDir)
	{
		BEGIN_TEST_CLASS_ATTRIBUTE()
			TEST_CLASS_ATTRIBUTE(L"Ignore", L"true")
		END_TEST_CLASS_ATTRIBUTE()
	public:
		
		TEST_METHOD(Windir_Nothing)
		{
			// TODO: Your test code here
			Assert::Fail(L"not implemented!");
		}

	};

	TEST_CLASS(utest_WinFile)
	{
		BEGIN_TEST_CLASS_ATTRIBUTE()
			TEST_CLASS_ATTRIBUTE(L"Ignore", L"true")
		END_TEST_CLASS_ATTRIBUTE()
	public:

		TEST_METHOD(WinFile_Nothing)
		{
			// TODO: Your test code here
			Assert::Fail(L"not implemented!");
		}

	};

	TEST_CLASS(utest_WinPath)
	{
		BEGIN_TEST_CLASS_ATTRIBUTE()
			TEST_CLASS_ATTRIBUTE(L"Ignore", L"true")
		END_TEST_CLASS_ATTRIBUTE()
	public:

		TEST_METHOD(WinPath_Nothing)
		{
			// TODO: Your test code here
			Assert::Fail(L"not implemented!");
		}

	};
}