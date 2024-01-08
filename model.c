#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

int main()
{
    bun2dInit(1, 100, 100, 400, 400);
    Pixel textColor = { 255,
                        255,
                        255,
                        255 };

    Voxel p = {255,10,100,255,0,0};
    Voxel i = {255,10,100,255,1,1};

    Voxel data[2];

    data[0] = p;
    data[1] = i;

    Model* foo = bun2dMakeModel(data, 2);
    while (bun2dTick())
    {
        bun2dClear();
        bun2dDrawModel(foo, 10,10);
        bun2dDrawModel(foo, 20,20);
    }
}