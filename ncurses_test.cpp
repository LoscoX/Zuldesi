//
// Created by LoscoX on 28/12/2022.
//

#include <ncursesw/ncurses.h>

using namespace  std;

int main ()
{

    initscr();

   int height, width, start_y, start_x;
    height = 10;
    width = 20;
    start_y = start_x = 10;

    WINDOW * win = newwin(height, width, start_y, start_x);
    refresh();

    start_color();
    init_pair(5, COLOR_GREEN, COLOR_MAGENTA);
    box(win, 5, 58);
    attron(COLOR_PAIR(5));
    printw( "This Is SPARTA!");
    attroff(COLOR_PAIR(5));
    wrefresh(win);


    int c = getch();

    endwin();

    return 0;
}