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
    int value;
} Crop;

typedef struct
{
    Vec2 position;
    int maxCrops;
    Crop *crops;
    int cropSize;
    int currentCrop;
} Farm;

Crop empty = {
    {0,0,0,0},
    0.0,
    0,
    0,
    0
};

int main()
{
    int money = 0;
    float speed = 0.2;
    float lightStrength = 1;
    bun2dInit(1, 100, 100, 800, 800);
    Player p = {{0, 0}, {0, 0}, 3, 3};
    Farm f = {{5, 5}, 9, NULL, 5,0};
    Farm f2 = {{35, 35}, 25, NULL, 5,0};
    Crop currentCrop = {{50,0,0,255}, 50, 0, 35, 5};
    f.crops = calloc(f.maxCrops, sizeof(Crop));
    f2.crops = calloc(f2.maxCrops, sizeof(Crop));
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
           else if(placeTimer > 20 && isPlayerInFarm(&f2, &p)){
                placeCrop(&f2, currentCrop);
           }
           placeTimer = 0; 
        }

        if(bun2dKey(KEY_H) == BUN2D_PRESS){
            if(isPlayerInFarm(&f, &p)){
                money += harvestCrops(&f);
                printf("%i", money);
            }

            if(isPlayerInFarm(&f2, &p)){
                money += harvestCrops(&f2);
                printf("%i", money);
            }
        }

        if(bun2dKey(KEY_UP) == BUN2D_PRESS){
            lightStrength+=0.1;
        }

        if(bun2dKey(KEY_DOWN) == BUN2D_PRESS){
            lightStrength-=0.1;
        }
        
        // Updates
        updateCrops(&f, bun2dGetFrameTime());
        updateCrops(&f2, bun2dGetFrameTime());

        p.position.x += p.velocity.x;
        p.position.y += p.velocity.y;
        //bun2dSetLight(p.position.x, p.position.y, lightStrength);
        // Draw farm;
        drawFarm(&f);
        drawFarm(&f2);
        // Draw player;
        bun2dFillRect(p.position.x, p.position.y, p.width, p.height, RED);

        char buf[20];
        sprintf(buf, "%d", money);
        bun2dText(&buf, 2, 50, WHITE);

        placeTimer++;
    }
}

void placeCrop(Farm *f, Crop c){
    printf("Placing crop");
    for(int i = 0; i < f->maxCrops; i++){
        if(f->crops[i].color.a == 0){
            f->crops[i] = c;
            break;
        }
    }
}

int harvestCrops(Farm *f){
    int value = 0;
    for(int i = 0; i < f->maxCrops; i++){
        if(f->crops[i].isGrown){
            value += f->crops[i].value;
            f->crops[i] = empty;
        }
    }
    return value;
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
