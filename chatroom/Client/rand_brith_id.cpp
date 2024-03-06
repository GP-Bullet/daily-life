#include "GP_ONLINE.h"

int rand_brith_id()
{
    int i;
    int j;
    srand((unsigned)time(NULL));

    for (i = 0; i < 10; i++)
    {
	j = (((double)rand() / (double)999999) * 999999 + 100001);
    }
    j = j % 1000000;
    
    return j;
}
