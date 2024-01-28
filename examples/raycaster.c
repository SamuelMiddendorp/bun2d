#define BUN2D_IMPLEMENTATION
#include <bun2d.h>
#include <stdbool.h>

float vec_mag(Vec2 vec);
void vec_sum(Vec2 *dist, Vec2 a, Vec2 b);
void vec_div(Vec2 *a, float division);
void vec_mul(Vec2 *a, float multi);
Vec2 vec_sub(Vec2 a, Vec2 b);

#define WORLD_SIZE 100
#define PI 3.14159265358979323846
#define RADIANS_END 2.3561944902
#define RADIANS_START 0.436
#define TOTAL_RADIANS RADIANS_END - RADIANS_START

int main()
{
    float RADIANS_STEP = 1.92 / WORLD_SIZE;
    printf("%f \n", RADIANS_START);
    printf("%f \n", TOTAL_RADIANS);
    printf("%f \n", RADIANS_STEP);
    bool world[WORLD_SIZE * WORLD_SIZE];
    Vec2 pos = {5, 0};
    // init world
    for (int i = 0; i < WORLD_SIZE * WORLD_SIZE; i++)
    {
        if (rand() % 1000 > 995)
        {
            world[i] = true;
        }
        else
        {
            world[i] = false;
        }
    }
    Pixel color = {255, 50, 50, 255};

    int maxRayMarch = 50;
    bun2dInit(1, WORLD_SIZE, WORLD_SIZE, 1440, 1440);
    while (bun2dTick())
    {
        bun2dClear();
        Point p = bun2dGetMouse();
        if (bun2dKey(KEY_W) > 0)
        {
            pos.y += 0.1;
        }
        if (bun2dKey(KEY_S) > 0)
        {
            pos.y -= 0.1;
        }
        if (bun2dKey(KEY_D) > 0)
        {
            pos.x += 0.1;
        }
        if (bun2dKey(KEY_A) > 0)
        {
            pos.x -= 0.1;
        }

        if (bun2dKey(KEY_SPACE) > 0){
            world[WORLD_SIZE * p.x + p.y] = true;
        }
        float radians = RADIANS_START;
        // March a ray, very naive
        for (int x = 0; x < WORLD_SIZE; x++)
        {
            Vec2 headingVec = {cos(radians), sin(radians)};
            bool found = false;
            for (int i = 0; i < maxRayMarch; i++)
            {
                Vec2 newHeading;
                newHeading.x = headingVec.x * (i + 1);
                newHeading.y = headingVec.y * (i + 1);
                bun2dLine(pos.x, pos.y, pos.x + newHeading.x, pos.y + newHeading.y, RED);
                Vec2 newPos;
                vec_sum(&newPos, pos, newHeading);
                if(newPos.x > WORLD_SIZE || newPos.x < 0
                    || newPos.y > WORLD_SIZE || newPos.y < 0){
                        break;
                    }
                int worldPos = WORLD_SIZE * (int)newPos.x + (int)newPos.y;
                // Check for uninitialized memory
                if (world[worldPos])
                {
                    // bun2dLine(pos.x, pos.y, newPos.x, newPos.y, GREEN);
                    bun2dFillRect(WORLD_SIZE - x, 0, 1, 50 - i, BLUE);
                    found = true;
                    break;
                }
            }
            radians += RADIANS_STEP;
        }

        // draw the world
        bun2dFillRect(pos.x, pos.y, 1, 1, GREEN);
        for (int i = 0; i < WORLD_SIZE; i++)
        {
            for (int j = 0; j < WORLD_SIZE; j++)
            {
                if (world[WORLD_SIZE * i + j])
                {
                    bun2dPixel(i, j, color);
                }
            }
        }
    }
}

float vec_mag(Vec2 vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

void vec_sum(Vec2 *dist, Vec2 a, Vec2 b)
{
    Vec2 new = {a.x + b.x, a.y + b.y};
    dist->x = new.x;
    dist->y = new.y;
}

void vec_div(Vec2 *a, float division)
{
    if(division == 0){
        return;
    }
    Vec2 new = {a->x / division, a->y / division};
    a->x = new.x;
    a->y = new.y;
}

void vec_mul(Vec2 *a, float multi)
{
    Vec2 new = {a->x * multi, a->y * multi};
    a->x = new.x;
    a->y = new.y;
}

Vec2 vec_sub(Vec2 a, Vec2 b)
{
    Vec2 new = {a.x - b.x, a.y - b.y};
    return new;
}
