#include "Tile.h"
#include <curses.h>

Tile::Tile()
{
    set_id(0);
    _color = 7;
    _effect = A_NORMAL;
    mapped = false;
    lit = true;
    diggable = true;
    occupant = nullptr;
    feature = nullptr;
    owner = nullptr;
}

Tile::Tile(const Tile& t)
{
    _x = t._x;
    _y = t._y;
    _color = t._color;
    _effect = t._effect;
    mapped = t.mapped;
    lit = t.lit;
    diggable = t.diggable;
    set_id(t._id);
    occupant = nullptr;
    feature = nullptr;
    owner = nullptr;
}

void Tile::operator=(const Tile& t)
{
    this->_x = t._x;
    this->_y = t._y;
    this->_color = t._color;
    this->_effect = t._effect;
    this->mapped = t.mapped;
    this->lit = t.lit;
    this->diggable = t.diggable;
    this->set_id(t._id);
    this->occupant = nullptr;
    this->feature = nullptr;
    this->owner = nullptr;
}

Tile::Tile(int x, int y, Map * o, int id, int color, chtype effect, bool m, bool l, bool d)
{
    _x = x;
    _y = y;
    _id = id;
    _color = color;
    _effect = effect;
    mapped = m;
    lit = l;
    diggable = d;
    occupant = nullptr;
    feature = nullptr;
    owner = o;
}

Tile::~Tile()
{
    delete occupant;
    delete feature;
    //delete owner;  // don't uncomment, literally destroys program
}

int Tile::get_id()
{
    return _id;
}

void Tile::set_id(int id)
{
    _id = id;
    switch(_id)     // setting the id automatically updates the color and icon of the tile
    {

                // WALLS

    case 0:             // dark wall
        _icon = ' ';
        _color = 7;
        break;
    case 1:             // standard wall
        _color = 7;
        break;
    case 2:             // wooden wall
        _color = 4;
        break;
    case 3:             // maze wall
        _color = 7;
        break;
    case 4:             // reinforced wall
        _color = 7;
        break;
    case 5:             // ice wall
        _color = 3;
        break;
                // FLOORS

    case 20:            // standard floor
        _icon = ACS_BULLET;
        _color = 7;
        break;
    case 21:            // wooden
        _icon = ACS_BULLET;
        _color = 4;
        break;
    case 22:            // ice
        _icon = 65786;
        _color = 24;
        break;
    case 23:            // snow
        _icon = 65714;
        _color = 31;
        break;
    default:            // no discernible id (BAD)
        _icon = '?';
    }
}

int Tile::get_color()
{
    return _color;
}

void Tile::set_color(int color)
{
    _color = color;
}

int Tile::get_icon()
{
    if ( is_wall() == 2 )
        return fix_wall();
    return _icon;
}

int Tile::is_wall()
{

    /*
    Returns an integer based on whether or not this tile is a wall, and if so, a rendered one.

    RETURN VALUES
    -------------

    0: Tile is not a wall
    1: Tile is a nonrendered wall
    2: Tile is a rendered wall
    */

    if ( get_id() == 0 )
        return 1;
    if ( get_id() < 20 )
        return 2;
    return 0;
}

Tile Tile::get_adjacent(int dir)
{

    /*
    Returns the the adjacent tile in the direction of the keypad number.
    It returns a pointer to the tile adjacent to this tile in the specified direction
    and nullptr if the direction is invalid (dir must be 1 - 9 inclusive) or the tile
    does not exist (this tile is probably against the edge of the map).
    */

    if ( dir < 1 || dir > 9)
        return Tile();
    int row = 0, col = 0;
    switch ( dir % 3 )
    {
    case 0:
        col = 1;
        break;
    case 1:
        col = -1;
        break;
    }
    switch ( (dir - 1) / 3 )
    {
    case 0:
        row = 1;
        break;
    case 2:
        row = -1;
        break;
    }
    return owner->tiles[_y + row][_x + col];
}

int Tile::fix_wall(int style /* = 0 */)
{
    int up = 1, down = 2, left = 4, right = 8;

    // determine properties of surrounding tiles
    if ( _y == 0 || owner->tiles[_y - 1][_x].is_wall() != 2 )
        up = 0;
    if ( _y == 20 || owner->tiles[_y + 1][_x].is_wall() != 2 )
        down = 0;
    if ( _x == 0 || owner->tiles[_y][_x - 1].is_wall() != 2 )
        left = 0;
    if ( _x == 79 || owner->tiles[_y][_x + 1].is_wall() != 2 )
        right = 0;

    switch(style)
    {
        case 0:         // standard wall
        switch(up + down + left + right)
        {
            case 0:
                return ACS_HLINE;
            case 1:
                return ACS_VLINE;
            case 2:
                return ACS_VLINE;
            case 3:
                return ACS_VLINE;
            case 4:
                return ACS_HLINE;
            case 5:
                return ACS_LRCORNER;
            case 6:
                return ACS_URCORNER;
            case 7:
                return ACS_RTEE;
            case 8:
                return ACS_HLINE;
            case 9:
                return ACS_LLCORNER;
            case 10:
                return ACS_ULCORNER;
            case 11:
                return ACS_LTEE;
            case 12:
                return ACS_HLINE;
            case 13:
                return ACS_BTEE;
            case 14:
                return ACS_TTEE;
            case 15:
                return ACS_PLUS;
            default:
                return ACS_DIAMOND;
        }
        case 1:         // double wall
        switch(up + down + left + right)
        {
            case 0:
                return ACS_DIAMOND;
            case 1:
                return 65744;
            case 2:
                return 65746;
            case 3:
                return 65722;
            case 4:
                return 65741;
            case 5:
                return 65724;
            case 6:
                return 65723;
            case 7:
                return 65721;
            case 8:
                return 65741;
            case 9:
                return 65736;
            case 10:
                return 65737;
            case 11:
                return 65740;
            case 12:
                return 65741;
            case 13:
                return 65738;
            case 14:
                return 65739;
            case 15:
                return 65742;
            default:
                return ACS_DIAMOND;
        }
        case 2:         // block wall
        switch(up + down + left + right)
        {
            case 0:
                return 65755;
            case 1:
                return 65759;
            case 2:
                return 65756;
            case 3:
                return 65755;
            case 4:
                return 65757;
            case 5:
                return 65755;
            case 6:
                return 65755;
            case 7:
                return 65755;
            case 8:
                return 65758;
            case 9:
                return 65755;
            case 10:
                return 65755;
            case 11:
                return 65755;
            case 12:
                return 65755;
            case 13:
                return 65755;
            case 14:
                return 65755;
            case 15:
                return 65755;
            default:
                return 65755;
        }
        case 3:         // standard wall with double horizontal
        switch(up + down + left + right)
        {
            case 0:
                return ACS_DIAMOND;
            case 1:
                return ACS_VLINE;
            case 2:
                return ACS_VLINE;
            case 3:
                return ACS_VLINE;
            case 4:
                return 65741;
            case 5:
                return 65726;
            case 6:
                return 65720;
            case 7:
                return 65717;
            case 8:
                return 65741;
            case 9:
                return 65748;
            case 10:
                return 65749;
            case 11:
                return 65734;
            case 12:
                return 65741;
            case 13:
                return 65743;
            case 14:
                return 65745;
            case 15:
                return 65660;
            default:
                return ACS_DIAMOND;
        }
        case 4:         // standard wall with double vertical
        switch(up + down + left + right)
        {
            case 0:
                return ACS_DIAMOND;
            case 1:
                return 65744;
            case 2:
                return 65746;
            case 3:
                return 65722;
            case 4:
                return ACS_HLINE;
            case 5:
                return 65725;
            case 6:
                return 65719;
            case 7:
                return 65718;
            case 8:
                return ACS_HLINE;
            case 9:
                return 65747;
            case 10:
                return 65750;
            case 11:
                return 65735;
            case 12:
                return ACS_HLINE;
            case 13:
                return 65744;
            case 14:
                return 65746;
            case 15:
                return 65751;
            default:
                return ACS_DIAMOND;
        }
        case 5:         // classic NetHack wall
        switch(up + down + left + right)
        {
            case 0:
                return '-';
            case 1:
                return '|';
            case 2:
                return '|';
            case 3:
                return '|';
            case 4:
                return '-';
            case 5:
                return '-';
            case 6:
                return '-';
            case 7:
                return '|';
            case 8:
                return '-';
            case 9:
                return '-';
            case 10:
                return '-';
            case 11:
                return '|';
            case 12:
                return '-';
            case 13:
                return '-';
            case 14:
                return '-';
            case 15:
                return '-';
            default:
                return '-';
        }
        default:
            return ACS_DIAMOND;
    }
}

void Tile::set_effect(chtype effect)
{
    _effect = effect;
}

chtype Tile::get_effect()
{
    return _effect;
}


