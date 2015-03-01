#include "stdafx.h"
#include "CppUnitTest.h"

#include "Dir.h"
#include "File.h"
#include "FilePath.h"
#include "FileInfo.h"
#include "DirEnumerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

struct FilePathData
{
	const wchar_t* str;
	bool valid;
	bool relative;
};

FilePathData s_pathData[] ={
	//str			    valid	relative
	{ L"myPath",		true,	true  },
	{ L"C:\\Users",		true,	false },
	{ L"M",				true,	true  },
	{ L"",				false,	false },
	{ L"\t",			false,	false },
	{ L" ",				false,  false },
	{ L" a",			false,  false },
	{ L"a ",			false,  false },
	{ L"a .txt",		true,   true  },
	{ L".\temp.txt",	true,	true  },
	{ L"file.",			false,	false },
	{ L".file",			true,	true  },
	{ L"\\server\\share",true,	false },
	{ L"\\temp.txt",	true,	false },
	{ L"șțăîtemp.txt",	true,	true  }
};

template <>
inline static std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Zen::FilePath>(const Zen::FilePath& q)
{
	return q.ToWString();
}

template <>
inline static std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Zen::Dir>(Zen::Dir* q)
{
	if (q)
	{
		return q->GetPath().ToWString();
	}

	return std::wstring();
}

template <>
inline static std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Zen::DirIterator>(const Zen::DirIterator& q)
{
	return std::wstring(L"DirIterator__UnknownName");
}

TEST_CLASS(utest_Path)
{
public:
	TEST_METHOD(Path_Valid)
	{
		for (auto& fp : s_pathData)
		{
			Zen::FilePath path(fp.str);

			if (fp.valid) {
				Assert::IsTrue(path.IsValid(), fp.str);
			}
			else {
				Assert::IsFalse(path.IsValid(), fp.str);
			}
		}
	}

	TEST_METHOD(Path_Relative)
	{
		for (auto& fp : s_pathData)
		{
			Zen::FilePath path(fp.str);

			if (fp.relative) {
				Assert::IsTrue(path.IsRelative(), fp.str);
			}
			else {
				Assert::IsFalse(path.IsRelative(), fp.str);
			}
		}
	}

};

TEST_CLASS(utest_Dir)
{
public:

	TEST_METHOD(Dir_Ctor_Str_Simple)
	{
		Zen::FilePath path1 = L"path";
		Zen::Dir dir(path1);
		Zen::FilePath path2 = dir.GetPath();

		Assert::AreEqual(path1, path2, L"dir path simple", LINE_INFO());
	}

	TEST_METHOD(Dir_Create_Delete)
	{
		Zen::Dir dir(L"folderName");
		
		Assert::IsFalse(dir.Exists());
		Assert::IsTrue(dir.Create());

		Assert::IsTrue(dir.Exists());
		Assert::IsTrue(dir.Delete());
		Assert::IsFalse(dir.Exists());
	}

};

TEST_CLASS(utest_File)
{
public:
	TEST_METHOD(File_Ctor_Str_Simple)
	{
		Zen::FilePath path1 = L"path";
		Zen::File file(path1);
		Zen::FilePath path2 = file.GetPath();

		Assert::AreEqual(path1, path2, L"file path simple", LINE_INFO());
	}

	TEST_METHOD(File_Create_Delete)
	{
		Zen::File file(L"fileName");

		Assert::IsFalse(file.Exists());
		Assert::IsTrue(file.Create());

		Assert::IsTrue(file.Exists());
		Assert::IsTrue(file.Delete());
		Assert::IsFalse(file.Exists());
	}
};

TEST_CLASS(utest_DirEnumerator)
{
public:

	TEST_METHOD(DirEnum_Create)
	{
		Zen::Dir dir(L"dir");
		std::unique_ptr<Zen::DirEnumerator> pEnum = dir.Enumerator();

		Assert::IsNotNull(pEnum.get());
	}
};

TEST_CLASS(utest_DirIterator)
{
public:

	TEST_METHOD(DirIter_Empty)
	{
		Zen::Dir dir(L"dir");
		auto pEnum = dir.Enumerator();

		Zen::DirEnumerator::iterator I = pEnum->begin();
		Zen::DirEnumerator::iterator end = pEnum->end();

		Zen::DirEnumerator::iterator I2 = pEnum->begin();
		Zen::DirEnumerator::iterator end2 = pEnum->end();

		Assert::AreEqual(I, I2);
		Assert::AreEqual(end, end2);

		Assert::AreEqual(I, end);
	}

	TEST_METHOD(DirIter_Begin_NotEmpty)
	{
		Zen::Dir dir(L"dir");
		Zen::File file(dir, L"file");
		std::unique_ptr<Zen::DirEnumerator> pEnum = dir.Enumerator();

		Assert::IsTrue(dir.Create());
		Assert::IsFalse(file.Exists());
		Assert::IsTrue(file.Create());

		Zen::DirEnumerator::iterator I = pEnum->begin();
		Zen::DirEnumerator::iterator end = pEnum->end();

		Zen::DirEnumerator::iterator I2 = pEnum->begin();
		Zen::DirEnumerator::iterator end2 = pEnum->end();

		Assert::AreEqual(I, I2);
		Assert::AreEqual(end, end2);

		Assert::AreNotEqual(I, end);

		Assert::IsTrue(dir.Delete());
	}

	TEST_METHOD(DirIter_OneFile)
	{
		Zen::Dir dir(L"dir1");
		std::unique_ptr<Zen::DirEnumerator> pEnum = dir.Enumerator();

		Assert::IsTrue(dir.Create());

		Zen::File file(dir, L"file");
		Assert::IsFalse(file.Exists());

		Assert::IsTrue(file.Create());

		Zen::DirEnumerator::iterator I = pEnum->begin();
		Zen::DirEnumerator::iterator end = pEnum->end();

		Zen::FileInfo fi = *I;
		Assert::AreEqual(fi.DisplayName(), std::wstring(L"file"));

		Assert::IsTrue(dir.Delete());
	}

	BEGIN_TEST_METHOD_ATTRIBUTE(DirIter_IterNext)
		TEST_METHOD_ATTRIBUTE(L"Ignore", L"true")
		END_TEST_METHOD_ATTRIBUTE()
	TEST_METHOD(DirIter_IterNext)
	{
		Zen::Dir dir(L"dir1");
		std::unique_ptr<Zen::DirEnumerator> pEnum = dir.Enumerator();

		Assert::IsTrue(dir.Create());

		Zen::File file(dir, L"file");
		Assert::IsFalse(file.Exists());
		Assert::IsTrue(file.Create());

		Zen::DirEnumerator::iterator I = pEnum->begin();
		Zen::DirEnumerator::iterator end = pEnum->end();

		Assert::AreNotEqual(I, end);

		++I;

		Assert::AreEqual(I, end);
	}

	BEGIN_TEST_METHOD_ATTRIBUTE(DirIter_FiveFiles)
		TEST_METHOD_ATTRIBUTE(L"Ignore", L"true")
	END_TEST_METHOD_ATTRIBUTE()
	TEST_METHOD(DirIter_FiveFiles)
	{
		Zen::Dir dir(L"dir5");
		std::unique_ptr<Zen::DirEnumerator> pEnum = dir.Enumerator();

		Assert::IsTrue(dir.Create());

		for (int i = 0; i < 5; ++i)
		{
			wchar_t wsName[20];

			swprintf(wsName, 20, L"file%i.txt", i);
			Zen::File file(dir, wsName);

			Assert::IsFalse(file.Exists());
			Assert::IsTrue(file.Create());
		}

		Zen::DirEnumerator::iterator I;
		int i = 0;
		for (I = std::begin(*pEnum); I != std::end(*pEnum); ++I, ++i)
		{
			wchar_t wsName[20];
			swprintf(wsName, 20, L"file%i.txt", i);

			Zen::FileInfo fi = *I;
			Assert::AreEqual(fi.DisplayName(), std::wstring(wsName));
		}

		Assert::AreEqual(i, 5);
		Assert::AreEqual(I, std::end(*pEnum));
	}

};

TEST_CLASS(utest_Exception)
{
public:
	BEGIN_TEST_CLASS_ATTRIBUTE()
		TEST_CLASS_ATTRIBUTE(L"Ignore", L"true")
		END_TEST_CLASS_ATTRIBUTE()

		TEST_METHOD(TestMethod1)
	{
		// TODO: Your test code here
		Assert::Fail(L"not implemented!");
	}

};

TEST_CLASS(utest_Logger)
{
public:
	BEGIN_TEST_CLASS_ATTRIBUTE()
		TEST_CLASS_ATTRIBUTE(L"Ignore", L"true")
		END_TEST_CLASS_ATTRIBUTE()

		TEST_METHOD(TestMethod1)
	{
		// TODO: Your test code here
		Assert::Fail(L"not implemented!");
	}

};

TEST_CLASS(utest_MemResource)
{
public:

	BEGIN_TEST_CLASS_ATTRIBUTE()
		TEST_CLASS_ATTRIBUTE(L"Ignore", L"true")
		END_TEST_CLASS_ATTRIBUTE()

		TEST_METHOD(TestMethod1)
	{
		// TODO: Your test code here
		Assert::Fail(L"not implemented!");
	}

};