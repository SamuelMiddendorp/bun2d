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
    Model* foo3 = bun2dLoadModel("bun.csv");
    while (bun2dTick())
    {
        bun2dClear();
        bun2dDrawModel(foo, 40,20);
        bun2dDrawModel(foo3, 20,20);
        bun2dDrawModel(foo3, 0,10);
    }
}

