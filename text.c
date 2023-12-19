#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

int main()
{
    bun2dInit(1);

    while (bun2dTick())
    {
        bun2dClear();
        bun2dText("ollttttllloood", 20,20);
    }
}