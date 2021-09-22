#pragma once

//This code usually resides in the stdafx.h file and 
//sets the manifest so that the modern Windows controls 
//are used. If this is missing dialog boxes will look old
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

/*===================================================================#
| 'Utility' source files last updated on 22 September 2021           |
#====================================================================#
| Class has not been fully tested. No known issues found.            |
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

	enum class Severity
	{
		Failure = MB_ICONERROR,
		Warning = MB_ICONWARNING,
		Default = MB_ICONINFORMATION
	};

	static void RemoveCharacter(std::string& string, char character);

	static void ParseString(const std::string& string,
		std::vector<std::string>& subStrings, char token);

	static bool LoadConfigFile(const std::string& filename,
		std::map<std::string, std::string>& dataMap);

	static void Log(int destination, float value, const std::string& label = "");
	static void Log(int destination, const std::string& message, Severity severity = Severity::Default);
	static void Log(int destination, float x, float y, float z, const std::string& label = "");

};