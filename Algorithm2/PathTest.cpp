#include "PathTest.h"
#include "MyString.h"

void PathTest::Init(void)
{
	Add("FullPath", [&]() {
		wchar_t path[] = L"D:\\Test\\Test01\\file.ext";
		My::Path p(path);
		wstring s = p.Drive();
		wcout << L"Drive: " << s << endl;
		ASSERT1(s == L"D:");
		s = p.Directory();
		wcout << L"Directory: " << s << endl;
		ASSERT1(s == L"\\Test\\Test01\\");
		s = p.File();
		wcout << L"File: " << s << endl;
		ASSERT1(s == L"file");
		s = p.Extension();
		wcout << L"Extension: " << s << endl;
		ASSERT1(s == L".ext");
		s = p.FullPath();
		wcout << L"FullPath: " << s << endl;
		ASSERT1(s == wstring(path));
	});

	Add("Drive:\\Directory", [&]() {
		wchar_t path[] = L"D:\\Test\\Test01";
		My::Path p(path);
		wstring s = p.Drive();
		wcout << L"Drive: " << s << endl;
		ASSERT1(s == L"D:");
		s = p.Directory();
		wcout << L"Directory: " << s << endl;
		ASSERT1(s == L"\\Test\\");
		s = p.File();
		wcout << L"File: " << s << endl;
		ASSERT1(s == L"Test01");
		s = p.Extension();
		wcout << L"Extension: " << s << endl;
		ASSERT1(s == L"");
		s = p.FullPath();
		wcout << L"FullPath: " << s << endl;
		ASSERT1(s == wstring(path));
	});

	Add("Drive::\\Directory\\", [&]() {
		wchar_t path[] = L"D:\\Test\\Test01\\";
		My::Path p(path);
		wstring s = p.Drive();
		wcout << L"Drive: " << s << endl;
		ASSERT1(s == L"D:");
		s = p.Directory();
		wcout << L"Directory: " << s << endl;
		ASSERT1(s == L"\\Test\\Test01\\");
		s = p.File();
		wcout << L"File: " << s << endl;
		ASSERT1(s == L"");
		s = p.Extension();
		wcout << L"Extension: " << s << endl;
		ASSERT1(s == L"");
		s = p.FullPath();
		wcout << L"FullPath: " << s << endl;
		ASSERT1(s == wstring(path));
	});

	Add("\\Directory\\", [&]() {
		wchar_t path[] = L"\\Test\\Test01\\";
		My::Path p(path);
		wstring s = p.Drive();
		wcout << L"Drive: " << s << endl;
		ASSERT1(s == L"");
		s = p.Directory();
		wcout << L"Directory: " << s << endl;
		ASSERT1(s == L"\\Test\\Test01\\");
		s = p.File();
		wcout << L"File: " << s << endl;
		ASSERT1(s == L"");
		s = p.Extension();
		wcout << L"Extension: " << s << endl;
		ASSERT1(s == L"");
		s = p.FullPath();
		wcout << L"FullPath: " << s << endl;
		ASSERT1(s == wstring(path));
	});

	Add("Directory", [&]() {
		wchar_t path[] = L"Test\\Test01";
		My::Path p(path);
		wstring s = p.Drive();
		wcout << L"Drive: " << s << endl;
		ASSERT1(s == L"");
		s = p.Directory();
		wcout << L"Directory: " << s << endl;
		ASSERT1(s == L"Test\\");
		s = p.File();
		wcout << L"File: " << s << endl;
		ASSERT1(s == L"Test01");
		s = p.Extension();
		wcout << L"Extension: " << s << endl;
		ASSERT1(s == L"");
		s = p.FullPath();
		wcout << L"FullPath: " << s << endl;
		ASSERT1(s == wstring(path));
	});
}