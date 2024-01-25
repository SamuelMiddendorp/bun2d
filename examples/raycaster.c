#define BUN2D_IMPLEMENTATION
#include <bun2d.h>
#include <stdbool.h>
int main()
{
    unsigned short resX = 500;
    unsigned short resY = 500;
    bool world[20 * 20];
    Vec2 pos = {5, 5};
    // init world
    for (int i = 0; i < 20 * 20; i++)
    {
        if (i % 2 == 0)
        {
            world[i] = true;
        }
        else
        {
            world[i] = false;
        }
    }
    float radians = 0;
    Pixel color = {255, 100, 100, 255};

    bun2dInit(1, resX, resY, 800, 800);
    int rays = 50;
    int length = 50;
    while (bun2dTick())
    {
        bun2dClear();
        if(bun2dKey(KEY_D) > 1){
            pos.x+=1;
        }
        if(bun2dKey(KEY_A) > 1){
            pos.x-=1;
        }
        for (int i = 0; i < rays; i++)
        {
            Vec2 headingVec = {cos(radians), sin(radians)};
            headingVec.x *= length;
            headingVec.y *= length;
            Vec2 target = {headingVec.x + pos.x, headingVec.y + pos.y};
            bun2dLine(pos.x, pos.y, target.x, target.y, color);
            radians+=0.05;
        }
        radians = 0;
        // for (unsigned short i = 0; i < resX; i++)
        // {

        //     for (unsigned short j = 0; j < resY; j++)
        //     {
        //         if(i < 20 && j < 20){
        //             if(world[20 * i + j]){
        //                 Pixel p = {255,100,100,255};
        //                 bun2dPixel(i,j,p);
        //             }
        //         }
        //     }
        // }
    }
}
