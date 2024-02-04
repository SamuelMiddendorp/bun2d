#define BUN2D_IMPLEMENTATION
#include <bun2d.h>
#include <unistd.h>
#include <pthread.h>

typedef struct
{
    float x, y, z
} Vec3;

void* doRayCast(void *_);
int toWorldArray(int x, int y, int z);
float toRad(float degrees);
float getMag(Vec3 vec);
float getDist3(Vec3 v1, Vec3 v2);

#define PI 3.14159265358979323846
#define WORLD_DIM 200
#define NUM_THREADS 4
#define WORLD_SIZE WORLD_DIM *WORLD_DIM *WORLD_DIM
// Nasty globals for multithreading
// Define a resolution
// Currently not able to run natively with 100 rays;
const int screenWidth = 1280;
const int screenHeight = 720;
unsigned char *world;
Vec3 pos = {0, 0, 0};
// The max steps for the rays, putting a higher value costs a lot as of now
int maxRays = 100;
// Some arbitrairy fov value, I am not smart enough to translate this into a fov in radians or degrees
float fov = 1;

const int threadStep = screenWidth / NUM_THREADS;

int main()
{
    world = malloc(sizeof(unsigned char) * WORLD_SIZE);
    for (int i = 0; i < WORLD_SIZE; i++)
    {
        // Some random positions filled with random colors
        // Can be used later on to actually render the pixel's color
        if (rand() % 1000 > 950)
        {
            world[i] = rand() % 255;
        }
        else
        {
            // We dont do a calloc but it might be faster to generate with a calloc?
            world[i] = 0;
        }
    }

    float speed = 1;
    bun2dInit(1, screenWidth, screenHeight, 2560, 1440);

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
            fov += 0.01;
        }
        if (bun2dKey(KEY_DOWN) > 0)
        {
            fov -= 0.01;
        }
        pthread_t th[NUM_THREADS]; 
        unsigned int* starts = malloc(sizeof(int) * NUM_THREADS);
        for(int i = 0; i < NUM_THREADS; i++){
            starts[i] = i * threadStep;
        }
        for(int i = 0; i < NUM_THREADS; i++){
            pthread_create(&th[i], NULL, doRayCast, (void*)&starts[i]); 
        }
        for(int j = 0; j < NUM_THREADS; j++){
            pthread_join(th[j], NULL); 
        }
    }
}

void* doRayCast(void *begin)
{
    int* start = (int*)begin;
    for (int y = 0; y < screenHeight; y++)
    {
        for (int x = *start; x < (*start + threadStep) ; x++)
        {
            Vec2 uv;
            uv.x = (x - 0.5 * screenWidth) / screenHeight;
            uv.y = (y - 0.5 * screenHeight) / screenHeight;

            Vec3 headingBar;
            headingBar.x = uv.x;
            headingBar.y = uv.y;
            headingBar.z = fov;

            float mag = getMag(headingBar);
            headingBar.x /= mag;
            headingBar.y /= mag;

            Vec3 lastRay;
            for (int r = 0; r < maxRays; r++)
            {
                bool found = false;
                Vec3 heading3 = {headingBar.x * (r + 1), headingBar.y * (r + 1), headingBar.z * (r + 1)};
                Vec3 newWorldPos = {pos.x + heading3.x, pos.y + heading3.y, pos.z + heading3.z};
                if (newWorldPos.x <= 0 || newWorldPos.y <= 0 || newWorldPos.z <= 0)
                {
                    lastRay = newWorldPos;
                    continue;
                }
                int worldDim = toWorldArray(newWorldPos.x, newWorldPos.y, newWorldPos.z);
                if (newWorldPos.x >= WORLD_DIM || newWorldPos.y >= WORLD_DIM || newWorldPos.z >= WORLD_DIM)
                {
                    lastRay = newWorldPos;
                    continue;
                }
                if (world[worldDim] > 0)
                {
                    found = true;
                    Pixel c = RED;
                    c.r = 50;
                    c.b = world[worldDim];
                    c.g = 255 - world[worldDim];
                    if ((int)lastRay.x > (int)newWorldPos.x || (int)lastRay.x < (int)newWorldPos.x)
                    {
                        c.r = c.r / 1.3;
                        c.g = c.g / 1.3;
                        c.b = c.b / 1.3;
                    }
                    bun2dPixel(x, y, c);
                    lastRay = newWorldPos;
                    break;
                }
                lastRay = newWorldPos;
            }
        }
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
    return sqrt(((v2.x - v1.x) * (v2.x - v1.x)) + ((v2.y - v1.y) * (v2.y - v1.y)) + ((v2.z - v1.z) * (v2.z - v1.z)));
}
