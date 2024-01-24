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
    Vec2 acceleration;
    Vec2 dims;
} Player;

typedef struct
{
    Vec2 position;
    Vec2 velocity;
} Bullet;

typedef struct{
    Vec2 position;
    Vec2 velocity;
    int lifetime;
} Particle;

Platform platforms[100];
int currentPlatAmount = 0;

Bullet bullets[1000];
int currentBulletAmount = 0;
int currentBulletIndex = 0;

Particle particles[100];
int currentParticleAmount = 0;
int currentParticleIndex = 0;
float particleSpeed = 0.3;
float particleLifeSpan = 60;

int bulletTimer = 0;

void makePlatform(int posX, int posY, int width, int height);
void fireBullet(int x, int y, float velX, float velY);
void updateGamestate();
void spawnDestructionParticles(int x, int y);
void spawnBullets(int x, int y);
void spawnParticle(int x, int y, float velX, float velY);

int main()
{
    float speed = 0.4;
    float friction = 0.6;
    bun2dInit(1, 200, 200, 1000, 1000);

    Player player = {{5, 0}, {0, 0}, {0, 0}, {1, 2}};
    makePlatform(5, 5, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 45, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 5, 5, 3);
    makePlatform(5, 5, 5, 3);
    makePlatform(5, 5, 5, 3);
    makePlatform(5, 5, 5, 3);
    makePlatform(5, 5, 5, 3);
    makePlatform(5, 5, 5, 3);
    makePlatform(5, 5, 5, 3);
    makePlatform(5, 5, 5, 3);
    makePlatform(5, 5, 5, 3);
    makePlatform(5, 5, 5, 3);
    makePlatform(5, 5, 5, 3);
    makePlatform(5, 5, 5, 3);
    makePlatform(5, 5, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 45, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 45, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 45, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 45, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 45, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 45, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 45, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 45, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 45, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 45, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 45, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 45, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 20, 5, 3);
    makePlatform(5, 45, 5, 3);
    makePlatform(5, 20, 5, 3);
    int frameTimer = 0;
    while (bun2dTick())
    {
        bun2dClear();
        if (bun2dKey(KEY_D) > 0)
        {
            player.acceleration.x+=speed;
        }

        if (bun2dKey(KEY_A) > 0)
        {
            player.acceleration.x-=speed;
        }

        if (bun2dKey(KEY_W) > 0)
        {
            if (bulletTimer > 1)
            {
                fireBullet(player.position.x, player.position.y, 0, 1);
                bulletTimer = 0;
            }
        }
        player.velocity.x += player.acceleration.x;
        player.velocity.y += player.acceleration.y;

        player.position.x += player.velocity.x;
        player.position.y += player.velocity.y;

        player.velocity.x *= friction;
        player.velocity.y *= friction;
        player.acceleration.x = 0;
        player.acceleration.y = 0;
        if(frameTimer > 100){
            printf("frametime: %f ms", bun2dGetFrameTime());
            frameTimer = 0;
        }
        // Render platforms;
        for (int i = 0; i < currentPlatAmount; i++)
        {
            Platform p = platforms[i];
            bun2dFillRect(p.position.x, p.position.y, p.dims.x, p.dims.y, RED);
        }

        for (int i = 0; i < currentBulletAmount; i++)
        {
            Bullet b = bullets[i];
            bullets[i].position.x += b.velocity.x;
            bullets[i].position.y += b.velocity.y;
            bun2dFillRect(b.position.x, b.position.y, 1, 1, RED);
        }

        for (int i = 0; i < currentParticleAmount; i++)
        {
            Particle p = particles[i];
            if(p.lifetime == 0)
            {
                continue;
            }
            particles[i].position.x += p.velocity.x;
            particles[i].position.y += p.velocity.y;
            bun2dFillRect(p.position.x, p.position.y, 1, 1, WHITE);
            particles[i].lifetime--;
        }
        updateGamestate();

        bun2dFillRect(player.position.x, player.position.y, player.dims.x, player.dims.y, BLUE);
        bulletTimer++;
        frameTimer++;
    }
    return 0;
}

void makePlatform(int posX, int posY, int width, int height)
{
    Platform p = {{posX, posY}, {width, height}};
    platforms[currentPlatAmount++] = p;
}

void fireBullet(int x, int y, float velX, float velY)
{
    Bullet b = {{x, y}, {velX, velY}};
    if (currentBulletAmount == 1000)
    {
        if (currentBulletIndex == 1000)
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
                Platform newPlat = {{rand() % 200, rand() % 200 + 15}, {5,3}};
                spawnDestructionParticles(b.position.x, b.position.y);
                //spawnBullets(b.position.x, b.position.y);
                platforms[i] = newPlat;
            }
        }
    }
}

void spawnBullets(int x, int y){
    fireBullet(x,y,particleSpeed,particleSpeed);
    fireBullet(x,y,particleSpeed,-particleSpeed);
    fireBullet(x,y,-particleSpeed,particleSpeed);
    fireBullet(x,y,-particleSpeed,-particleSpeed);
}

void spawnDestructionParticles(int x, int y){
    spawnParticle(x,y,particleSpeed,particleSpeed);
    spawnParticle(x,y,particleSpeed,-particleSpeed);
    spawnParticle(x,y,-particleSpeed,particleSpeed);
    spawnParticle(x,y,-particleSpeed,-particleSpeed);
}

void spawnParticle(int x, int y, float velX, float velY){
    Particle p = {{x, y}, {velX, velY}, particleLifeSpan};
    if (currentParticleAmount == 100)
    {
        if (currentParticleIndex == 100)
        {
            currentParticleIndex = 0;
        }
        particles[currentParticleIndex++] = p;
    }
    else
    {
        particles[currentParticleAmount++] = p;
    }
}
