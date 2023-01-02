//
// Created by LoscoX on 28/12/2022.
//

#include <ncursesw/ncurses.h>

int main ()
{
    // initializes the screen
    // sets up memory and clears the screen
    initscr();

    // prints a string(const char *) to a window
    printw("Hello world!");

    // refresber the screen to match what's in memory
    refresh();

    // what's for user input, returns in value of that key
    int c = getch();

    printw("%d", c);

    getch();

    endwin();
    // deallocates memory and ends ncurses

    return 0;
}