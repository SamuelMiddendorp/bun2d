#define BUN2D_IMPLEMENTATION 

#include <bun2d.h>


int main()
{
    bun2dInit(0);

    Pixel color = {255,0,0,255};
    while (bun2dTick())
    {
        bun2dClear();

        if(bun2dKey(KEY_W) == 1){
            Point foo = bun2dGetMouse();
            bun2dRect(foo.x, foo.y, 20,20);
        }
    }
}