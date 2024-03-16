#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

int main()
{
    bun2dInit(1, 100,100,1000,1000, "rectangle");


    
    while (bun2dTick())
    {
        bun2dClear();
        bun2dFillRectEXP(20,20,20,20,RED);
    }
}
