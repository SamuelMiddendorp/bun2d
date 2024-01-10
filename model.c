#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

int main()
{
    bun2dInit(1, 200, 200, 800, 800);

    Voxel p = {255,10,100,255,0,0};
    Voxel i = {255,10,100,255,1,1};

    Voxel data[2];

    data[0] = p;
    data[1] = i;

    Model* fooInternal = bun2dMakeModel(data, 2);
    Model* fooCsv = bun2dLoadModel("bun.csv");
    Model* fooPng = bun2dLoadPngModel("bun.png");
    while (bun2dTick())
    {
        bun2dClear();
        bun2dDrawModel(fooInternal, 40,20,1);
        bun2dDrawModel(fooCsv, 0,10,1);
        bun2dDrawModel(fooPng, 10,10,1);
    }
}

