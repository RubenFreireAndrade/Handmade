#pragma once

/*===================================================================#
| 'Debug' source files last updated on 11 May 2021                   |
#===================================================================*/

#include <string>
#include <Windows.h>
#include "Vector.h"

class Debug
{

public:

	enum class ErrorCode
	{
		FAILURE = 4,
		WARNING = 6,
		SUCCESS = 10,
		DEFAULT = 15
	};

	static void PauseLog();
	static void ClearLog();
	static void Log(float value, const std::string& label = "");
	static void Log(int x, int y, const std::string& label = "");
	static void Log(const Vector<int>& point, const std::string& label = "");
	static void Log(const std::string& message, ErrorCode errorCode = ErrorCode::DEFAULT);

private:

	static HANDLE s_consoleHandle;

};