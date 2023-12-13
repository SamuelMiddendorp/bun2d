
#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

int main()
{
    bun2dInit(0);

    while (bun2dTick())
    {
        bun2dText("ollttttlllooo", 20,20);
    }
}