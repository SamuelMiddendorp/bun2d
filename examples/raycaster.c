#define BUN2D_IMPLEMENTATION
#include <bun2d.h>
#include <stdbool.h>

float vec_mag(Vec2 vec);
void vec_sum(Vec2 *dist, Vec2 a, Vec2 b);
void vec_div(Vec2 *a, float division);
void vec_mul(Vec2 *a, float multi);
Vec2 vec_sub(Vec2 a, Vec2 b);

int main()
{
    int worldSize = 100;
    bool world[100 * 100];
    Vec2 pos = {5, 0};
    // init world
    for (int i = 0; i < worldSize * worldSize; i++)
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

    int rays = 40;
    int maxRayMarch = 50;
    bun2dInit(1, worldSize, worldSize, 1440, 1440);
    while (bun2dTick())
    {
        float radians = 2.5;
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
            world[worldSize * p.x + p.y] = true;
        }

        // March a ray, very naive
        for (int x = 0; x < rays; x++)
        {
            Vec2 headingVec = {cos(radians), sin(radians)};
            radians -= 0.05;
            bool found = false;
            for (int i = 0; i < maxRayMarch; i++)
            {
                Vec2 newHeading;
                newHeading.x = headingVec.x * (i + 1);
                newHeading.y = headingVec.y * (i + 1);
                Vec2 newPos;
                vec_sum(&newPos, pos, newHeading);
                int worldPos = worldSize * (int)newPos.x + (int)newPos.y;
                // Check for uninitialized memory
                if (worldPos > worldSize * worldSize - 1)
                {
                    break;
                }
                if (world[worldPos])
                {
                    // bun2dLine(pos.x, pos.y, newPos.x, newPos.y, GREEN);
                    bun2dFillRect(x + 1, 0, 1, 60 / (i), BLUE);
                    found = true;
                    break;
                }
            }
        }

        // draw the world
        bun2dFillRect(pos.x, pos.y, 5, 5, RED);
        for (int i = 0; i < worldSize; i++)
        {
            for (int j = 0; j < worldSize; j++)
            {
                if (world[worldSize * i + j])
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
