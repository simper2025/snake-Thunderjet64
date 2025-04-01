//This is a framework to allow you to focus on the game logic.
//Most of your code will go in three locations. 
//Function decalrations, game logic in runGame, and the function declarations.

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <ctime>
#include <chrono>

using namespace std;

#define key_UP 72
#define key_DOWN 80
#define key_LEFT 75
#define key_RIGHT 77
#define key_ESCAPE 27

//This is a struct (aka structure) it reduces the number of variables needed.
struct point { int x, y; };

//keypress keeps track of what the last pressed key. It is global, but could be made local.
int keypress = 0;

void runGame();
point keyPressed(point direction);
void gotoxy(int x, int y);
void setcolor(WORD color);
void txtPlot(point item, unsigned char Color);

//Add function declarations here
point moverodent();

int main() {
    srand(time(0));

    //Uncomment the next four lines to see console color options 0-255
    /*for (int i = 0; i < 255; i++) {
        setcolor(i);
        _cprintf("Color option: %i. Hello, world.\n", i);
    }*/

	runGame();
	return 0;
}

void runGame() {

    chrono::time_point<chrono::system_clock> runTime;
    chrono::time_point<chrono::system_clock> currentTime;
    runTime = std::chrono::system_clock::now();
    Sleep(300);


    point playerloc = { 0, 10 };
    point direction = { 1, 0 };
    point rodent = {10, 10};

    vector<point> tail;
    

    int length = 5;

    //Loop to start drawing and playing.
    while (keypress != key_ESCAPE) {
		
        direction = keyPressed(direction);
        
        currentTime = chrono::system_clock::now();

        double elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - runTime).count();
        if (elapsedTime > 0.3 * 1000) {
            runTime = chrono::system_clock::now();

            //Most of your game logic goes here.

            //txtPlot(playerloc, 15);

            tail.push_back(playerloc);

            playerloc.x += direction.x;
            playerloc.y += direction.y;

            if (tail.size() > length)
            {
                point erase = tail[0];
                txtPlot(erase, 15);
                tail.erase(tail.begin() + 0);
            }

            for (int d = 1; d < tail.size() - 1; d++)
            {
                if (playerloc.x == tail[d].x && playerloc.y == tail[d].y)
                {
                    setcolor(15);
                    gotoxy(1, 20);
                    _cprintf("GAME OVER");
                    keypress = key_ESCAPE;
                }
            }

            for (int t = 0; t < tail.size(); t++)
            {
                txtPlot(tail[t], 42);
            }

            txtPlot(rodent, 67);
            txtPlot(playerloc, 31);
            
            setcolor(15);
            gotoxy(1, 21);
            _cprintf("Length: %i", length);

            if (playerloc.x == rodent.x  && playerloc.y == rodent.y)
            {
                length += 1;

                rodent = moverodent();

            }

            if (playerloc.x < 0 || playerloc.x > 19 || playerloc.y < 0 || playerloc.y > 19)
            {
                setcolor(15);
                gotoxy(1, 20);
                _cprintf("GAME OVER");
                keypress = key_ESCAPE;

            }

        }

		Sleep(10);
	}
}

//Put function definitions here.
point moverodent()
{
    srand(time(0));

    point temp;

    temp.x = rand() % 20;
    temp.y = rand() % 20;

    return temp;

}


//These are helper funcitons to capture keyboard and draw to the console.
point keyPressed(point direction) {
    if (_kbhit())
    {
        keypress = _getch();
        switch (keypress)
        {
        case key_LEFT:
            direction = { -1, 0 };
            break;

        case key_RIGHT:
            direction = { 1, 0 };
            break;

        case key_UP:
            direction = { 0, -1 };
            break;

        case key_DOWN:
            direction = { 0, 1 };
            break;

        default:

            break;
        }
    }
    return direction;
}

void txtPlot(point item, unsigned char Color)
{
    setcolor(Color);
    gotoxy(item.x*2, item.y); 
    _cprintf("  ");
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x + 1; coord.Y = y + 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    return;
}

void setcolor(WORD color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    return;
}

