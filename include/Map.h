#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Character.h"
#include "Tile.h"

using std::vector;

class Tile;
//class Character;

class Map
{
    public:
        vector<vector<Tile> > tiles;   // matrix of all tiles in the map
        vector<Tile> tiles_tbr;         // vector of tiles to be rendered upon gameloop, is reset at each loop
        vector<Character *> characters;   // vector of all characters on the map

        Map();
        Map(const Map& m);
        Map& operator=(const Map& m);
        virtual ~Map();

        int get_level() const;
        int get_type() const;

        void render();
        void insert_character(int x, int y, Character * newchar);

        /** \brief Increments every characters' tokens in this map.
         *
         * \param t The number of tokens to increment by. Defaults to 1.
         */

        void tick(int t = 1);
        void draw_rect(int x1, int x2, int y1, int y2, int id);
        void draw_hline(int x1, int x2, int y, int id);
        void draw_vline(int y1, int y2, int x, int id);
        int draw_fill(int x, int y, int id, int prev_id = -1);

        void save();
    protected:
    private:
        int _level, _type;
};

#endif // MAP_H
