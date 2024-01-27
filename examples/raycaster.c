#define BUN2D_IMPLEMENTATION
#include <bun2d.h>
#include <stdbool.h>

float vec_mag(Vec2 vec);
void vec_sum(Vec2* dist, Vec2 a, Vec2 b);
void vec_div(Vec2* a, float division);
void vec_mul(Vec2* a, float multi);
Vec2 vec_sub(Vec2 a, Vec2 b);

int main()
{
    bool world[50 * 50];
    Vec2 pos = {5, 0};
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

    char maxRayMarch = 100;
    bun2dInit(1, 50, 50, 800, 800);
    while (bun2dTick())
    {
        bun2dClear();
        Point p = bun2dGetMouse();
        // for (int i = 0; i < rays; i++)
        // {
        //     Vec2 headingVec = {cos(radians), sin(radians)};
        //     headingVec.x *= length;
        //     headingVec.y *= length;
        //     Vec2 target = {headingVec.x + pos.x, headingVec.y + pos.y};
        //     bun2dLine(pos.x, pos.y, target.x, target.y, color);
        //     radians+=0.05;
        // }

        // March a ray, very naive
        Vec2 headingVec = {p.x - pos.x, p.y - pos.y};
        float magnitude = vec_mag(headingVec);
        vec_div(&headingVec, magnitude);

        bool found = false;
        for(int i = 0; i < maxRayMarch; i++){
            Vec2 newHeading;
            newHeading.x = headingVec.x * (i + 1);
            newHeading.y = headingVec.y * (i + 1);
            Vec2 newPos;
            vec_sum(&newPos, pos, newHeading);
            int worldPos = 50 * (int)newPos.x + (int)newPos.y;
            // Check for uninitialized memory
            if(worldPos > 50 * 50 - 1){
                break;
            }
            if(world[worldPos]){
                bun2dLine(pos.x, pos.y, newPos.x, newPos.y, GREEN);
                found = true;
                break;
            }
        }
        if(!found){
            bun2dLine(pos.x, pos.y, p.x, p.y, RED);
        }

        // draw the world
        for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++){
            if(world[50 * i + j]){
                bun2dPixel(i,j,color);
            }
        }

        }
    }
}

float vec_mag(Vec2 vec){
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

void vec_sum(Vec2* dist, Vec2 a, Vec2 b){
    Vec2 new = {a.x + b.x, a.y + b.y};
    dist->x = new.x;
    dist->y = new.y;

}

void vec_div(Vec2* a, float division){
    Vec2 new = {a->x / division, a->y / division};
    a->x = new.x;
    a->y = new.y;
}

void vec_mul(Vec2* a, float multi){
    Vec2 new = {a->x * multi, a->y * multi};
    a->x = new.x;
    a->y = new.y;
}

Vec2 vec_sub(Vec2 a, Vec2 b){
    Vec2 new = {a.x - b.x, a.y - b.y};
    return new;
}
