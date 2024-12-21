#include <Windows.h>
#include <fstream>
#include <iostream>
#include <stdio.h>

#include "main.h"

int WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd
)
{
	if (true)
	{
		AllocConsole();
		freopen("conin$", "r", stdin);
		freopen("conout$", "w", stdout);
		freopen("conin$", "w", stderr);
		std::cout.sync_with_stdio();
	};

	
	main();


	return 0;
}