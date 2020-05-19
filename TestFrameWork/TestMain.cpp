
#include "TestMain.h"
#include "MyTestCases.h"
#include<iostream>
#include <windows.h> 

using namespace std;

int g_TotalPassed = 0 ;
int g_TotalFailed = 0 ;
int g_TotalSkipped = 0 ;
int g_TotalTestSuitsRan = 0;
int g_TotalTestSuitsFailed = 0;


TestCases ModuleATestCases[] = {
	{"testcaseA1",testcaseA1},
    {"testcaseA1",testcaseA2},
	{"FiniTestCase",FINITESTCASE}
};

TestCases ModuleBTestCases[] = {
	{"testcaseB1",testcaseB1},
    {"testcaseB2",testcaseB2},
	{"FiniTestCase",FINITESTCASE}

};




TestSuite g_TestSuites[] = {

	{"ModuleA",ModuleATestCases},
	{"ModuleB",ModuleBTestCases},
	{"FiniTestSuite",FINITESTSUITE}
};



void PrintTestResults()
{
std::cout<<"\t=============="<<endl;
cout<<"\tTEST RESULTS"<<endl;
std::cout<<"\t=============="<<endl;
cout<<"\tg_TotalPassed  = "<<g_TotalPassed<<endl;
cout<<"\tg_TotalFailed = "<<g_TotalFailed<<endl;
cout<<"\tg_TotalSkipped = "<<g_TotalSkipped<<endl;
cout<<"\tg_TotalTestSuitsRan = "<<g_TotalTestSuitsRan<<endl;
cout<<"\tg_TotalTestSuitsFailed = "<<g_TotalTestSuitsFailed<<endl;
std::cout<<"\t=============="<<endl;

}


int main()
{

	int ret = 0;
	bool suitefailedflag = false;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout<<endl<<"\t=============="<<endl;
	std::cout<<"\tTEST FRAMEWORK"<<endl;
	std::cout<<"\t=============="<<endl;
	TestSuite *TestSuiteList = g_TestSuites;

	for(int iTestSuite = 0;TestSuiteList[iTestSuite].ptrTestCases != NULL;iTestSuite++)
	{

		std::cout<<"\nStarted Test-Suite : "<<TestSuiteList[iTestSuite].name;

		TestCases *ptrTestCaseList = TestSuiteList[iTestSuite].ptrTestCases;
		g_TotalTestSuitsRan++;
		
		//suitefailedflag  alreday set to false

		for(int iTestCase = 0;ptrTestCaseList[iTestCase].ptrTestFunction != NULL;iTestCase++)
		{

			std::cout<<"\nCalling Test-Case: "<<ptrTestCaseList[iTestCase].name;

			EnumResult er = ptrTestCaseList[iTestCase].ptrTestFunction();
			switch(er)
			{
				case PASS:
					g_TotalPassed++;
					SetConsoleTextAttribute(hConsole, 2);
					std::cout<<" : PASS"<<endl;
					break;

				case FAIL:
					g_TotalFailed++;
					suitefailedflag = true;
					SetConsoleTextAttribute(hConsole, 12);
					std::cout<<" : FAIL"<<endl;
					break;

				case UNKNOWN:
				default:
					g_TotalSkipped++;

			}
			SetConsoleTextAttribute(hConsole, 15);

		}//end of test cases

		if(suitefailedflag == true)
		{
			g_TotalTestSuitsFailed++;
			suitefailedflag = false;
		}


	}//end of testsuites

    SetConsoleTextAttribute(hConsole, 1);
	PrintTestResults();
	SetConsoleTextAttribute(hConsole, 15);


	//fail Test result of excepted result differs
	if (g_TotalTestSuitsFailed > 0)
		ret = -1;

	return ret;

}