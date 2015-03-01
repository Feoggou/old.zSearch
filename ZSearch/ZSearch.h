// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the ZSEARCH_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ZSEARCH_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef ZSEARCH_EXPORTS
#define ZSEARCH_API __declspec(dllexport)
#else
#ifdef _DEBUG
#define ZSEARCH_API
#else
#define ZSEARCH_API __declspec(dllimport)
#endif //_DEBUG
#endif //ZSEARCH_EXPORTS

#include <string>
#include <vector>

#pragma warning (disable : 4251)

struct ZSEARCH_API ZResultItem
{
	std::wstring fullFileName;
};

#pragma warning (default : 4251)

typedef std::vector<ZResultItem> ZResultItems;

// This class is exported from the ZSearch.dll
class ZSEARCH_API ZSearch
{
public:
	enum Option
	{
		//TODO: flags?
		FileNameCaseSensitive = 0,
	};

	ZSearch(void);
	
	void SetOption(Option option, bool value) { m_FileNameCS = value; }
	bool GetOption(Option option) { return m_FileNameCS; }

	ZResultItems&& operator()(const std::wstring& dirPath);

private:
	bool m_FileNameCS;
};

extern ZSEARCH_API int nZSearch;

ZSEARCH_API int fnZSearch(void);
