#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

int main()
{
    bun2dInit(1, 100, 100, 400, 400);
    Pixel textColor = { 255,
                        255,
                        255,
                        255 };

    while (bun2dTick())
    {
        bun2dClear();
        bun2dText("0123456789", 20, 20, textColor);
    }
}