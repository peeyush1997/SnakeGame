#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<fstream>

using namespace std;

void Run();
void BoxPrint();
void InitialBox();
void Move(int dx, int dy);
void UpdateSnake();
void DirectionChange(char key);
void ClearScreen();
void GenerateFood();
char GetBoxValue(int value);

const int width = 15;
const int height = 15;
const int Size = width * height;

int squarebox[Size];

int xposition;
int yposition;
int direction;
int startinglenght = 4;
bool running;

int main()
{
    Run();
    return 0;
}

void Run()
{
    InitialBox();
    running = true;
    while(running)
    {
        if(kbhit())
            DirectionChange(getch());

        UpdateSnake();
        ClearScreen();
        BoxPrint();
        _sleep(220);
    }
    std::cout << "\t\t!!!*Game Over*!!!" << std::endl << "\t\tYour Score is: " << startinglenght;
    std::cin.ignore();
}

void DirectionChange(char key)
{
    switch (key) {
    case 'w':
        if (direction != 2) direction = 0;
        break;
    case 'd':
        if (direction != 3) direction = 1;
        break;
    case 's':
        if (direction != 4) direction = 2;
        break;
    case 'a':
        if (direction != 5) direction = 3;
        break;
    }
}

void ClearScreen()
{
    system("cls");
}

void UpdateSnake()
{
    switch (direction) {
    case 0: Move(-1, 0);
        break;
    case 1: Move(0, 1);
        break;
    case 2: Move(1, 0);
        break;
    case 3: Move(0, -1);
        break;
    }
    for (int i = 0; i < Size; i++) {
        if (squarebox[i] > 0) squarebox[i]--;
    }
}

void Move(int dx , int dy)
{
    int x = xposition + dx;
    int y = yposition + dy;

    if(squarebox[x + y * width] == -2)
    {
        startinglenght++;
        GenerateFood();
    }
    else if(squarebox[x + y * width] != 0)
            running = false;

    xposition = x;
    yposition = y;
    squarebox[x + y * width] = startinglenght + 1;
}

void GenerateFood() {
    int x1 = 0;
    int y1 = 0;
    do
    {
        x1 = rand() % (width - 2) + 1;
        y1 = rand() % (height - 2) + 1;
    }
    while (squarebox[x1 + y1 * width] != 0);

    squarebox[x1 + y1 * width] = -2;
}

void BoxPrint()
{
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y){
            std::cout << GetBoxValue(squarebox[x + y * width]);
        }
        std::cout << std::endl;
    }
}

void InitialBox()
{
    xposition = width / 2;
    yposition = height / 2;
    squarebox[xposition + yposition * width] = 1;

    for (int x = 0; x < width; ++x) {
        squarebox[x] = -1;
        squarebox[x + (height - 1) * width] = -1;
    }
    for (int y = 0; y < height; y++) {
        squarebox[0 + y * width] = -1;
        squarebox[(width - 1) + y * width] = -1;
    }
    GenerateFood();
}
char GetBoxValue(int value)
{
    if (value > 0) return 'o';

    switch (value) {

    case -1: return 'X';

    case -2: return 'O';
    }
}

