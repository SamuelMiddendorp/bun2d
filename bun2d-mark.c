#define BUN2D_IMPLEMENTATION
#include <bun2d.h>

#define MAX_BUNS 10000

typedef struct
{
    float x,y,xvel,yvel;
    int w,h;
} Bun;

int main()
{
    int bound = 1000; 
    bun2dInit(0, bound, bound, 2560, 1440);

    Model *bunModel = bun2dLoadModel("bun.csv");

    int bunWidth = 12;
    int bunheight = 8;
    Bun buns[MAX_BUNS];
    for (int i = 0; i < MAX_BUNS; i++)
    {
        buns[i].w = bunWidth;
        buns[i].h = bunheight;
        buns[i].x = 5 + rand() % bound - 20;
        buns[i].y = 5 + rand() % bound - 20;
        buns[i].xvel =  (100.0f - rand () % 200) / 200; 
        buns[i].yvel =  (100.0f - rand () % 200) / 200; 
    }

    int frameTimer = 0;
    while (bun2dTick())
    {

        bun2dClear();
        Point p = bun2dGetMouse();
        bun2dSetLight(p.x, p.y, 100);
        // Update some buns pos;
        for (int i = 0; i < MAX_BUNS; i++)
        {
            Bun b = buns[i];
            if(b.x + b.w >= bound){
                buns[i].xvel = -b.xvel;
                buns[i].x = bound - b.w;
            }
            if(b.x <= 0){
                buns[i].xvel = -b.xvel;
                buns[i].x = 0;
            }
            if(b.y + b.h >= bound){
                buns[i].yvel = -b.yvel;
                buns[i].y = bound - b.h;
            }
            if(b.y <= 0){
                buns[i].yvel = -b.yvel;
                buns[i].y = 0;
            }

            buns[i].x += buns[i].xvel;
            buns[i].y += buns[i].yvel;

        }

        // Draw some buns
        for (int i = 0; i < MAX_BUNS; i++)
        {
            bun2dDrawModel(bunModel, buns[i].x, buns[i].y);
        }
        if(frameTimer > 100){
            printf("frametime: %f ms", bun2dGetFrameTime());
            frameTimer = 0;
        }
        frameTimer++;
    }
}