#ifndef TILE_H
#define TILE_H

#include "Inventory.h"
#include "Character.h"
#include "Entity.h"
#include "Map.h"
#include <curses.h>

class Character;
class Map;

class Tile
{
    public:

        short _x, _y;

        Inventory inv;
        Character * occupant;
        Entity * feature;
        Map * owner;

        bool mapped, lit, diggable;

        Tile();
        Tile(const Tile& t);
        void operator=(const Tile& t);
        Tile(int x, int y, Map * o, int id = 0, int color = 7, chtype effect = A_NORMAL, bool mapped = false, bool lit = true, bool diggable = true);
        virtual ~Tile();

        int get_id();
        void set_id(int id);
        int get_color();
        void set_color(int color);
        int get_icon();
        void set_effect(chtype effect);
        chtype get_effect();
        int is_wall();
        Tile get_adjacent(int dir);
        int fix_wall(int style = 0);

    protected:

    private:

        unsigned int _id, _color, _icon;
        chtype _effect;

};

#endif // TILE_H
