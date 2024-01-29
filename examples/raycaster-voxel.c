#define BUN2D_IMPLEMENTATION
#include <bun2d.h>

typedef struct
{
    float x, y, z
} Vec3;

int toWorldArray(int x, int y, int z);
float toRad(float degrees);
float getMag(Vec3 vec);


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
        if (rand() % 1000 > 950)
        {
            world[i] = true;
        }
        else
        {
            world[i] = false;
        }
    }

    Vec3 pos = {0, 0, 0};
    bun2dInit(1, screenWidth, screenHeight, 800, 800);
    int maxRays = 100;
    while (bun2dTick())
    {
        bun2dClear();
        if(bun2dKey(KEY_W) > 0){
            pos.z-=0.01;
        }
        if(bun2dKey(KEY_S) > 0){
            pos.z+=0.01;
        }
        if(bun2dKey(KEY_A) > 0){
            pos.x+=0.01;
        }
        if(bun2dKey(KEY_D) > 0){
            pos.x-=0.01;
        }
        if(bun2dKey(KEY_Q) > 0){
            pos.y+=0.01;
        }
        if(bun2dKey(KEY_E) > 0){
            pos.y-=0.01;
        }

        for (int y = 0; y < screenHeight; y++)
        {
            for (int x = 0; x < screenWidth; x++)
            {
                Vec2 uv;
                uv.x = (x * 0.5 - screenWidth) / screenWidth;
                uv.y = (y * 0.5 - screenHeight) / screenHeight;


                // Cast ray
                // _ and y
                // Vec2 headingY = {cos(radY), sin(radY)};
                // // x and z
                // Vec2 headingX = {cos(radX), sin(radX)};
                Vec3 headingBar;
                headingBar.x = uv.x;
                headingBar.y = uv.y;
                headingBar.z = 1;

                float mag = getMag(headingBar);

                headingBar.x /= mag;
                headingBar.y /= mag;
                headingBar.z /= mag;
                // Calculate heading vector;

                Vec3 newHeading;
                newHeading.x = headingBar.x - pos.x;
                newHeading.y = headingBar.y - pos.y;
                newHeading.z = headingBar.z - pos.z;

                float mag2 = getMag(newHeading);

                newHeading.x /= mag2;
                newHeading.y /= mag2;
                newHeading.z /= mag2;


                for (int r = 0; r < maxRays; r++)
                {
                    Vec3 heading3 = {newHeading.x * (r + 1), newHeading.y * (r + 1), newHeading.z * (r + 1)};
                    Vec3 newWorldPos = {pos.x + heading3.x, pos.y + heading3.y, pos.z + heading3.z};
                    int worldDim = toWorldArray(newWorldPos.x, newWorldPos.y, newWorldPos.z);
                    if (newWorldPos.x > WORLD_DIM || newWorldPos.y > WORLD_DIM || newWorldPos.z > WORLD_DIM ){
                        break;
                    }
                    if (world[worldDim])
                    {
                        Pixel c = RED;
                        c.r = c.r / (r + 1);
                        bun2dPixel(x, y, c);
                        break;
                    }
                    // printf("[%f,%f,%f]\n", newWorldPos.x, newWorldPos.y, newWorldPos.z);
                    // break;
                }
                // Debug
                // bun2dLine(screenWidth / 2, screenHeight / 2, pos.x + headingX.y * 10, pos.y + headingY.x * 10, BLUE);
            }
        }
        // break;
    }
}
int toWorldArray(int x, int y, int z)
{
    return (WORLD_DIM * WORLD_DIM * z) + (WORLD_DIM * y) + x;
}

float toRad(float degrees)
{
    return PI * degrees / 180;
}

float getMag(Vec3 vec){
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}
