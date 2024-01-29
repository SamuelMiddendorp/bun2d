#define BUN2D_IMPLEMENTATION
#include <bun2d.h>

int toWorldArray(int x, int y, int z);
float toRad(float degrees);

typedef struct
{
    float x, y, z
} Vec3;

#define PI 3.14159265358979323846
#define WORLD_DIM 10
#define WORLD_SIZE WORLD_DIM *WORLD_DIM *WORLD_DIM

int main()
{
    const int screenWidth = 50;
    const int screenHeight = 50;
    bool world[WORLD_SIZE];
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        if (rand() % 1000 > 900)
        {
            world[i] = true;
        }
        else
        {
            world[i] = false;
        }
    }

    Vec3 pos = {0, 0, 5};
    bun2dInit(1, screenWidth, screenHeight, 800, 800);
    int maxRays = 50;
    while (bun2dTick())
    {
        float fov = toRad(120);
        float radStep = fov / screenWidth;

        bun2dClear();
        if(bun2dKey(KEY_W) > 0){
            pos.z-=0.1;
        }
        if(bun2dKey(KEY_S) > 0){
            pos.z+=0.1;
        }
        if(bun2dKey(KEY_A) > 0){
            pos.x+=0.01;
        }
        if(bun2dKey(KEY_D) > 0){
            pos.x-=0.01;
        }
        // Cast rays for every pixel on the screen
        float radY = toRad(120);
        for (int y = 0; y < screenHeight; y++)
        {
            float radX = toRad(120);
            for (int x = 0; x < screenWidth; x++)
            {
                // Cast ray
                // _ and y
                Vec2 headingY = {cos(radY), sin(radY)};
                // x and z
                Vec2 headingX = {cos(radX), sin(radX)};

                for (int r = 0; r < maxRays; r++)
                {
                    Vec3 heading3 = {headingY.x * (r + 1), headingY.y * (r + 1), headingX.y * (r + 1)};
                    Vec3 newWorldPos = {pos.x + heading3.x, pos.y + heading3.y, pos.z + heading3.z};
                    int worldDim = toWorldArray(newWorldPos.x, newWorldPos.y, newWorldPos.z);
                    if (newWorldPos.x > WORLD_DIM || newWorldPos.y > WORLD_DIM || newWorldPos.z > WORLD_DIM ){
                        break;
                    }
                    if (world[worldDim])
                    {
                        Pixel c = RED;
                        c.r = c.r / (r + 1);
                        bun2dPixel(screenWidth - x, screenHeight - y, c);
                        break;
                    }
                }
                // Debug
                // bun2dLine(screenWidth / 2, screenHeight / 2, pos.x + headingX.y * 10, pos.y + headingY.x * 10, BLUE);
                radX += radStep;
            }
            radY += radStep;
        }
    }
}
int toWorldArray(int x, int y, int z)
{
    return (z * WORLD_DIM * WORLD_DIM) + (y * WORLD_DIM) + x;
}

float toRad(float degrees)
{
    return PI * degrees / 180;
}
