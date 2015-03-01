#include "stdafx.h"
#include "CppUnitTest.h"

#include "../ZSearch/ZSearch.h"
#include "../ZCore/Dir.h"
#include "../gmock/gmock.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

BEGIN_TEST_MODULE_ATTRIBUTE()
TEST_MODULE_ATTRIBUTE(L"Date", L"2010/6/12")
END_TEST_MODULE_ATTRIBUTE()

TEST_MODULE_INITIALIZE(ModuleInitialize)
{
	Logger::WriteMessage("In Module Initialize\n");
}

TEST_MODULE_CLEANUP(ModuleCleanup)
{
	Logger::WriteMessage("In Module Cleanup\n");
}

namespace utest
{		
	TEST_CLASS(SearchOption)
	{
	public:
		
		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("In Class Initialize\n");
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("In Class Cleanup\n");
		}

		TEST_METHOD(Option_FileNameCaseSensitive_False)
		{
			//default options
			ZSearch search;
			//set options
			search.SetOption(ZSearch::FileNameCaseSensitive, false);

			Assert::IsFalse(search.GetOption(ZSearch::FileNameCaseSensitive),
				L"search option: FileNameCaseSensitive not false!\n", LINE_INFO());
		}

		TEST_METHOD(Option_FileNameCaseSensitive_True)
		{
			//default options
			ZSearch search;
			//set options
			search.SetOption(ZSearch::FileNameCaseSensitive, true);

			Assert::IsTrue(search.GetOption(ZSearch::FileNameCaseSensitive),
				L"search option: FileNameCaseSensitive not false!\n", LINE_INFO());
		}
	};

	TEST_CLASS(SearchFile)
	{
		TEST_CLASS_INITIALIZE(Search_Init)
		{
			std::wstring curDir = Zen::Dir::GetCurrentDir();
			//create a file
		}

		TEST_CLASS_CLEANUP(Search_Uninit)
		{
			//delete the file
		}

		BEGIN_TEST_METHOD_ATTRIBUTE(Search_OneFile)
		TEST_IGNORE()
		END_TEST_METHOD_ATTRIBUTE()
		TEST_METHOD(Search_OneFile)
		{
			//default options
			ZSearch search;
			//set options
			search.SetOption(ZSearch::FileNameCaseSensitive, true);

			std::vector<ZResultItem> results = search(L"localDirName");

			Assert::AreEqual(results.size(), std::size_t(1), L"result size: expected 1");
			//TODO: or displayName
			Assert::AreEqual(results.back().fullFileName, std::wstring(L"testFile.txt"), L"result name: expected \"testFile.txt\"");
		}
	};
}