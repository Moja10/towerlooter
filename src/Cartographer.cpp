#include "Cartographer.h"
#include <stdlib.h>
#include <time.h>

Map generate_bigroom_map(int type /* = 0 */)
{
    Map m;
    srand(time(NULL));
    switch(type)
    {

    case 0:

        return generate_bigroom_map(1 + rand() % 5);

    case 1:

        // create side walls
        for (int row = 0; row < 21; ++row)
        {
            m.tiles[row][0].set_id(1);
            m.tiles[row][79].set_id(1);
        }

        // create top and bottom walls
        for (int sides = 0; sides < 80; ++sides)
        {
            m.tiles[0][sides].set_id(1);
            m.tiles[20][sides].set_id(1);
        }

        // fill floor
       m.draw_fill(1, 1, 20);

        return m;

    case 2:

        m = generate_bigroom_map(1);

        // fill in darkened areas
        for(int row = 1; row < 7; ++row)
        {
            for (int col = 24; col < 56; ++col)
            {
               m.tiles[row][col].lit = false;
               m.tiles[row + 13][col].lit = false;
            }
        }

        for(int row = 7; row < 14; ++row)
        {
            for(int col = 1; col < 24; ++col)
            {
               m.tiles[row][col].lit = false;
               m.tiles[row][col + 55].lit = false;
            }
        }
        return m;

    case 3:

        // begin with standard walled rectangle
        m = generate_bigroom_map(1);

        // generate niches
        for(int i = 2; i < 36; i += 2)
        {
           m.tiles[1][i].set_id(1);
           m.tiles[1][79 - i].set_id(1);
           m.tiles[19][i].set_id(1);
           m.tiles[19][79 - i].set_id(1);
        }

        // draw inside niches
        {
           m.draw_hline(6, 26, 10, 1);
           m.draw_hline(53, 73, 10, 1);
           m.draw_vline(7, 13, 16, 1);
           m.draw_vline(7, 13, 63, 1);

            for(int o = 6; o < 28; o += 2)
            {
               m.tiles[9][o].set_id(1);
               m.tiles[11][o].set_id(1);
               m.tiles[9][79 - o].set_id(1);
               m.tiles[11][79 - o].set_id(1);
            }
           m.draw_rect(15, 17, 9, 11, 1);
           m.draw_rect(62, 64, 9, 11, 1);
           m.draw_hline(15, 17, 10, 0);
           m.draw_hline(62, 64, 10, 0);
        }

        return m;

    case 4:

        // draw corner horizontal walls
        {
           m.draw_hline(0, 9, 0, 1);
           m.draw_hline(70, 79, 0, 1);
           m.draw_hline(0, 9, 20, 1);
           m.draw_hline(70, 79, 20, 1);
        }

        // draw inner horizontal walls
        for (int o = 0; o < 3; ++o)
        {
           m.draw_hline(10 + o*10, 20 + o*10, 2 + o, 1);
           m.draw_hline(10 + o*10, 20 + o*10, 18 - o, 1);
           m.draw_hline(59 - o*10, 69 - o*10, 2 + o, 1);
           m.draw_hline(59 - o*10, 69 - o*10, 18 - o, 1);
        }

        // draw vertical walls
        {
           m.draw_vline(0, 2, 10, 1);
           m.draw_vline(0, 2, 70, 1);
           m.draw_vline(18, 20, 10, 1);
           m.draw_vline(18, 20, 70, 1);

           m.draw_vline(0, 3, 0, 1);
           m.draw_vline(0, 3, 79, 1);
           m.draw_vline(17, 20, 0, 1);
           m.draw_vline(17, 20, 79, 1);
        }

        // draw diagonal walls
        for (int i = 0; i < 8; ++i)
        {
           m.draw_hline(i + 1, i + 2, i + 3, 1);
           m.draw_hline(i + 1, i + 2, 17 - i, 1);
           m.draw_hline(78 - i, 77 - i, i + 3, 1);
           m.draw_hline(78 - i, 77 - i, 17 - i, 1);
        }

        // fill floors out
        {
           m.draw_fill(1, 1, 20);
        }
        return m;

    case 5:

        // draw quadrant of oval
        {
           m.draw_hline(29, 49, 0, 1);
           m.draw_hline(19, 29, 1, 1);
           m.draw_hline(14, 19, 2, 1);
           m.draw_hline(11, 14, 3, 1);
           m.draw_hline(8, 11, 4, 1);
           m.draw_hline(5, 8, 5, 1);
           m.draw_hline(2, 5, 6, 1);
           m.draw_hline(0, 2, 7, 1);
           m.draw_vline(7, 12, 0, 1);
        }

        // copy quadrant over to other quadrants
        for (int col = 40; col < 80; ++col)
        {
            for (int row = 0; row < 13; ++row)
            {
               m.tiles[row][col].set_id(m.tiles[row][79 - col].get_id());
            }
        }

        for (int col = 0; col < 80; col++)
        {
            for (int row = 13; row < 21; ++row)
            {
               m.tiles[row][col].set_id(m.tiles[20 - row][col].get_id());
            }
        }

       m.draw_fill(10, 10, 20);

        return m;

    default:

        return m;
    }

    return m;
}

Map generate_blank_map(int id, bool diggable /*= true*/)
{
    Map m;
    m.draw_fill(0, 0, id);
    if ( !diggable )
    {
        for(int row = 0; row < 21; ++row)
        {
            for(int col = 0; col < 80; ++col)
            {
               m.tiles[row][col].diggable = false;
            }
        }
    }

    return m;
}

Map generate_maze_map(int id, int wall, int tendency /*= 0*/, int coefficient /*= 1*/)
{
	struct check
	{
		int x = -1;
		int y = -1;
		check * previous = nullptr;
		bool passed = false;
	};

	Map m = generate_blank_map(wall);
	srand(time(NULL));
	int direction = rand() % 4; // 0 = up, 1 = right, 2 = down, 3 = left
	int bump = rand() % 2 + 1; // sometimes bump the maze a square to the right

	if (bump == 1)
        m.draw_vline(0, 20, 79, 0);
    else
        m.draw_vline(0, 20, 0, 0);

	check generated[10][39];
	check * current = &generated[rand() % 10][rand() % 39];
	current->previous = current;
	for(int row = 0; row < 10; ++row)
	{
		for(int col = 0; col < 39; ++col)
		{
			generated[row][col].x = col;
			generated[row][col].y = row;
		}
	}
	while (true)
	{
		current->passed = true;
		int row = current->y;
		int col = current->x;

		m.tiles[row * 2 + 1][col * 2 + bump].set_id(id);

		vector<int> possible = vector<int>(0); // construct list of possible directions to dig maze

		if (row != 0 && generated[row - 1][col].passed == false)
		{
			possible.push_back(int(0));
			if (tendency == 2 || (tendency == 3 && direction % 2 == 1) || (tendency == 4 && direction % 2 == 0))
			{
				for(int i = 0; i < coefficient; ++i)
				{
					possible.push_back(int(0));
				}
			}
		}
		if (col != 38 && generated[row][col + 1].passed == false)
		{
			possible.push_back(int(1));
			if (tendency == 1 || (tendency == 3 && direction % 2 == 0) || (tendency == 4 && direction % 2 == 1))
			{
				for(int i = 0; i < coefficient; ++i)
				{
					possible.push_back(int(1));
				}
			}
		}
		if (row != 9 && generated[row + 1][col].passed == false)
		{
			possible.push_back(int(2));
			if (tendency == 2 || (tendency == 3 && direction % 2 == 1) || (tendency == 4 && direction % 2 == 0))
			{
				for(int i = 0; i < coefficient; ++i)
				{
					possible.push_back(int(2));
				}
			}
		}
		if (col != 0 && generated[row][col - 1].passed == false)
		{
			possible.push_back(int(3));
			if (tendency == 1 || (tendency == 3 && direction % 2 == 0) || (tendency == 4 && direction % 2 == 1))
			{
				for(int i = 0; i < coefficient; ++i)
				{
					possible.push_back(int(3));
				}
			}
		}

		if (possible.size() == 0 && current->previous == current) // stop generation if back to square one
			break;

		if (possible.size() != 0)
		{
			direction = possible[rand() % possible.size()];
			switch(direction)
			{
			case 0:
				m.tiles[row * 2][col * 2 + bump].set_id(id);
				generated[row - 1][col].previous = current;
				current = &generated[row - 1][col];
				break;
			case 1:
				m.tiles[row * 2 + 1][col * 2 + 1 + bump].set_id(id);
				generated[row][col + 1].previous = current;
				current = &generated[row][col + 1];
				break;
			case 2:
				m.tiles[row * 2 + 2][col * 2 + bump].set_id(id);
				generated[row + 1][col].previous = current;
				current = &generated[row + 1][col];
				break;
			case 3:
				m.tiles[row * 2 + 1][col * 2 - 1 + bump].set_id(id);
				generated[row][col - 1].previous = current;
				current = &generated[row][col - 1];
				break;
			default:
				break;
			}
		}
		else
		{
			current = current->previous;
		}
		possible.clear();
	}
	return m;
}

void construct_maze_room(Map * m, int x1, int x2, int y1, int y2, int id, int floor, int tendency /*= 0*/, int coefficient /*= 1*/)
{
	struct check
	{
		int x = -1;
		int y = -1;
		check * previous = nullptr;
		bool passed = false;
	};

	int length = x2 - x1 - 1;
	int height = y2 - y1 - 1;

	length = length / 2;
	height = height / 2;

	if ((x2 - x1) % 2 == 0 || x2 <= x1 || (y2 - y1) % 2 == 0 || y2 <= y1)
		return;

	for(int row = y1; row < y2; ++row)
	{
		for(int col = x1; col < x2; ++col)
		{
			m->tiles[row][col].set_id(id);
		}
	}

	srand(time(NULL));
	int direction = rand() % 4; // 0 = up, 1 = right, 2 = down, 3 = left

	check generated[height][length];
	check * current = &generated[rand() % height][rand() % length];
	current->previous = current;
	for(int row = 0; row < height; ++row)
	{
		for(int col = 0; col < length; ++col)
		{
			generated[row][col].x = col;
			generated[row][col].y = row;
		}
	}
	while (true)
	{
		current->passed = true;
		int row = current->y;
		int col = current->x;
		m->render();
        getch();
		m->tiles[row * 2 + 1 + y1][col * 2 + 1 + x1].set_id(floor);

		vector<int> possible = vector<int>(0); // construct list of possible directions to dig maze

		if (row != 0 && generated[row - 1][col].passed == false)
		{
			possible.push_back(int(0));
			if (tendency == 2 || (tendency == 3 && direction % 2 == 1) || (tendency == 4 && direction % 2 == 0))
			{
				for(int i = 0; i < coefficient; ++i)
				{
					possible.push_back(int(0));
				}
			}
		}
		if (col != length - 1 && generated[row][col + 1].passed == false)
		{
			possible.push_back(int(1));
			if (tendency == 1 || (tendency == 3 && direction % 2 == 0) || (tendency == 4 && direction % 2 == 1))
			{
				for(int i = 0; i < coefficient; ++i)
				{
					possible.push_back(int(1));
				}
			}
		}
		if (row != height - 1 && generated[row + 1][col].passed == false)
		{
			possible.push_back(int(2));
			if (tendency == 2 || (tendency == 3 && direction % 2 == 1) || (tendency == 4 && direction % 2 == 0))
			{
				for(int i = 0; i < coefficient; ++i)
				{
					possible.push_back(int(2));
				}
			}
		}
		if (col != 0 && generated[row][col - 1].passed == false)
		{
			possible.push_back(int(3));
			if (tendency == 1 || (tendency == 3 && direction % 2 == 0) || (tendency == 4 && direction % 2 == 1))
			{
				for(int i = 0; i < coefficient; ++i)
				{
					possible.push_back(int(3));
				}
			}
		}

		if (possible.size() == 0 && current->previous == current) // stop generation if back to square one
			break;

		if (possible.size() != 0)
		{
			direction = possible[rand() % possible.size()];
			switch(direction)
			{
			case 0:
				m->tiles[row * 2 + y1][col * 2 + 1 + x1].set_id(floor);
				generated[row - 1][col].previous = current;
				current = &generated[row - 1][col];
				break;
			case 1:
				m->tiles[row * 2 + 1 + y1][col * 2 + 2 + x1].set_id(floor);
				generated[row][col + 1].previous = current;
				current = &generated[row][col + 1];
				break;
			case 2:
				m->tiles[row * 2 + 2 + y1][col * 2 + 1 + x1].set_id(floor);
				generated[row + 1][col].previous = current;
				current = &generated[row + 1][col];
				break;
			case 3:
				m->tiles[row * 2 + 1 + y1][col * 2 + x1].set_id(floor);
				generated[row][col - 1].previous = current;
				current = &generated[row][col - 1];
				break;
			default:
				break;
			}
		}
		else
		{
			current = current->previous;
		}
		possible.clear();
	}
}
