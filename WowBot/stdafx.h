// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once
//#define WOW_EXECUTABLE_PATH L"C:\\Users\\laptop\\Desktop\\World of Warcraft\\Wow.exe"
#define WOW_EXECUTABLE_PATH L"C:\\Users\\laptop\\Documents\\Visual Studio 2010\\Projects\\Tutorial01\\Debug\\Tutorial01.exe"
#define DLL_PATH "C:\\Users\\laptop\\Documents\\visual studio 2010\\Projects\\WowBot\\Debug\\InProcessLibrary.dll"

#include "targetver.h"
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <iostream>
#include <Communicator.h>
using namespace std;
#include "Exception.h"
#include "Communicator_Client.h"
#include "ProcessInteractor.h"
#include "ProcessDispatcher.h"




// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы
