//
// Created by LoscoX on 28/12/2022.
//

#include <ncursesw/ncurses.h>

int main ()
{

    initscr();

    int x,y;
    x=y=0;

    move(y,x);

    printw("Hello world!");


    refresh();

    int c = getch();

    printw("%d", c);

    clear();
    getch();

    endwin();
    return 0;
}