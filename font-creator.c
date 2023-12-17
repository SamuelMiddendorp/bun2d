#define BUN2D_IMPLEMENTATION 

#include <bun2d.h>


int main()
{
    bun2dInit(0);

    Pixel color = {255,0,0,255};
    while (bun2dTick())
    {

        Point foo = bun2dGetMouse();
        if(bun2dKey(KEY_W) == 1){
            bun2dPixel(foo.x, foo.y, color);
        }
        bun2dClear();
    }
}