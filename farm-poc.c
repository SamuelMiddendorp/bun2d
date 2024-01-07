#define BUN2D_IMPLEMENTATION
#include <bun2d.h>

typedef struct
{
    Vec2 position;
    Vec2 velocity;
    int width;
    int height;
} Player;

typedef struct
{
    Pixel color;
    float lifeTime;
    int isGrown;
    int growMultiplier;
} Crop;

typedef struct
{
    Vec2 position;
    int maxCrops;
    Crop *crops;
    int cropSize;
    int currentCrop;
} Farm;

int main()
{
    float speed = 0.2;
    float lightStrength = 1;
    bun2dInit(1, 100, 100, 800, 800);
    Player p = {{0, 0}, {0, 0}, 3, 3};
    Farm f = {{5, 5}, 9, NULL, 5,0};
    Crop currentCrop = {{50,0,0,255}, 50, 0, 35};
    f.crops = calloc(f.maxCrops, sizeof(Crop));
    int placeTimer = 0;
    while (bun2dTick())
    {
        p.velocity.x = 0;
        p.velocity.y = 0;
        bun2dClear();
        if (bun2dKey(KEY_W) > 0)
        {
            p.velocity.y = speed;
        }
        if (bun2dKey(KEY_S) > 0)
        {
            p.velocity.y = -speed;
        }
        if (bun2dKey(KEY_A) > 0)
        {
            p.velocity.x = -speed;
        }
        if (bun2dKey(KEY_D) > 0)
        {
            p.velocity.x = speed;
        }

        if(bun2dKey(KEY_C) == BUN2D_PRESS){
           if(placeTimer > 20 && isPlayerInFarm(&f, &p)){
                placeCrop(&f, currentCrop);
           }
           placeTimer = 0; 
        }
        if(bun2dKey(KEY_UP) == BUN2D_PRESS){
            lightStrength+=0.1;
        }
        if(bun2dKey(KEY_DOWN) == BUN2D_PRESS){
            lightStrength-=0.1;
        }
        
        // Updates
        updateCrops(&f, bun2dGetFrameTime());

        p.position.x += p.velocity.x;
        p.position.y += p.velocity.y;
        bun2dSetLight(p.position.x, p.position.y, lightStrength);
        // Draw farm;
        drawFarm(&f);
        // Draw player;
        bun2dFillRect(p.position.x, p.position.y, p.width, p.height, RED);

        placeTimer++;
    }
}

void placeCrop(Farm *f, Crop c){
    printf("Placing crop");
    if(f->currentCrop >= f->maxCrops){
        f->currentCrop = 0;
    }
    f->crops[f->currentCrop++] = c;
}

void updateCrops(Farm *f, double frameTime){
    for(int i = 0; i < f->maxCrops; i++){
        if(f->crops[i].isGrown){
            continue;
        }
        f->crops[i].lifeTime += frameTime / 1000 * f->crops[i].growMultiplier;
        if(f->crops[i].lifeTime >= 150){
            f->crops[i].isGrown = 1;
            f->crops[i].color.r = 255;
            continue;
        }
        f->crops[i].color.r = f->crops[i].lifeTime;
    }
}
void drawFarm(Farm *f)
{
    int rootCrop = sqrt(f->maxCrops);
    for (int x = 0; x < rootCrop; x++)
    {
        for (int y = 0; y < rootCrop; y++)
        {
            Crop c = f->crops[rootCrop * x + y];
            if(c.color.a == 0){
                bun2dRect(f->position.x + x * f->cropSize, f->position.y + y * f->cropSize, f->cropSize, f->cropSize, RED);
                continue;
            }
            bun2dFillRect(f->position.x + x * f->cropSize, f->position.y + y * f->cropSize, f->cropSize, f->cropSize, c.color);
        }
    }
}

int isPlayerInFarm(Farm* f, Player* p){
     return (
    f->position.x <= p->position.x + p->width &&
    f->position.x + (f->cropSize * 3) >= p->position.x &&
    f->position.y <= p->position.y + p->height &&
    f->position.y + (f->cropSize * 3) >= p->position.y
    );
}
