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
void updateGamestate();

int main()
{
    float speed = 0.5;
    bun2dInit(1, 100, 100, 1000, 1000);

    Player player = {{5, 0}, {0, 0}, {1, 2}};
    makePlatform(5, 5, 5, 3);
    makePlatform(5, 10, 5, 3);
    makePlatform(5, 15, 5, 3);
    makePlatform(7, 11, 5, 3);
    makePlatform(12, 12, 5, 3);

    while (bun2dTick())
    {
        bun2dClear();
        if (bun2dKey(KEY_D) > 0)
        {
            player.velocity.x+=speed;
        }

        if (bun2dKey(KEY_A) > 0)
        {
            player.velocity.x-=speed;
        }

        if (bun2dKey(KEY_W) > 0)
        {
            if (bulletTimer > 5)
            {
                fireBullet(player.position.x, player.position.y);
            }
            bulletTimer = 0;
        }
        player.position.x += player.velocity.x;
        player.position.y += player.velocity.y;

        player.velocity.x = 0;
        player.velocity.y = 0;

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
            bun2dFillRect(b.position.x, b.position.y, 1, 1, RED);
        }
        updateGamestate();

        bun2dFillRect(player.position.x, player.position.y, player.dims.x, player.dims.y, BLUE);
        bulletTimer++;
    }
    return 0;
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
        if (currentBulletIndex == 100)
        {
            currentBulletIndex = 0;
        }
        bullets[currentBulletIndex++] = b;
    }
    else
    {
        bullets[currentBulletAmount++] = b;
    }
}

void updateGamestate()
{
    for(int i = 0; i < currentPlatAmount; i++){
        for(int j = 0; j < currentBulletAmount; j++){
            Platform p = platforms[i];
            Bullet b = bullets[j];
            if(b.position.x >= p.position.x
            && b.position.x <= p.position.x + p.dims.x
            && b.position.y >= p.position.y
            && b.position.y <= p.position.y + p.dims.y)
            {
                Platform newPlat = {{rand() % 100, rand() % 100 + 5}, {5,3}};
                platforms[i] = newPlat;
            }
        }
    }
}
