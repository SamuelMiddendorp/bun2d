#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <bun2d.h>

Model *bun2dLoadPngModel(char *adress);
FastModel *bun2dLoadPngModelFast(char *adress);

/// @brief Loads a png image into a model
/// @param adress 
/// @return a pointer to the piece of memory where the model is 
Model *bun2dLoadPngModel(char *adress)
{
    printf("Loading png %s", adress);
    stbi_set_flip_vertically_on_load(1);
    int x, y, n;
    unsigned char *data = stbi_load(adress, &x, &y, &n, 0);
    printf("Loading png, width: %d, height: %d, channels: %d", x, y, n);
    int entries = x * y;
    Model *m = malloc(sizeof(Model));
    m->data = malloc(sizeof(Voxel) * entries);
    m->length = entries;
    int currentEntry = 0;
    for (int i = 0; i < x * n; i += n)
    {
        for (int j = 0; j < y * n; j += n)
        {
            int index = x * j + i;
            m->data[currentEntry].r = data[index];
            m->data[currentEntry].g = data[index + 1];
            m->data[currentEntry].b = data[index + 2];
            // For now always fully opaque
            m->data[currentEntry].a = 255;
            m->data[currentEntry].x = i == 0 ? 0 : i / n;
            m->data[currentEntry].y = j == 0 ? 0 : j / n;
            currentEntry++;
        }
    }
    stbi_image_free(data);
    return m;
}

/// @brief Only for opaque models without empty pixels pixels
/// @param adress
/// @return The model reference that can be passed to render
FastModel *bun2dLoadPngModelFast(char *adress)
{
    stbi_set_flip_vertically_on_load(1);
    int x, y, n;
    unsigned char *data = stbi_load(adress, &x, &y, &n, 0);
    printf("Loading png %s, width: %d, height: %d, channels: %d", adress, x, y, n);
    int entries = x * y;
    FastModel *m = malloc(sizeof(FastModel));
    m->data = malloc(sizeof(Pixel) * entries);
    m->length = entries;
    m->width = x;
    m->height = y;
    int currentEntry = 0;
    for (int i = 0; i < x * n; i += n)
    {
        for (int j = 0; j < y * n; j += n)
        {
            int index = x * i + j;
            m->data[currentEntry].r = data[index];
            m->data[currentEntry].g = data[index + 1];
            m->data[currentEntry].b = data[index + 2];
            m->data[currentEntry].a = n > 3 ? data[index + 3] : 255;
            currentEntry++;
        }
    }
    stbi_image_free(data);
    return m;
}