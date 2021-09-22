#include <assert.h>
#include <fstream>
#include <sstream>
#include "Screen.h"
#include "Utility.h"

void Utility::RemoveCharacter(std::string& string, char character)
{
	auto it = std::find(string.begin(), string.end(), character);

	if (it != string.end())
	{
		do
		{
			string.erase(it);
			it = std::find(string.begin(), string.end(), character);
		} while (it != string.end());
	}
}

void Utility::ParseString(const std::string& string, std::vector<std::string>& subStrings, char token)
{
	size_t start = 0;
	size_t end = 0;

	assert(!string.empty());

	while (end != std::string::npos)
	{
		end = string.find(token, start);
		if ((end - start) > 0)
		{
			subStrings.push_back(string.substr(start, end - start));
		}
		start = end + 1;
	}
}

bool Utility::LoadConfigFile(const std::string& filename,
	std::map<std::string, std::string>& dataMap)
{
	std::fstream file(filename, std::ios_base::in);

	if (!file.is_open())
	{
		return false;
	}

	std::string line;
	std::vector<std::string> subStrings;

	while (!file.eof())
	{
		std::getline(file, line);
		std::vector<std::string> subStrings;

		ParseString(line, subStrings, '=');

		if (!subStrings.empty())
		{
			dataMap[subStrings[KEY]] = subStrings[VALUE];
		}
	}

	file.close();
	return true;
}

void Utility::Log(int destination, float value, const std::string& label)
{
	if (!label.empty())
	{
		if (destination == MESSAGE_BOX)
		{
			MessageBox(Screen::Instance()->GetWindowHandle(),
				reinterpret_cast<LPCSTR>(std::to_string(value).c_str()),
				reinterpret_cast<LPCSTR>(std::wstring(label.begin(), label.end()).c_str()),
				MB_ICONINFORMATION | MB_OK);
		}

		else if (destination == VS_OUTPUT)
		{
			std::string message = "[" + label + "] " + std::to_string(value) + "\n";
			OutputDebugString(reinterpret_cast<LPCSTR>
				(std::wstring(message.begin(), message.end()).c_str()));
		}

		else if (destination == FILE)
		{
			std::fstream file("Data/Output.log", std::ios_base::out | std::ios_base::app);
			std::string message = "[" + label + "] " + std::to_string(value) + "\n";
			file << message;
			file.close();
		}
	}
}

void Utility::Log(int destination, const std::string& message, Severity severity)
{
	if (!message.empty())
	{
		if (destination == MESSAGE_BOX)
		{
			MessageBox(Screen::Instance()->GetWindowHandle(),
				reinterpret_cast<LPCSTR>(std::string(message.begin(), message.end()).c_str()),
				"Log", static_cast<int>(severity) | MB_OK);
		}

		else if (destination == VS_OUTPUT)
		{
			std::string finalMessage;

			if (severity == Severity::Failure)
			{
				finalMessage = "[FAILURE] " + message + "\n";
			}

			else if (severity == Severity::Warning)
			{
				finalMessage = "[WARNING] " + message + "\n";
			}

			else
			{
				finalMessage = message + "\n";
			}

			OutputDebugString(reinterpret_cast<LPCSTR>
				(std::string(finalMessage.begin(), finalMessage.end()).c_str()));
		}

		else if (destination == FILE)
		{
			std::string finalMessage;
			std::fstream file("Data/Output.log", std::ios_base::out | std::ios_base::app);

			if (severity == Severity::Failure)
			{
				finalMessage = "[FAILURE] " + message + "\n";
			}

			else if (severity == Severity::Warning)
			{
				finalMessage = "[WARNING] " + message + "\n";
			}

			else
			{
				finalMessage = message + "\n";
			}

			file << finalMessage;
			file.close();
		}
	}
}

void Utility::Log(int destination, float x, float y, float z, const std::string& label)
{
	if (!label.empty())
	{
		if (destination == MESSAGE_BOX)
		{
			std::string message = "x = " + std::to_string(x) +
				", y = " + std::to_string(y) +
				", z = " + std::to_string(z);

			MessageBox(Screen::Instance()->GetWindowHandle(),
				reinterpret_cast<LPCSTR>(std::string(message.begin(), message.end()).c_str()),
				reinterpret_cast<LPCSTR>(std::string(label.begin(), label.end()).c_str()),
				MB_ICONINFORMATION | MB_OK);
		}

		else if (destination == VS_OUTPUT)
		{
			std::string message = "[" + label + "] " + "x = " + std::to_string(x) +
				", y = " + std::to_string(y) +
				", z = " + std::to_string(z) + "\n";
			OutputDebugString(reinterpret_cast<LPCSTR>
				(std::wstring(message.begin(), message.end()).c_str()));
		}

		else if (destination == FILE)
		{
			std::fstream file("Data/Output.log", std::ios_base::out | std::ios_base::app);
			std::string message = "[" + label + "] " + "x = " + std::to_string(x) +
				", y = " + std::to_string(y) +
				", z = " + std::to_string(z) + "\n";
			file << message;
			file.close();
		}
	}
}