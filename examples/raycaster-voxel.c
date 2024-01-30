#define BUN2D_IMPLEMENTATION
#include <bun2d.h>

typedef struct
{
    float x, y, z
} Vec3;

int toWorldArray(int x, int y, int z);
float toRad(float degrees);
float getMag(Vec3 vec);
float getDist3(Vec3 v1, Vec3 v2);

#define PI 3.14159265358979323846
#define WORLD_DIM 50
#define WORLD_SIZE WORLD_DIM *WORLD_DIM *WORLD_DIM

int main()
{
    Vec3 positionsOcc[10] = {
        {0, 0, 1},
        {0, 0, 2},
        {0, 1, 4}
    };
    const int screenWidth = 100;
    const int screenHeight = 100;
    bool world[WORLD_SIZE];
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        // if (rand() % 1000 > 990)
        // {
        // world[i] = true;
        // }
        // else
        // {
        //     world[i] = false;
        // }
        if(i % 10 == 0){
            world[i] = true;
        }
        else{
            world[i] = false;
        }
    }

    Vec3 pos = {0, 0, 0};
    float speed = 0.04;
    bun2dInit(1, screenWidth, screenHeight, 800, 800);
    int maxRays = 100;
    float fov = 1;
    while (bun2dTick())
    {
        bun2dClear();
        if (bun2dKey(KEY_W) > 0)
        {
            pos.z += speed;
        }
        if (bun2dKey(KEY_S) > 0)
        {
            pos.z -= speed;
        }
        if (bun2dKey(KEY_A) > 0)
        {
            pos.x -= speed;
        }
        if (bun2dKey(KEY_D) > 0)
        {
            pos.x += speed;
        }
        if (bun2dKey(KEY_Q) > 0)
        {
            pos.y += speed;
        }
        if (bun2dKey(KEY_E) > 0)
        {
            pos.y -= speed;
        }

        if (bun2dKey(KEY_UP) > 0)
        {
            fov+=0.01;
        }
        if (bun2dKey(KEY_DOWN) > 0)
        {
            fov-=0.01;
        }



        for (int y = 0; y < screenHeight; y++)
        {
            for (int x = 0; x < screenWidth; x++)
            {
                Vec2 uv;
                uv.x = ((float)x - 0.5*screenWidth) / screenHeight;
                uv.y = ((float)y - 0.5*screenHeight) / screenHeight;
                //printf("%f, %f\n", uv.x, uv.y);

                // Cast ray
                // _ and y
                // Vec2 headingY = {cos(radY), sin(radY)};
                // // x and z
                // Vec2 headingX = {cos(radX), sin(radX)};
                Vec3 headingBar;
                headingBar.x = uv.x;
                headingBar.y = uv.y;
                headingBar.z = fov;

                float mag = getMag(headingBar);
                //printf("%f", mag);
                headingBar.x /= mag;
                headingBar.y /= mag;
                headingBar.z /= mag;
                // Calculate heading vector;

                // Vec3 newHeading;
                // newHeading.x = headingBar.x - pos.x;
                // newHeading.y = headingBar.y - pos.y;
                // newHeading.z = headingBar.z - pos.z;

                // float mag2 = getMag(newHeading);

                // newHeading.x /= mag2;
                // newHeading.y /= mag2;
                // newHeading.z /= mag2;
                // printf("%f, %f, %f \n", newHeading.x, newHeading.y, newHeading.z);
                for (int r = 0; r < maxRays; r++)
                {
                    bool found = false;
                    Vec3 heading3 = {headingBar.x * (r / 5 + 1), headingBar.y * (r / 5 + 1), headingBar.z * (r / 5 + 1)};
                    Vec3 newWorldPos = {pos.x + heading3.x, pos.y + heading3.y, pos.z + heading3.z};
                    //printf("ray pos new: %f, %f, %f", newWorldPos.x, newWorldPos.y, newWorldPos.z);
                    // for (int v = 0; v < 10; v++)
                    // {
                    //     Vec3 point = positionsOcc[v];
                    //     // if ((int)newWorldPos.x == (int)point.x && (int)newWorldPos.y == (int)point.y && (int)newWorldPos.z == (int)point.z)
                    //     // {
                    //         //printf("RAY HIT! ray x:%f ray y:%f", uv.x, uv.y);
                    //         float dist = getDist3(point, newWorldPos);
                    //         if(dist < 0){
                    //             break;
                    //         }
                    //         if(dist < 0.5){
                    //         found = true;
                    //         Pixel c = RED;
                    //         c.r = c.r * (1 - dist);
                    //         bun2dPixel(x, y, c);
                    //         break;
                    //         }
                    //     // }
                    // }
                    if(newWorldPos.x < 0 || newWorldPos.y < 0 || newWorldPos.z < 0){
                        break;
                    }
                    int worldDim = toWorldArray(newWorldPos.x, newWorldPos.y, newWorldPos.z);
                    if (newWorldPos.x > WORLD_DIM || newWorldPos.y > WORLD_DIM || newWorldPos.z > WORLD_DIM ){
                        break;
                    }
                    if (world[worldDim])
                    {
                        found = true;
                        Pixel c = RED;
                        c.r = c.r / (r + 1);
                        bun2dPixel(x, y, c);
                        break;
                    }
                    // printf("[%f,%f,%f]\n", newWorldPos.x, newWorldPos.y, newWorldPos.z);
                    // break;
                    if(found){
                        break;
                    }
                }
                // Debug
                // bun2dLine(screenWidth / 2, screenHeight / 2, pos.x + headingX.y * 10, pos.y + headingY.x * 10, BLUE);
            }
        }
        //sleep(1);
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

float getMag(Vec3 vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float getDist3(Vec3 v1, Vec3 v2)
{
    return  sqrt( ((v2.x - v1.x) * (v2.x - v1.x)) + ((v2.y - v1.y) * (v2.y - v1.y)) + ((v2.z - v1.z) * (v2.z - v1.z)));
}
