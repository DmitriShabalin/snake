#include <iostream>
#include<Windows.h>
using namespace std;

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

const int Width = 17;
const int Height = 10;
const int MaxLenSnake = (Width - 3) * (Height - 2);

const int Up = 0;
const int Down = 1;
const int Left = 2;
const int Right = 3;

int snakeDir = Up;

bool isRunning = true;

char map[] =
"################\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"#              #\n"
"################\n";

char snake = 'O';
int snakeX[MaxLenSnake] = { 0 };
int snakeY[MaxLenSnake] = { 0 };
int snakeLen = 1;
int foodX = 1 + (rand() % (Width - 3));
int foodY = 1 + (rand() % (Height - 2));
char food = '*';
int main() {
	snakeX[0] = Width / 2;
	snakeY[0] = Height / 2;
	int time = clock();

	while (isRunning) {

		if (GetKeyState('W') & 0x8000) {
			if (snakeDir != Down) {
				snakeDir = Up;
			}
		}
		if (GetKeyState('A') & 0x8000) {
			if (snakeDir != Right) {
				snakeDir = Left;
			}
		}
		if (GetKeyState('S') & 0x8000) {
			if (snakeDir != Up) {
				snakeDir = Down;
			}
		}
		if (GetKeyState('D') & 0x8000) {
			if (snakeDir != Left) {
				snakeDir = Right;
			}
		}

		if ((clock() - time) / CLOCKS_PER_SEC >= 1) {
			time = clock();
			if (snakeX[0] == foodX && snakeY[0] == foodY) {
				++snakeLen;
				foodX = 1 + (rand() % (Width - 3));
				foodY = 1 + (rand() % (Height - 2));
			}
			for (int i = snakeLen - 2; i >= 0; --i) {
				snakeX[i + 1] = snakeX[i];
				snakeY[i + 1] = snakeY[i];
			}

			if (snakeDir == Up) {
				--snakeY[0];
			}
			if (snakeDir == Down) {
				++snakeY[0];
			}
			if (snakeDir == Right) {
				++snakeX[0];
			}
			if (snakeDir == Left) {
				--snakeX[0];
			}
			if (snakeX[0] == 0 || snakeY[0] == 0 || snakeX[0] == Width - 2 || snakeY[0] == Height - 1) {
				isRunning = false;
			}
			for (int i = 1; i < snakeLen; ++i) {
				if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
					isRunning = false;
					i = snakeLen;
				}
			}
			gotoxy(0, 0);
			cout << "Lenght: " << snakeLen << endl;
			map[foodY * Width + foodX] = food;
			for (int i = 0; i < snakeLen; ++i) {
				map[snakeY[i] * Width + snakeX[i]] = snake;
			}
			cout << map;
			for (int i = 0; i < snakeLen; ++i) {
				map[snakeY[i] * Width + snakeX[i]] = ' ';
			}
		}
	}
	gotoxy(1, Height / 2);
	cout << "You score = " << snakeLen;
	gotoxy(Width, Height);
}