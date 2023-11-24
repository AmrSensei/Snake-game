// wtf am i doing with my life
#include <iostream>
#include <conio.h>
#include<vector>
#include<algorithm>
#include <windows.h>
using namespace std;
const int width = 20;
const int height = 20;
bool gameover, playagain = true;
int x, y, fruitx, fruity, score, ntail;
bool throwwalls;
int tailx[100], taily[100];
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;
void setup()
{
    gameover = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitx = rand() % width;
    fruity = rand() % height;
    score = 0;
}
void draw()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(hConsole, cursorPosition);
    for (int i = 0; i < width + 2; i++)
    {
        cout << "#";
    }
    cout << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                cout << "#";
            }
            if (i == y && j == x)
            {
                cout << "O";
            }
            else if (i == fruity && j == fruitx)
            {
                cout << "x";
            }
            else
            {
                bool print = false;
                for (int k = 0; k < ntail; k++)
                {
                    if (tailx[k] == j && taily[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                {
                    cout << " ";
                }
            }
            if (j == width - 1)
            {
                cout << "#";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
    {
        cout << "#";
    }
    cout << endl;
    cout << "Score = " << score;
}
void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'p':
            gameover = true;
            break;
        }
    }
}
void logic()
{
    int prex = tailx[0];
    int prey = taily[0];
    int pre2x, pre2y;
    tailx[0] = x;
    taily[0] = y;
    for (int i = 1; i < ntail; i++)
    {
        pre2x = tailx[i];
        pre2y = taily[i];
        tailx[i] = prex;
        taily[i] = prey;
        prex = pre2x;
        prey = pre2y;
    }
    switch (dir)
    {
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
    if (!throwwalls)
    {
        if (x > width || x < 0 || y > height || y < 0)
        {
            gameover = 1;
        }
    }
    else
    {
        if (x >= width)
        {
            x = 0;
        }
        else if (x < 0)
        {
            x = width - 1;
        }
        if (y >= height)
        {
            y = 0;
        }
        else if (y < 0)
        {
            y = height - 1;
        }
    }
    for (int i = 0; i < ntail; i++)
    {
        if (tailx[i] == x && taily[i] == y)
        {
            gameover = true;
        }
    }
    if (x == fruitx && y == fruity)
    {
        score += 10;
        fruitx = rand() % width;
        fruity = rand() % height;
        ntail++;
    }
}
int main()
{
    score = 0;
    cout << "Do you want to go throw walls : y/n ? " << endl;
    char tw;
    cin >> tw;
    (tw == 'y') ? throwwalls = true : throwwalls = false;
    system("cls");
    setup();
    while (!gameover)
    {
        draw();
        input();
        logic();
        Sleep(50);
    }
    system("cls");
    cout << "You lost" << endl;
    cout << "Score = " << score << endl;
    return 0;
}
