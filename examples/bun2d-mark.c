#define BUN2D_IMPLEMENTATION
#include <bun2d.h>
#include <bun2d_image.h>

#define MAX_BUNS 50000

typedef struct
{
    float x,y,xvel,yvel;
    int w,h;
} Bun;

int main()
{
    int bound = 1000; 
    bun2dInit(1, bound, bound, 2560, 1440, "bun2d-mark");

    Model *bunModel = bun2dLoadPngModel("res/kells_rip_small.png");
    FastModel *fastModel = bun2dLoadPngModelFast("res/kells_rip_small.png");

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
    int* bunPositions = malloc(sizeof(float) * MAX_BUNS * 2);
    int frameTimer = 0;
    while (bun2dTick())
    {

        bun2dClear();
        Point p = bun2dGetMouse();
        //bun2dSetLight(p.x, p.y, 100);
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
            bunPositions[i * 2] = buns[i].x;
            bunPositions[i * 2 + 1] = buns[i].y;
            bunPositions[i * 2 + 1] = buns[i].y;
        }

        // Draw some buns
        for(int i = 0; i < MAX_BUNS; i++)
        {
            bun2dDrawModelFast(fastModel, buns[i].x, buns[i].y);
        }
        //bun2dDrawModelBulkFast(fastModel, MAX_BUNS, bunPositions);
        if(frameTimer > 100){
            printf("frametime: %f ms", bun2dGetFrameTime());
            frameTimer = 0;
        }
        frameTimer++;
    }
}