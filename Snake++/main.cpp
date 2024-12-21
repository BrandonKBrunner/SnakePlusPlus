#include <iostream>
#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#include <list>

#include "keyLogger.h"

void drawBoard(HANDLE stdHandle);
void drawGameOver(HANDLE stdHandle);
void moveSnake(std::string direction);

const short boardWidth = 11;
char gameboard[boardWidth * boardWidth];
bool fruit = false;
bool gameover = false;

struct Coord
{
	int x;
	int y;
};

struct Snake
{
	std::list<Coord> body;

} snake;

int main()
{
	Coord head;
	head.x = boardWidth / 2;
	head.y = boardWidth / 2;

	snake.body.push_front(head);

	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(stdHandle, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(stdHandle, &cursorInfo);

	for (int i = 0; i < std::size(gameboard); i++)
	{
		if (i == boardWidth * snake.body.front().x + snake.body.front().y)
		{
			gameboard[i] = 'O';
		}
		else
		{
			gameboard[i] = ' ';
		}
	}

	int randVal = std::rand() % (std::size(gameboard) + 1);
	std::string direction = "S";
	
	while (!gameover && getKeyPressed() != "[ESCAPE]" && !(snake.body.front().x < 0 || snake.body.front().x >= boardWidth || snake.body.front().y < 0 || snake.body.front().y >= boardWidth))
	{

		while (gameboard[randVal] == 'O')
		{
			randVal = std::rand() % (std::size(gameboard) + 1);
		}

		if (!fruit)
		{
			fruit = true;
			gameboard[randVal] = '6';
		}

		Sleep(500);
		SetConsoleCursorPosition(stdHandle, {0, 0});

		if (getKeyPressed() == "W" && direction != "S")
		{
			direction = "W";
		}
		else if (getKeyPressed() == "A" && direction != "D")
		{
			direction = "A";
		}
		else if (getKeyPressed() == "S" && direction != "W")
		{
			direction = "S";
		}
		else if (getKeyPressed() == "D" && direction != "A")
		{
			direction = "D";
		}
		
		moveSnake(direction);
		drawBoard(stdHandle);
	}

	drawGameOver(stdHandle);

	CloseHandle(stdHandle);
	return 0;
}

void moveSnake(std::string direction)
{
	// move head
	Coord front;
	
	Coord temp = snake.body.front();

	if (direction == "W")
	{
		front.x = temp.x - 1;
		front.y = temp.y;
	}
	else if (direction == "A")
	{
		front.x = temp.x;
		front.y = temp.y - 1;
	}
	else if (direction == "S")
	{
		front.x = temp.x + 1;
		front.y = temp.y;
	}
	else if (direction == "D")
	{
		front.x = temp.x;
		front.y = temp.y + 1;
	}
	snake.body.push_front(front);

	temp = snake.body.front();
	// move tail
	if (gameboard[boardWidth * temp.x + temp.y] == 'O')
	{
		gameover = true;
	}
	if (gameboard[boardWidth * temp.x + temp.y] != '6')
	{
		gameboard[boardWidth * snake.body.back().x + snake.body.back().y] = ' ';
		snake.body.pop_back();
	}
	else
	{
		fruit = false;
	}
	gameboard[boardWidth * snake.body.front().x + snake.body.front().y] = 'O';
}

void drawBoard(HANDLE stdHandle)
{
	for (int i = 0; i < boardWidth; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			if (gameboard[boardWidth * i + j] == 'O')
			{
				SetConsoleTextAttribute(stdHandle, 0xCC);
			}

			std::cout << gameboard[boardWidth * i + j];
			SetConsoleTextAttribute(stdHandle, 0x07);
		}
		std::cout << '|' << std::endl;
	}
	for (int i = 0; i < boardWidth; i++)
	{
		std::cout << '-';
	}
	std::cout << std::endl;
}

void drawGameOver(HANDLE stdHandle)
{
	SetConsoleCursorPosition(stdHandle, {0, 0});
	SetConsoleTextAttribute(stdHandle, 0x0C);
	for (int i = 0; i < boardWidth; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			std::cout << ' ';
		}
		std::cout << '|' << std::endl;
	}
	for (int i = 0; i < boardWidth; i++)
	{
		std::cout << '-';
	}

	SetConsoleCursorPosition(stdHandle, { (boardWidth / 2) - 4, (boardWidth / 2)});
	std::cout << "GAME OVER" << std::endl;

	SetConsoleCursorPosition(stdHandle, { (boardWidth / 2) - 3, (boardWidth / 2) + 1 });
	std::cout << "Size: " << snake.body.size() << std::endl;

	while (getKeyPressed() != "[ESCAPE]")
	{
	}
}