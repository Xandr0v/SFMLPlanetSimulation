#include "functions.h"







int hash(int n)
{
	int a = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    a += rand();
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a % n;
}



//double pythagor(Vector2d vec)
//{
//    return sqrtf(pow(vec.x, 2) + pow(vec.y, 2));
//}






