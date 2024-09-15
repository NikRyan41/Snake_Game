#include <conio.h> 
#include <iostream> 
#include <windows.h>
#include <string>
using namespace std;

// ������ � ������ ����
const int width = 80;
const int height = 20;

// ���������� ������ ���� (x, y) 
int x, y;
// ���������� ��� (x, y) 
int fruit_X, fruit_Y;
// ���� ������ 
int playerScore;
// Array to store the coordinates of snake tail (x-axis, 
// y-axis) 
int snakeTailX[100], snakeTailY[100];
// ���������� ��� ����� ������ 
int snakeTailLen;
// Enum ��� ����� �������� ���� 
enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
// ��������� - ����������� �������� ���� 
snakesDirection sDir;
// Bool-���������� (��������)
bool GameOver;

// ������� ��� ��������� ������ ��������� 
int Fps() {
	int fps, choice;
	cout << "\nSET MAX FPS\n1: 1 Fps\n2: 10 Fps\n3: 60 Fps "
		"\nNOTE: if not chosen or pressed any other "
		"key, the Max Fps will be automatically set "
		"to 60 Fps\nChoose difficulty level: ";
	cin >> choice;
	switch (choice) {
	case '1':
		fps = 1000;
		break;
	case '2':
		fps = 100;
		break;
	case '3':
		fps = 100/6;
		break;
	default:
		fps = 100/6;
	}
	return fps;
}
int SetDifficulty()
{
	int dfc, choice;
	cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: hard "
		"\nNOTE: if not chosen or pressed any other "
		"key, the difficulty will be automatically set "
		"to medium\nChoose difficulty level: ";
	cin >> choice;
	switch (choice) {
	case '1':
		dfc = 50;
		break;
	case '2':
		dfc = 100;
		break;
	case '3':
		dfc = 1000;
		break;
	default:
		dfc = 100;
	}
	return dfc;
}

//������������� ����
void GameInit() {
		/*isGameOver = false;
		sDir = STOP;
		x = width / 2;
		y = height / 2;
		fruitCordX = rand() % width;
		fruitCordY = rand() % height;
		playerScore = 0;*/
	GameOver = false;
	playerScore = 0;
	sDir = STOP;
	fruit_X = rand() % width;
	fruit_Y = rand() % height;
	x = width / 2;
	y = height / 2;
}

// �������-��������� 
void GameRender(string playerName)
{
	system("cls"); // Clear the console 

	// Creating top walls with '-' 
	for (int i = 0; i < width + 2; i++)
		cout << "-";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j <= width; j++) {
			// Creating side walls with '|' 
			if (j == 0 || j == width)
				cout << "|";
			// Creating snake's head with 'O' 
			if (i == y && j == x)
				cout << "O";
			// Creating the sanke's food with '#' 
			else if (i == fruit_Y && j == fruit_X)
				cout << "#";
			// Creating snake's head with 'O' 
			else {
				// ���������� - �������� �� ������� ������ ������
				bool prTail = false;
				for (int k = 0; k < snakeTailLen; k++) {
					if (snakeTailX[k] == j
						&& snakeTailY[k] == i) {
						cout << "o";
						prTail = true;
					}
				}
				if (!prTail)
					cout << " ";
			}
		}
		cout << endl;
	}
	// Creating bottom walls with '-' 
	for (int i = 0; i < width + 2; i++)
		cout << "-";
	cout << endl;

	// Display player's score 
	cout << playerName << "'s Score: " << playerScore
		<< endl;
}

// ��������� ���������� � �������� 
void UserInput()
{
	// Checks if a key is pressed or not 
	if (_kbhit()) {
		// Getting the pressed key 
		switch (_getch()) {
		case 'a':
			sDir = LEFT;
			break;
		case 'd':
			sDir = RIGHT;
			break;
		case 'w':
			sDir = UP;
			break;
		case 's':
			sDir = DOWN;
			break;
		case 'x':
			GameOver = true;
			break;
		}
	}
}

// ���������� ��������� ���� 
void UpdateGame()
{

	int prevX = snakeTailX[0];
	int prevY = snakeTailY[0];
	int prev2X, prev2Y;
	snakeTailX[0] = x;
	snakeTailY[0] = y;

	for (int i = 1; i < snakeTailLen; i++) {
		prev2X = snakeTailX[i];
		prev2Y = snakeTailY[i];
		snakeTailX[i] = prevX;
		snakeTailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (sDir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	// Checks for snake's collision with the wall (|) 
	if (x >= width || x < 0 || y >= height || y < 0)
		GameOver = true;

	// Checks for collision with the tail (o) 
	for (int i = 0; i < snakeTailLen; i++) {
		if (snakeTailX[i] == x && snakeTailY[i] == y)
			GameOver = true;
	}

	// Checks for snake's collision with the food (#) 
	if (x == fruit_X && y == fruit_Y) {
		playerScore += 10;
		fruit_X = rand() % width;
		fruit_Y = rand() % height;
		snakeTailLen++;
	}
}

// Main function / game looping function 
int main()
{
	string playerName;
	cout << "enter your name: ";
	cin >> playerName;
	int fps = Fps();

	GameInit();
	while (!GameOver) {
		GameRender(playerName);
		UserInput();
		Sleep(fps);
		UpdateGame();
		// creating a delay for according to the chosen 
		// difficulty 
	}
	return 0;
}
