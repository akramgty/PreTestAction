#pragma once
#include <string>
#include <iostream>

enum EnumResult
{
	PASS=1,
	FAIL=2,
	UNKNOWN=3,
};

struct TestCases
{
	std::string name;
	EnumResult (*ptrTestFunction)();
};

struct TestSuite
{
	std::string name;
	TestCases *ptrTestCases;
};


#define FINITESTCASE NULL
#define FINITESTSUITE NULL