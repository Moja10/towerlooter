#include <random>
#include <time.h>
#include <stdlib.h>
#include <string>

int rnd(int x)
{
    if (x <= 0)
    {
        // impossible rnd attempted
        return 1;
    }
    srand(time(NULL));
    return (rand() % x + 1);
}

int d(int n, int x)
{
    if (x < 0 || n < 0 || (x == 0 && n != 0))
    {
        return 1;
    }
    int result = 0;
    srand(time(NULL));
    while (n--) result += rnd(x);
    return result;
}
