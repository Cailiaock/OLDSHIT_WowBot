// ConsoleTest.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <ProcessDispatcher.h>
#include <iostream>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	ProcessDispatcher disp;
	ProcessInteractor * p;
	int proc_cret=0;
	int inter=0;
	int comm=0;
	int count=0;
	 disp=ProcessDispatcher();

	 p=disp.StartNewProcess();

		

	return 0;
}