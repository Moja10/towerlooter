#include <iostream>
#include <curses.h>
#include "Map.h"
#include "Cartographer.h"
#include "TerminalColors.h"
#include "Random.h"
#include "Hero.h"

void initialize_curses();
void gameloop();

int main()
{
    initialize_curses();
    gameloop();
    return 0;
}

void initialize_curses()
{
	keypad(initscr(), TRUE);
    noecho();
    cbreak();
    curs_set(0);
    clear();
    initialize_colors();
}

void gameloop()
{
    Map m;
    m = generate_maze_map(20, 1, 3);
    generate_maze_map(1, 20);
    Marauder player;
    m.insert_character(7, 7, &player);
    for(;;)
    {
        m.tick();
        m.render();
        mvprintw(23, 0, "%s the %s", player.name.c_str(), player.class_name.c_str());
        printw(" Str:%d", player.stat_str);
        printw(" Dex:%d", player.stat_dex);
        printw(" Con:%d", player.stat_con);
        printw(" Int:%d", player.stat_int);
        printw(" Wis:%d", player.stat_wis);
        printw(" Cha:%d", player.stat_cha);
    }
}
