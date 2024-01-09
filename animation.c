#define BUN2D_IMPLEMENTATION 
#include <bun2d.h>

int main()
{
    bun2dInit(1, 100, 100, 400, 400);

    int animFrameTime = 500;
    unsigned int currentAnimFrame = 0;
    Model* anim_1 = bun2dLoadModel("anim_1.csv");
    Model* anim_2 = bun2dLoadModel("anim_2.csv");
    Model* frames[2];
    frames[0] = anim_1;
    frames[1] = anim_2;
    float animationTimer = 0;
    while (bun2dTick())
    {

        bun2dClear();
        if(animationTimer > animFrameTime){
            currentAnimFrame = !currentAnimFrame;
            animationTimer = 0;
        }
        bun2dDrawModel(frames[currentAnimFrame],20,0);
        animationTimer += bun2dGetFrameTime();
    }
}