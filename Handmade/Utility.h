#pragma once

//this code usually resides in the stdafx.h file and 
//sets the manifest so that the modern Windows controls 
//are used. If this is missing dialog boxes will look old
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

/*===================================================================#
| 'Utility' source files last updated on 28 May 2021                 |
#===================================================================*/

#include <Windows.h>
#include <map>
#include <string>
#include <vector>

//TODO - Consider replacing these with enums

#define KEY 0
#define VALUE 1

#define FILE 2
#define VS_OUTPUT 4
#define MESSAGE_BOX 8

class Utility
{

public:

	enum Severity
	{
		FAILURE = MB_ICONERROR,
		WARNING = MB_ICONWARNING,
		DEFAULT = MB_ICONINFORMATION
	};

	static void RemoveCharacter(std::string& str, char character);

	static void ParseString(const std::string& str,
		std::vector<std::string>& subStrings, char token);

	static bool LoadConfigFile(const std::string& filename,
		std::map<std::string, std::string>& dataMap);

	static void Log(int destination, float value, const std::string& label = "");
	static void Log(int destination, const std::string& message, Severity severity = DEFAULT);
	static void Log(int destination, float x, float y, float z, const std::string& label = "");

};