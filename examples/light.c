#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

int main()
{
    bun2dInit(1, 50, 50, 800, 800);
    while (bun2dTick())
    {
        bun2dClear();
        Point p = bun2dGetMouse();
        bun2dSetLight(p.x,p.y,1);
        bun2dText("ollttttllloood", 20, 20, RED);
    }
}