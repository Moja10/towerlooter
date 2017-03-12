#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

/** \file Random.h

\brief Controls the fate of the player.

This file contains all free functions which are used to generate random numbers.
It includes standard random number generation, dice rolls, and weighted random number generation.
It also allows for the generation of random numbers contained in various distributions.

*/

/** \brief Generates a random integer from 1 to x, inclusive.

This function simulates rolling an x-sided die and returns the result.
All faces are equally weighted.

\param x    The maximum integer returned by the dice roll.
\return int

*/

int rnd(int x);

/** \brief Simulates several throws of a die and returns the sum of results.

This function uses the Dungeons & Dragons style rolling notation.
It rolls an x-sided die n times, and returns the combined sum.
The result is a reasonably normal distribution with a maximum of n * x and minimum of x.

\param n    The number of dice to roll.
\param x    The maximum integer returned by the die.
\return int

*/

int d(int n, int x);

#endif // RANDOM_H_INCLUDED
