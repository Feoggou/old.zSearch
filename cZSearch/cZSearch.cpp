// cZSearch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../ZSearch/ZSearch.h"

#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	int x = fnZSearch();
	std::cout << x << std::endl;

	CZSearch czSearch;

	doX();

	return 0;
}

