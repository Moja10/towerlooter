#include <stdlib.h>
#include <curses.h>
#include "TerminalColors.h"

void initialize_colors()
{
    /*
    This function initializes the 64 unique color combinations.
    These colors correspond to only those available on the Windows terminal system.
    */

    if( !has_colors() )
	{
        endwin();
		printf("Your terminal does not support color!\n");
		exit(0);
	}

    start_color();
    use_default_colors();

    for (int i = 0; i < 8; ++i)
    {
        for (int o = 0; o < 8; ++o)
        {
            init_pair(8 * i + o, o, i);
        }
    }
}
