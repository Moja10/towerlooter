#ifndef CARTOGRAPHER_H_INCLUDED
#define CARTOGRAPHER_H_INCLUDED

#include <stdlib.h>
#include <time.h>
#include "Map.h"

/** \file Cartographer.h

\brief Defines behavior for map generation.

This file contains all the free functions for generating Maps in Towerlooter.
Functions beginning with 'generate' produce output which fills an entire Map.
Functions beginning with 'construct' produce output which make individual rooms inside of a Map.

*/

/** \brief Generates a preset variety of bigroom Maps.

Bigroom is a misnomer, it is a room that takes up the entire Map rather than a subroom of a Map.
This function takes in a type integer which defaults to 0 which determines which kind of bigroom will be generated.
The following types of bigrooms and their corresponding type values are listed below.

- 0:
Room type is randomly chosen among the following types. (Random)
- 1:
Room is entirely empty except for walls along the edges of the Map.
- 2:
Room is entirely empty except for walls along the edges of the Map.
Additionally, there are large, rectangular patches of darkness.
- 3:
Room is rectangular and has two large structures near the middle.
There are niches throughout the walls.
- 4:
Room is shaped like a large butterfly.
- 5:
Room is shaped like an oval.

\param type  The type of bigroom to be generated.
\return Map

 */

Map generate_bigroom_map(int type = 0);

/** \brief Generates a room with all tiles of the same type.

This function generates an entirely blank room where all tiles are identical.
The diggable variable defaults to 1, meaning that the map can be dug through.

\param id    The id of the tiles to fill the room with.
\param diggable  Whether or not the tiles are diggable.
\return Map

*/

Map generate_blank_map(int id, bool diggable = true);

/** \brief Generates a variety of maze maps.

Maze maps are a special kind of Map which consist entirely of one continuous maze.
They have a unified tile type for the walls and another type for the floors.
Using a wall for the floor id will create a sort of inverse-maze.
These mazes can have a specific kind of generation tendency which defaults to inactive.

- 0:
No tendency: the direction of each maze fork is chosen at random (default).
- 1:
Horizontal: the generator attempts to dig horizontally more than usual.
- 2:
Vertical: the generator attempts to dig vertically more than usual.
- 3:
Uncertain: the generator attempts to change direction more than usual.
- 4:
Tunnel-vision: the generator attempts to refuse to change direction more than usual.

\param id The id of the tiles to be used for walls.
\param floor  The id of the tiles to be used for floors.
\param tendency   The directional tendency of the generator.
\param coefficient    The amount which the generator favors its tendency.
\return Map

*/

Map generate_maze_map(int id, int floor, int tendency = 0, int coefficient = 1);

/** \brief Generates a variety of maze rooms.

Maze rooms are single rooms in a Map which consist entirely of a maze.
The size of the room must be specified along with the type of wall and floor desired.
Like the generate_maze_map function, it too has a tendency which defaults to inactive.
The tendencies are identical to the maze Map tendencies.

- 0:
No tendency: the direction of each maze fork is chosen at random (default).
- 1:
Horizontal: the generator attempts to dig horizontally more than usual.
- 2:
Vertical: the generator attempts to dig vertically more than usual.
- 3:
Uncertain: the generator attempts to change direction more than usual.
- 4:
Tunnel-vision: the generator attempts to refuse to change direction more than usual.

\param m    The Map which will contain the room.
\param x1   The smallest x-coordinate of tiles in the room.
\param x2   The greatest x-coordinate of tiles in the room.
\param y1   The smallest y-coordinate of tiles in the room.
\param y2   The greatest y-coordinate of tiles in the room.
\param id   The id of the tiles to be used for walls.
\param floor    The id of the tiles to be used for floors.
\param tendency The directional tendency of the generator.
\param coefficient  The amount which the generator favors its tendency.

*/

void construct_maze_room(Map * m, int x1, int x2, int y1, int y2, int id, int floor, int tendency = 0, int coefficient = 1);

#endif // CARTOGRAPHER_H_INCLUDED
