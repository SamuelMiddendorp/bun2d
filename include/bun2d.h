#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define BUN2D_PRESS 1
#define BUN2D_HOLD 2
#define BUN2D_RELEASE 0

#define KEY_SPACE 32
#define KEY_APOSTROPHE 39
#define KEY_COMMA 44
#define KEY_MINUS 45
#define KEY_PERIOD 46
#define KEY_SLASH 47
#define KEY_0 48
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53
#define KEY_6 54
#define KEY_7 55
#define KEY_8 56
#define KEY_9 57
#define KEY_SEMICOLON 59
#define KEY_EQUAL 61
#define KEY_A 65
#define KEY_B 66
#define KEY_C 67
#define KEY_D 68
#define KEY_E 69
#define KEY_F 70
#define KEY_G 71
#define KEY_H 72
#define KEY_I 73
#define KEY_J 74
#define KEY_K 75
#define KEY_L 76
#define KEY_M 77
#define KEY_N 78
#define KEY_O 79
#define KEY_P 80
#define KEY_Q 81
#define KEY_R 82
#define KEY_S 83
#define KEY_T 84
#define KEY_U 85
#define KEY_V 86
#define KEY_W 87
#define KEY_X 88
#define KEY_Y 89
#define KEY_Z 90
#define KEY_LEFT_BRACKET 91
#define KEY_BACKSLASH 92
#define KEY_RIGHT_BRACKET 93
#define KEY_GRAVE_ACCENT 96
#define KEY_WORLD_1 161
#define KEY_WORLD_2 162
#define KEY_ESCAPE 256
#define KEY_ENTER 257
#define KEY_TAB 258
#define KEY_BACKSPACE 259
#define KEY_INSERT 260
#define KEY_DELETE 261
#define KEY_RIGHT 262
#define KEY_LEFT 263
#define KEY_DOWN 264
#define KEY_UP 265
#define KEY_PAGE_UP 266
#define KEY_PAGE_DOWN 267
#define KEY_HOME 268
#define KEY_END 269
#define KEY_CAPS_LOCK 280
#define KEY_SCROLL_LOCK 281
#define KEY_NUM_LOCK 282
#define KEY_PRINT_SCREEN 283
#define KEY_PAUSE 284
#define KEY_F1 290
#define KEY_F2 291
#define KEY_F3 292
#define KEY_F4 293
#define KEY_F5 294
#define KEY_F6 295
#define KEY_F7 296
#define KEY_F8 297
#define KEY_F9 298
#define KEY_F10 299
#define KEY_F11 300
#define KEY_F12 301
#define KEY_F13 302
#define KEY_F14 303
#define KEY_F15 304
#define KEY_F16 305
#define KEY_F17 306
#define KEY_F18 307
#define KEY_F19 308
#define KEY_F20 309
#define KEY_F21 310
#define KEY_F22 311
#define KEY_F23 312
#define KEY_F24 313
#define KEY_F25 314
#define KEY_KP_0 320
#define KEY_KP_1 321
#define KEY_KP_2 322
#define KEY_KP_3 323
#define KEY_KP_4 324
#define KEY_KP_5 325
#define KEY_KP_6 326
#define KEY_KP_7 327
#define KEY_KP_8 328
#define KEY_KP_9 329
#define KEY_KP_DECIMAL 330
#define KEY_KP_DIVIDE 331
#define KEY_KP_MULTIPLY 332
#define KEY_KP_SUBTRACT 333
#define KEY_KP_ADD 334
#define KEY_KP_ENTER 335
#define KEY_KP_EQUAL 336
#define KEY_LEFT_SHIFT 340
#define KEY_LEFT_CONTROL 341
#define KEY_LEFT_ALT 342
#define KEY_LEFT_SUPER 343
#define KEY_RIGHT_SHIFT 344
#define KEY_RIGHT_CONTROL 345
#define KEY_RIGHT_ALT 346
#define KEY_RIGHT_SUPER 347
#define KEY_MENU 348

typedef struct
{
    int offsets[50];
} Char;

typedef struct
{
    unsigned char r, g, b, a;
} Pixel;

typedef struct
{
    unsigned char r, g, b, a;
    int x, y;
} Voxel;

typedef struct
{
    Voxel* data;
    unsigned int length;
} Model;


typedef struct
{
    float x, y;
} Vec2;

typedef struct
{
    int x, y;
} Point;

typedef struct{
    int x, y, strength;
} Light;

int bun2dTick();
int bun2dInit(bool vsync, int src_width, int src_height, int win_width, int win_height);
void bun2dClear();

void bun2dPixel(int x, int y, Pixel color);
Pixel bun2dGetPixel(int x, int y);
void bun2dCircle(int x, int y, int r, Pixel color);
void bun2dFillCircle(int x, int y, int r, Pixel color);
void bun2dLine(int x0, int y0, int x1, int y1, Pixel color);
void bun2dRect(int x, int y, int width, int height, Pixel color);
void bun2dFillRect(int x, int y, int width, int height, Pixel color);
void bun2dText(char *text, int x, int y, Pixel color);
void bun2dSetLight(int x, int y, unsigned int strength);
Model* bun2dMakeModel(Voxel* data, unsigned int length);
Model* bun2dLoadModel(char* adress);
void bun2dDrawModel(Model* model, int x, int y);
double bun2dGetFrameTime();
int bun2dKey(unsigned int key);
Point bun2dGetMouse();

void bun2dClearPixel(int x, int y);
void bun2dInput(GLFWwindow *win, int key, int code, int action, int mod);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
Pixel divPixel(Pixel p, float d);
float getDist(int x1, int y1, int x2, int y2);


#ifdef BUN2D_IMPLEMENTATION

static struct bun2dGlobal
{
    GLFWwindow *window;
    int win_width;
    int win_height;
    int src_width;
    int src_height;
    unsigned char keys[400];
    Char *chars;
    double lastTime;
    double frameTime;
    Pixel *buff;
    Pixel color;
    Light light;

} bun2d = {NULL, 400, 400, 50, 50, {0}, NULL, 0, 0, NULL, {255, 255, 255, 255}, {0,0,0}};

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "layout (location = 1) in vec2 aTexCoord;\n"
                                 "out vec2 TexCoord;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "in vec2 TexCoord;\n"
                                   "uniform sampler2D texture1;\n"
                                   "void main()\n"
                                   "{\n"
                                   "vec4 texColor = texture(texture1, TexCoord);\n"
                                   "if(texColor.a < 0.1)\n"
                                   "discard;\n"
                                   "FragColor = texColor;\n"
                                   "}\n\0";

const Pixel EMPTY = {
    0,
    0,
    0,
    0};

const Pixel RED = {
    255,
    0,
    0,
    255};

const Pixel GREEN = {
    0,
    255,
    0,
    255};

const Pixel BLUE = {
    0,
    0,
    255,
    255};

const Pixel WHITE = {
    255,
    255,
    255,
    255};

const Char i = {{0, 0, 0, 1, 0, 2, 0, 3, 0, 4, -1}};
const Char l = {{0, 0, 0, 1, 0, 2, 0, 3, 0, 4, 1, 0, 2, 0, -1}};
const Char o = {{0, 0, 0, 1, 0, 2, 0, 3, 0, 4, 1, 0, 1, 4, 2, 0, 2, 1, 2, 2, 2, 3, 2, 4, -1}};
const Char t = {{1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 2, 4, 0, 4, -1}};
const Char d = {{0, 0, 0, 1, 0, 2, 0, 3, 0, 4, 1, 0, 1, 4, 2, 1, 2, 2, 2, 3, -1}};
const Char l_0 = {{0,1,0,2,0,3,1,0,1,4,2,0,2,4,3,0,3,4,4,1,4,2,4,3,-1}};
const Char l_1 = {{0,4,1,0,1,1,1,2,1,3,1,4,-1}};
const Char l_2 = {{0,0,0,3,1,0,1,1,1,4,2,0,2,2,2,4,3,0,3,3,-1}};
const Char l_3 = {{0,0,0,4,1,0,1,2,1,4,2,0,2,2,2,4,3,0,3,1,3,2,3,3,3,4,-1}};
const Char l_4 = {{0,2,0,3,0,4,1,2,2,2,3,0,3,1,3,2,3,3,3,4,-1}};
const Char l_5 = {{0,0,0,2,0,3,1,0,1,2,1,4,2,0,2,2,2,4,3,0,3,1,3,2,3,4,-1}};
const Char l_6 = {{0,0,0,1,0,2,0,3,0,4,1,0,1,2,1,4,2,0,2,2,2,4,3,0,3,1,3,2,3,4,-1}};
const Char l_7 = {{0,0,0,4,1,1,1,4,2,2,2,4,3,3,3,4,-1}};
const Char l_8 = {{0,0,0,1,0,3,0,4,1,0,1,2,1,4,2,0,2,2,2,4,3,0,3,1,3,3,3,4,-1}};
const Char l_9 = {{0,0,0,2,0,3,0,4,1,0,1,2,1,4,2,0,2,2,2,4,3,0,3,1,3,2,3,3,3,4,-1}};

Point rotatePoint(Point point, Point origin, int rot)
{

    float angle = rot * (3.14159265358979323846 / 180);
    Point p;

    p.x = cos(angle) * (point.x - origin.x) - sin(angle) * (point.y - origin.y) + origin.x;
    p.y = sin(angle) * (point.x - origin.x) + cos(angle) * (point.y - origin.y) + origin.y;

    return p;
}

void bun2dPixel(int x, int y, Pixel color)
{
    if (x >= bun2d.src_width || x < 0 || y >= bun2d.src_height || y < 0)
    {
        return;
    }
    
    bun2d.buff[bun2d.src_width * y + x] = color;
}

void putPixel(int x, int y, Pixel color)
{
    if (x >= bun2d.src_width || x < 0 || y >= bun2d.src_height || y < 0)
    {
        return;
    }

    if(bun2d.light.strength > 0){
        float dist = getDist(bun2d.light.x, bun2d.light.y, x, y);
        float newDist = dist / bun2d.light.strength;
        if(newDist > 0.1){
            color = divPixel(color, newDist);
        }
    }

    bun2d.buff[bun2d.src_width * y + x] = color;
}

int writeChar(char *l, int x, int y, Pixel color)
{
    int index = *l;
    int maxXOffset = 0;
    for (int i = 0; i < 30; i += 2)
    {
        // need to check for termination of relevant data
        if (bun2d.chars[index].offsets[i] == -1)
        {
            break;
        }
        int xOff = bun2d.chars[index].offsets[i];

        putPixel(x + xOff, y + bun2d.chars[index].offsets[i + 1], color);

        if (xOff > maxXOffset)
        {
            maxXOffset = xOff;
        }
    }
    return maxXOffset;
}

/// @brief Clears the whole pixelbuffer
void bun2dClear()
{
    memset(bun2d.buff, 0, bun2d.src_width * bun2d.src_height * sizeof(Pixel));
}

void bun2dClearPixel(int x, int y)
{
    if (x > bun2d.src_width || x < 0 || y > bun2d.src_height || y < 0)
    {
        return;
    }

    Pixel p = {0, 0, 0, 0};
    bun2d.buff[bun2d.src_width * y + x] = p;
}

/// @brief Renders a line to the screen
/// @param x0 The x coordinate of the origin
/// @param y0 The y coordinate of the origin
/// @param x1 The x coordinate of the target
/// @param y1 The y coordinate of the target
void bun2dLine(int x0, int y0, int x1, int y1, Pixel color)
{
    // We allow to draw lines to or from out of bounds

    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    for (;;)
    {
        putPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void bun2dRect(int x, int y, int width, int height, Pixel color)
{
    for (int i = 0; i < height; i++)
    {
        if (i == 0 || i == height - 1)
        {
            for (int j = 0; j < width; j++)
            {
                putPixel(j + x, i + y, color);
            }
        }
        else
        {
            putPixel(x, i + y, color);
            putPixel(x + width - 1, i + y, color);
        }
    }
}

void bun2dFillRect(int x, int y, int width, int height, Pixel color)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            putPixel(j + x, i + y, color);
        }
    }
}

Pixel bun2dGetPixel(int x, int y)
{

    if (x > bun2d.src_width || x < 0 || y > bun2d.src_height || y < 0)
    {
        return EMPTY;
    }

    return bun2d.buff[bun2d.src_width * y + x];
}

double bun2dGetFrameTime(){
    return bun2d.frameTime * 1000;
}

void drawCircle(int xc, int yc, int x, int y, Pixel color)
{
    putPixel(xc + x, yc + y, color);
    putPixel(xc - x, yc + y, color);
    putPixel(xc + x, yc - y, color);
    putPixel(xc - x, yc - y, color);
    putPixel(xc + y, yc + x, color);
    putPixel(xc - y, yc + x, color);
    putPixel(xc + y, yc - x, color);
    putPixel(xc - y, yc - x, color);
}

/// @brief Renders a circle to the screen
/// @param x The x coordinate on the screen where the text should be written
/// @param y The y coordinate on the screen where the text should be written
/// @param r The radius of the circle
void bun2dCircle(int x, int y, int r, Pixel color)
{
    if (x > bun2d.src_width || x < 0 || y > bun2d.src_height || y < 0)
    {
        return;
    }

    int _x = 0, _y = r;
    int d = 3 - 2 * r;
    drawCircle(x, y, _x, _y, color);
    while (_y >= _x)
    {
        _x++;
        if (d > 0)
        {
            _y--;
            d = d + 4 * (_x - _y) + 10;
        }
        else
            d = d + 4 * _x + 6;
        drawCircle(x, y, _x, _y, color);
    }
}

void bun2dSetLight(int x, int y, unsigned int strength)
{
    Light l = {x,y,strength};
    bun2d.light = l;
}

Model* bun2dMakeModel(Voxel* data, unsigned int length)
{


    void* bar = malloc(length * sizeof(Voxel) + sizeof(unsigned int));
    Model* m = (Model*)bar;
    m->data = data,
    m->length = length;
    return m;
}

Model* bun2dLoadModel(char *adress)
{
    FILE *file;
    file = fopen(adress, "r");
    Voxel* temp = malloc(sizeof(Voxel) * 1000);
    int entries = 0;
    do
    {
        int foo = fscanf(file,
            "%hhu,%hhu,%hhu,%hhu,%d,%d\n",
            &temp[entries].r,
            &temp[entries].g,
            &temp[entries].b,
            &temp[entries].a,
            &temp[entries].x,
            &temp[entries].y
            );
        entries++;
    } while (!feof(file));
    fclose(file);

    void* bar = malloc(entries * sizeof(Voxel) + sizeof(unsigned int));
    Model* m = (Model*)bar;
    memcpy(&m->data, &temp, sizeof(Voxel) * entries);


    m->length = entries;

    //free(temp);

    return m;
}

void bun2dDrawModel(Model *model, int x, int y)
{
    for(int i = 0; i < model->length; i++){
        Voxel v = model->data[i];
        Pixel color = {v.r, v.g, v.b, v.a};
        putPixel(x + v.x, y + v.y, color);
    }
}

void bun2dFillCircle(int x, int y, int r, Pixel color)
{
    for(int _y=-r; _y<=r; _y++)
    for(int _x=-r; _x<=r; _x++)
        if(_x*_x+_y*_y <= r*r)
            putPixel(x+_x, y+_y, color);
}

/// @brief Writes a pixel font text to the screen
/// @param text The text to be written use double \\ for a newline
/// @param x The x coordinate on the screen where the text should be written
/// @param y The y coordinate on the screen where the text should be written
/// @param color The color with which the text should be displayed
void bun2dText(char *text, int x, int y, Pixel color)
{
    int xOffset = 0;
    int yOffset = 8;
    while (*text != '\0')
    {
        if (isspace(*text))
        {
            xOffset += 1;
            ++text;
            continue;
        }
        // \\ is meant to introduce a nextline
        // Working on getting this to be \n
        if (*text == '\\')
        {
            xOffset = 0;
            yOffset += 6;
            ++text;
            continue;
        }

        int charOffset = writeChar(text, x + xOffset, y - yOffset, color);
        ++text;
        xOffset += charOffset + 2;
    }
}

int bun2dKey(unsigned int key)
{
    if (key > 399)
    {
        return 0;
    }
    return bun2d.keys[key];
}

Point bun2dGetMouse()
{
    double xpos, ypos;

    float ratioX = (float)bun2d.win_width / (float)bun2d.src_width;
    float ratioY = (float)bun2d.win_height / (float)bun2d.src_height;

    glfwGetCursorPos(bun2d.window, &xpos, &ypos);
    Point p = {xpos / ratioX, (bun2d.win_height - ypos) / ratioY};
    return p;
}

void fillPixelFont()
{

    bun2d.chars = calloc(150, sizeof(Char *));
    bun2d.chars[100] = d;
    bun2d.chars[105] = i;
    bun2d.chars[108] = l;
    bun2d.chars[111] = o;
    bun2d.chars[116] = t;
    bun2d.chars[48] = l_0;
    bun2d.chars[49] = l_1;
    bun2d.chars[50] = l_2;
    bun2d.chars[51] = l_3;
    bun2d.chars[52] = l_4;
    bun2d.chars[53] = l_5;
    bun2d.chars[54] = l_6;
    bun2d.chars[55] = l_7;
    bun2d.chars[56] = l_8;
    bun2d.chars[57] = l_9;
}
static void bun2dResizeDrawingArea()
{
    printf("bar");
    float vertices[16] = {
        1.0f,   1.0f,   1.0f,   1.0f,
        1.0f,  -1.0f,   1.0f,   0.0f,
        -1.0f, -1.0f,   0.0f,   0.0f,
        -1.0f,  1.0f,   0.0f,   1.0f
    };

    const float w = (float)bun2d.win_width / (float)bun2d.src_width;
    const float h = (float)bun2d.win_height / (float)bun2d.src_height;
    
    float width = (h < w) ? (h / w) : 1.0f;
    float height = (w < h) ? (w / h) : 1.0f;

    for (int i = 0; i < 16; i += 4) {
        vertices[i] *= width;
        vertices[i + 1] *= height;
    }
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

static void bun2dResizeWindow(GLFWwindow* window, int width, int height)
{
#ifndef __APPLE__
    glViewport(0, 0, width, height);
#endif
    bun2d.win_width = width;
    bun2d.win_height = height;
    bun2dResizeDrawingArea();
}

/// @brief Initializes the game engine
/// @param vsync 0 for off 1 for on
/// @return Wether or not the init method was succesfull
int bun2dInit(bool vsync, int src_width, int src_height, int win_width, int win_height)
{

    bun2d.src_width = src_width;
    bun2d.src_height = src_height;
    bun2d.win_width = win_width;
    bun2d.win_height = win_height;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    bun2d.window = glfwCreateWindow(bun2d.win_width, bun2d.win_height, "bun2d", NULL, NULL);
    if (bun2d.window == NULL)
    {
        printf("Failed to create glfwwindow");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(bun2d.window);

    if (!vsync)
    {
        glfwSwapInterval(0);
    }
    glfwSetFramebufferSizeCallback(bun2d.window, framebuffer_size_callback);
    glfwSetKeyCallback(bun2d.window, bun2dInput);
    glfwSetWindowSizeCallback(bun2d.window, bun2dResizeWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to load glad");
        return -1;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Shader linking failed");
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("Shader linking failed");
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("Shader linking failed");
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f};
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3};
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    unsigned int texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    bun2d.buff = calloc(bun2d.src_width * bun2d.src_height, sizeof(Pixel *));

    fillPixelFont();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bun2d.src_width, bun2d.src_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bun2d.buff);
    glGenerateMipmap(GL_TEXTURE_2D);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    return 0;
}

int bun2dTick()
{
    double currentTime = glfwGetTime();
    bun2d.frameTime = currentTime - bun2d.lastTime;
    bun2d.lastTime = currentTime;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bun2d.src_width, bun2d.src_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bun2d.buff);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(bun2d.window);
    glfwPollEvents();
    return !glfwWindowShouldClose(bun2d.window);
}

void bun2dInput(GLFWwindow *win, int key, int code, int action, int mod)
{
    bun2d.keys[key] = action;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    bun2d.win_width = width;
    bun2d.win_height = height;
    glViewport(0, 0, width, height);
}

float getDist(int x1, int y1, int x2, int y2){
    float distSquared = ((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1));
    return sqrt(distSquared);
}

Pixel divPixel(Pixel p, float d){
    int r = (int)p.r / d;
    int g = (int)p.g / d;
    int b = (int)p.b / d;
    Pixel new = {
        r > 255 ? 255 : r,
        g > 255 ? 255 : g,
        b > 255 ? 255 : b,
        p.a
    };

    return new;
}


#endif
