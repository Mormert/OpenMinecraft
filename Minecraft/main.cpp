#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

#include <Windows.h>
#include <iostream>
#include <sstream>


#include "Engine.h"

void DBOut(const char* file, const int line, const WCHAR* s)
{
    std::wostringstream os_;
    os_ << file << "(" << line << "): ";
    os_ << s;
    OutputDebugStringW(os_.str().c_str());
}

#define DBOUT(s)       DBOut(__FILE__, __LINE__, s)

int main()
{

    DBOUT(L"hello man!\n");

	Engine engine;
	engine.Run();

	return 0;
}