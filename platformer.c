#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>


typedef struct{
    int x;
    int y;
} Vec2;

typedef struct{
    Vec2 Position;
    Vec2 Dims;
} Platfom;

typedef struct{
    Vec2 Position;
    Vec2 Velocity;
    Vec2 Dims;
} Player;

int main()
{
    bun2dInit(1, 400, 400, 400, 400);
    Pixel textColor = { 255,
                        255,
                        255,
                        255 };

    while (bun2dTick())
    {
        bun2dClear();
    }
}