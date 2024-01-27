#define BUN2D_IMPLEMENTATION
#include <bun2d.h>
#include <stdbool.h>
int main()
{
    bool world[50 * 50];
    Vec2 pos = {5, 5};
    // init world
    for (int i = 0; i < 50 * 50; i++)
    {
        if (rand() % 100 > 98)
        {
            world[i] = true;
        }
        else
        {
            world[i] = false;
        }
    }
    Pixel color = {255, 50, 50, 255};

    bun2dInit(1, 50, 50, 800, 800);
    while (bun2dTick())
    {
        bun2dClear();
        // for (int i = 0; i < rays; i++)
        // {
        //     Vec2 headingVec = {cos(radians), sin(radians)};
        //     headingVec.x *= length;
        //     headingVec.y *= length;
        //     Vec2 target = {headingVec.x + pos.x, headingVec.y + pos.y};
        //     bun2dLine(pos.x, pos.y, target.x, target.y, color);
        //     radians+=0.05;
        // }
        for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            if(world[50 * i + j]){
                bun2dPixel(i,j,color);
            }
        }

        }
    }
}
