//
// Created by LoscoX on 28/12/2022.
//

#include <ncurses>
#include <cstdio>
using namespace std;

int main (int argc, char ** argv)
{
    // initializes the screen
    // sets up memory and clears the screen
    initscr();

    int x, y;
    x = y= 10;

    // moves the cursor to the specified location
    move(y, x);

    // prints a string(const char *) to a window
    printw("Hello world!");

    // refresber tbe screen to match what's in memory
    refresh();

    // what's for user input, returns in value of that key
    int c = getch();

    printw("%d", c);

    getch();

    // clears the screen
    clear();

    endwin();
    // deallocates memory and ends ncurses

    return 0;
}