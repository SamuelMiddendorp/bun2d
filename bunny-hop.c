#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

typedef struct{
    float x,y,xvel,yvel,xacc,yacc;
} Bun;


int main()
{
    bun2dInit(1, 1000, 1000, 1000, 1000);

    Model* bun = bun2dLoadModel("bun.csv");
    Model* flower = bun2dLoadModel("flower.csv");
    Bun b = {20,0,0,0,0,0};
    bool bunIsOnGround = true;
    while (bun2dTick())
    {
        bun2dClear();
            // Jump bun!
            if(bunIsOnGround){
            b.xacc = 2.0f;
            b.yacc = 5.0f;
            }
        
        // update bun
        b.xvel += b.xacc;
        b.yvel += b.yacc;
        // Apply some gravity and friction
        b.xvel -= 0.01 * b.xvel;
        b.yvel -= 0.1;
        b.x += b.xvel;
        b.y += b.yvel;
        b.xacc = 0;
        b.yacc = 0;

        if(b.y <= 0){
            b.y = 0;
            bunIsOnGround = true;
        }
        else{
            bunIsOnGround = false;
        }
        if(b.x > 1000){
            b.x = 0;
        }
        if(b.x < 0){
            b.x = 999;
        }
        bun2dDrawModel(bun, b.x, b.y, 20);
        bun2dDrawModel(bun, b.x + 100, b.y,1);
        bun2dDrawModel(bun, b.x + 110, b.y,1);
        bun2dDrawModel(bun, b.x + 40, b.y,1);
        bun2dDrawModel(flower, 20,0,10);
    }
}
