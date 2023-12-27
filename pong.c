#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

int main()
{
    printf("Pong!");
    bun2dInit(1, 400, 400, 400, 400);
    while (bun2dTick())
    {
        bun2dClear();
    }
}