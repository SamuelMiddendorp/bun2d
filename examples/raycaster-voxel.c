#define BUN2D_IMPLEMENTATION
#include <bun2d.h>

int toWorldArray(int x, int y, int z);
#define PI 3.14159265358979323846
#define WORLD_DIM 50
#define WORLD_SIZE WORLD_DIM * WORLD_DIM * WORLD_DIM

int main()
{
    const int screenWidth = 50;
    const int screenHeight = 50;
    bool world[WORLD_SIZE];
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        if (rand() % 10000 > 9900)
        {
            world[i] = true;
        }
        else
        {
            world[i] = false;
        }
    }

    bun2dInit(1, screenWidth, screenHeight, 800, 800);

    while (bun2dTick())
    {
        bun2dClear();
        // Cast rays for every pixel on the screen
        for (int x = 0; x < screenWidth; x++)
        {
            for (int y = 0; y < screenHeight; y++)
            {
                int worldDim = toWorldArray(x,y,0);
                if(world[worldDim]){
                    bun2dPixel(x,y,RED);
                }
            }
        }
    }
}
int toWorldArray(int x, int y, int z){
    return (z * WORLD_DIM * WORLD_DIM) + (y * WORLD_DIM) + x;
}
