#include "Map.h"
#include <curses.h>
#include <iostream>
#include <fstream>

using std::vector;

Map::Map()
{
    tiles = vector<vector<Tile> >(21, vector<Tile>(80));
    tiles_tbr = vector<Tile> (0);
    characters = vector<Character *> ();
    _level = 0;
    _type = 0;
    for (int row = 0; row < 21; ++row)
    {
        for (int col = 0; col < 80; ++col)
        {
            Tile t;
            t._x = col;
            t._y = row;
            t.owner = this;
            tiles[row][col] = t;
            tiles[row][col].owner = this;
        }
    }
}

Map::Map(const Map& m)
{
    tiles = vector<vector<Tile> >(21, vector<Tile>(80));
    tiles_tbr = vector<Tile> (0);
    characters = vector<Character *> ();
    _level = m.get_level();
    _type = m.get_type();
    for (int row = 0; row < 21; ++row)
    {
        for (int col = 0; col < 80; ++col)
        {
            tiles[row][col] = m.tiles[row][col];
            tiles[row][col].owner = this;
        }
    }
}

Map::~Map()
{
    for (unsigned int i = 0; i < characters.size(); ++i)
        delete characters[i];
}

Map& Map::operator=(const Map& m)
{
    tiles = vector<vector<Tile> >(21, vector<Tile>(80));
    tiles_tbr = vector<Tile> (0);
    characters = vector<Character *> ();
    _level = m.get_level();
    _type = m.get_type();
    for (int row = 0; row < 21; ++row)
    {
        for (int col = 0; col < 80; ++col)
        {
            tiles[row][col] = m.tiles[row][col];
            tiles[row][col].owner = this;
        }
    }
    return *this;
}

int Map::get_level() const
{
    return _level;
}

int Map::get_type() const
{
    return _type;
}

void Map::render()
{
	/*
	Renders the map to the terminal window. Starts with tiles,
	and places characters and entities on top of them.
	*/

    for(int row = 0; row < 21; ++row)
    {
        for (int col = 0; col < 80; ++col)
        {
            attron(COLOR_PAIR(tiles[row][col].get_color()));
            attron(tiles[row][col].get_effect());
            mvaddch(row + 1, col, tiles[row][col].get_icon());

            attroff(COLOR_PAIR(tiles[row][col].get_color()));
            attroff(tiles[row][col].get_effect());

            if ( !tiles[row][col].lit )
                mvaddch(row + 1, col, ' ') ;
        }
    }
    for(unsigned int c = 0; c < characters.size(); ++c)
    {
        attron(characters[c]->effect);
        mvaddch(characters[c]->y + 1, characters[c]->x, characters[c]->icon);
        attroff(characters[c]->effect);
    }
}

void Map::insert_character(int x, int y, Character * newchar)
{
	/*
	Inserts a new character at location x, y on the map, and adds it to the character array.
	*/

    tiles[y][x].occupant = newchar;
    newchar->x = x;
    newchar->y = y;
    newchar->owner = this;
    characters.push_back(newchar);
}

void Map::tick(int t /* = 1 */)
{
	/*
	Ticks all entities' and characters' timers by one. If a character has
	full tokens, it is called to act.
	*/

    for(unsigned int c = 0; c < characters.size(); ++c)
    {
        Character * current = characters[c];
        current->tokens = current->tokens + t;
        if(current->tokens == current->speed)
        {
            current->tokens = 0;
            current->act();
        }
    }
}

void Map::draw_rect(int x1, int x2, int y1, int y2, int id)
{
	/*
	Draws a rectangular patch of tiles of type id between the coordinates
	(x1, y1) to (x2, y2).
	*/

    if ( x1 > x2 )
        std::swap(x1, x2);
    if ( y1 > y2 )
        std::swap(y1, y2);
    if ( x1 < 0 || x2 > 79 || y1 < 0 || y2 > 20)
        return;
    for(int row = y1; row <= y2; ++row)
    {
        for(int col = x1; col <= x2; ++col)
        {
            tiles[row][col].set_id(id);
        }
    }
}

void Map::draw_hline(int x1, int x2, int y, int id)
{
	/*
	Draws a horizontal line of tiles of type id between
	x1 and x2 on y row.
	*/

    if ( x1 > x2 )
        std::swap(x1, x2);
    if ( x1 < 0 || x2 > 79 || y < 0 || y > 20)
        return;
    for( ; x1 <= x2; ++x1)
    {
        tiles[y][x1].set_id(id);
    }
}


void Map::draw_vline(int y1, int y2, int x, int id)
{
	/*
	Draws a vertical line of tiles of type id between
	y1 and y2 on x column.
	*/

    if ( y1 > y2 )
        std::swap(y1, y2);
    if ( y1 < 0 || y2 > 20 || x < 0 || x > 79)
        return;
    for( ; y1 <= y2; ++y1)
    {
        tiles[y1][x].set_id(id);
    }
}

int Map::draw_fill(int x, int y, int id, int prev_id)
{
    /*
    This function recursively fills an area of tiles of the same type with tiles of -id type,
    similar to a paint bucket. Its return value is equal to the number of tiles filled.
    */

    if ( x < 0 || x > 79 || y < 0 || y > 20)
        return 0;
    if ( prev_id != tiles[y][x].get_id() && prev_id != -1)
        return 0;
    if ( tiles[y][x].get_id() == id)
        return 0;
    prev_id = tiles[y][x].get_id();
    tiles[y][x].set_id(id);
    return 1 + draw_fill(x, y - 1, id, prev_id) +
    draw_fill(x, y + 1, id, prev_id) +
    draw_fill(x - 1, y, id, prev_id) +
    draw_fill(x + 1, y, id, prev_id);
}

void Map::save()
{
    std::ofstream data;
    data.open(_level + ".map");
}
