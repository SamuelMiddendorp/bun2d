#define BUN2D_IMPLEMENTATION
#include <bun2d.h>

typedef struct
{
    Vec2 position;
    Vec2 dims;
} Platform;

typedef struct
{
    Vec2 position;
    Vec2 velocity;
    Vec2 dims;
} Player;

typedef struct
{
    Vec2 position;
} Bullet;

Platform platforms[100];
int currentPlatAmount = 0;

Bullet bullets[100];
int currentBulletAmount = 0;
int currentBulletIndex = 0;

int bulletTimer = 0;

void makePlatform(int posX, int posY, int width, int height);
void fireBullet(int x, int y);

int main()
{
    bun2dInit(1, 100, 100, 1000, 1000);

    Player player = {{5, 0}, {0, 0}, {1, 2}};
    makePlatform(2, 2, 2, 1);

    while (bun2dTick())
    {
        if (bun2dKey(KEY_D) == BUN2D_PRESS)
        {
            player.position.x++;
        }

        if (bun2dKey(KEY_A) == BUN2D_PRESS)
        {
            player.position.x--;
        }

        if (bun2dKey(KEY_W) > 0)
        {
            if(bulletTimer > 5){
                fireBullet(player.position.x, player.position.y);
            }
            bulletTimer = 0;
        }

        bun2dClear();

        // Render platforms;
        for (int i = 0; i < currentPlatAmount; i++)
        {
            Platform p = platforms[i];
            bun2dFillRect(p.position.x, p.position.y, p.dims.x, p.dims.y, RED);
        }

        for (int i = 0; i < currentBulletAmount; i++)
        {
            bullets[i].position.y++;
            Bullet b = bullets[i];
            bun2dCircle(b.position.x, b.position.y, 5, RED);
        }

        bun2dFillRect(player.position.x, player.position.y, player.dims.x, player.dims.y, BLUE);
        bulletTimer++;
    }
}

void makePlatform(int posX, int posY, int width, int height)
{
    Platform p = {{posX, posY}, {width, height}};
    platforms[currentPlatAmount++] = p;
}

void fireBullet(int x, int y)
{
    Bullet b = {{x, y}};
    if (currentBulletAmount == 100)
    {
        if(currentBulletIndex == 100){
            currentBulletIndex = 0;
        }
        bullets[currentBulletIndex++] = b;
    }
    else{
        bullets[currentBulletAmount++] = b;
    }
}
