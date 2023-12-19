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

#define TEXT_X 160 
#define TEXT_Y 160
#define TEXT_SIZE TEXT_X *TEXT_Y

typedef struct 
{
    int offsets[100];
} Char;

typedef struct 
{
    unsigned char r, g, b, a;
} Pixel;

typedef struct 
{
    float x, y;
} Vec2;

typedef struct 
{
    int x, y;
} Point;

int bun2dTick();
int bun2dInit(int vsync);
void bun2dClear();

void bun2dPixel(int x, int y, Pixel color);
Pixel bun2dGetPixel(int x, int y);
void bun2dLine(int x0, int y0, int x1, int y1);
void bun2dRect(int x, int y, int width, int height);
void bun2dText(char* text, int x, int y);
int bun2dKey(int key);
Point bun2dGetMouse();

void bun2dClearPixel(int x, int y);
void bun2dInput(GLFWwindow *win, int key, int code, int action, int mod);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

#ifdef BUN2D_IMPLEMENTATION 
unsigned char keys[400];

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

double mouseX = 0;
double mouseY = 0;

GLFWwindow *window;

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

Pixel *buff;
Char *chars;
// Init to white
Pixel _color = {
    255,
    255,
    255,
    255
};

const Pixel EMPTY = {
    0,
    0,
    0,
    0
};

const Pixel RED = {
    255,
    0,
    0,
    255
};

const Pixel GREEN = {
    0,
    255,
    0,
    255
};

const Pixel BLUE = {
    0,
    0,
    255,
    255
};

const Pixel WHITE = {
    255,
    255,
    255,
    255
};


const Char i = {{0, 0, 0, 1, 0, 2, 0, 3, 0, 4, -1}};
const Char l = {{0, 0, 0, 1, 0, 2, 0, 3, 0, 4, 1, 0, 2, 0, -1}};
const Char o = {{0, 0, 0, 1, 0, 2, 0, 3, 0, 4, 1, 0, 1, 4, 2, 0, 2, 1, 2, 2, 2, 3, 2, 4, -1}};
const Char t = {{1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 2, 4, 0, 4, -1}};
const Char d = {{0,0,0,1,0,2,0,3,0,4,1,0,1,0,1,0,1,0,1,4,2,0,2,0,2,0,2,0,2,4,3,0,3,0,3,0,3,0,3,4,3,4,4,1,4,2,4,3,4,3,-1}};

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
    if (x > TEXT_X || x < 0 || y > TEXT_Y || y < 0)
    {
        return;
    }

    buff[TEXT_X * y + x].r = color.r;
    buff[TEXT_X * y + x].g = color.g;
    buff[TEXT_X * y + x].b = color.b;
    buff[TEXT_X * y + x].a = color.a;
}

void putPixel(int x, int y)
{
    if (x >= TEXT_X || x < 0 || y >= TEXT_Y || y < 0)
    {
        return;
    }

    buff[TEXT_X * y + x].r = _color.r;
    buff[TEXT_X * y + x].g = _color.g;
    buff[TEXT_X * y + x].b = _color.b;
    buff[TEXT_X * y + x].a = _color.a;
}

int writeChar(char *l, int x, int y)
{
    int index = *l;
    int maxXOffset = 0;
    for (int i = 0; i < 30; i += 2)
    {
        // need to check for termination of relevant data
        if (chars[index].offsets[i] == -1)
        {
            break;
        }
        int xOff = chars[index].offsets[i];

        putPixel(x + xOff, y + chars[index].offsets[i + 1]);

        if(xOff > maxXOffset){
            maxXOffset = xOff;
        }
    }
    return maxXOffset;
}

/// @brief Clears the whole pixelbuffer
void bun2dClear()
{
    memset(buff, 0, TEXT_X * TEXT_Y * sizeof(Pixel));
}

void bun2dClearPixel(int x, int y)
{   
    if (x > TEXT_X || x < 0 || y > TEXT_Y || y < 0)
    {
        return;
    }

    buff[TEXT_X * y + x].r = 0;
    buff[TEXT_X * y + x].g = 0;
    buff[TEXT_X * y + x].b = 0;
    buff[TEXT_X * y + x].a = 0;
}

/// @brief Renders a line to the screen 
/// @param x0 The x coordinate of the origin 
/// @param y0 The y coordinate of the origin 
/// @param x1 The x coordinate of the target 
/// @param y1 The y coordinate of the target 
void bun2dLine(int x0, int y0, int x1, int y1)
{
    // We allow to draw lines to or from out of bounds

    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    for (;;)
    {
        putPixel(x0, y0);
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

void bun2dRect(int x, int y, int width, int height)
{
    if (x > TEXT_X || x < 0 || y > TEXT_Y || y < 0)
    {
        return;
    }

    Point origin = {x, y};

    for (int i = 0; i < height; i++)
    {
        if (i == 0 || i == height - 1)
        {
            for (int j = 0; j < width + 1; j++)
            {
                Point p = {j + x, i + y};
                putPixel(p.x, p.y);
            }
        }
        else
        {
            Point pA = {x, i + y};
            putPixel(pA.x, pA.y);

            Point pB = {x + width, i + y};
            putPixel(pB.x, pB.y);
        }
    }
}

void bun2dColor(Pixel color){
    _color = color;
}

Pixel bun2dGetPixel(int x, int y){

    if (x > TEXT_X || x < 0 || y > TEXT_Y || y < 0)
    {
        return EMPTY;
    }
    
    Pixel p = {
    buff[TEXT_X * y + x].r,
    buff[TEXT_X * y + x].g,
    buff[TEXT_X * y + x].b,
    buff[TEXT_X * y + x].a
    };
    
    return p;
}

void drawCircle(int xc, int yc, int x, int y)
{
    putPixel(xc + x, yc + y);
    putPixel(xc - x, yc + y);
    putPixel(xc + x, yc - y);
    putPixel(xc - x, yc - y);
    putPixel(xc + y, yc + x);
    putPixel(xc - y, yc + x);
    putPixel(xc + y, yc - x);
    putPixel(xc - y, yc - x);
}

/// @brief Renders a circle to the screen
/// @param x The x coordinate on the screen where the text should be written
/// @param y The y coordinate on the screen where the text should be written
/// @param r The radius of the circle 
void bun2dCircle(int x, int y, int r)
{
    if (x > TEXT_X || x < 0 || y > TEXT_Y || y < 0)
    {
        return;
    }

    int _x = 0, _y = r;
    int d = 3 - 2 * r;
    drawCircle(x, y, _x, _y);
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
        drawCircle(x, y, _x, _y);
    }
}

/// @brief Writes a pixel font text to the screen   
/// @param text The text to be written use double \\ for a newline
/// @param x The x coordinate on the screen where the text should be written
/// @param y The y coordinate on the screen where the text should be written
void bun2dText(char* text, int x, int y)
{
    int xOffset = 0;
    int yOffset = 8;
    while (*text != '\0')
    {
        if(isspace(*text)){
            xOffset += 1;
            ++text;
            continue;
        }
        // \\ is meant to introduce a nextline
        // Working on getting this to be \n
        if(*text == '\\'){
            xOffset = 0;
            yOffset += 6;
            ++text;
            continue;
        }

        int charOffset = writeChar(text, x + xOffset, y - yOffset);
        ++text;
        xOffset += charOffset + 2;
    }
}

int bun2dKey(int key){
    if(key > 399){
        return 0;
    }
    return keys[key]; 
}

Point bun2dGetMouse(){
    double xpos, ypos;

    float ratioX = SCR_WIDTH / TEXT_X;
    float ratioY = SCR_HEIGHT / TEXT_Y;

    glfwGetCursorPos(window, &xpos, &ypos);
    Point p = {xpos / ratioX, TEXT_Y - ypos / ratioY};
    return p;
}

void fillPixelFont(){

    chars = calloc(200, sizeof(Char *));
    chars[100] = d;

    chars[105] = i;
    chars[108] = l;
    chars[111] = o;
    chars[116] = t;

}

/// @brief Initializes the game engine
/// @param vsync 0 for off 1 for on
/// @return Wether or not the init method was succesfull
int bun2dInit(int vsync)
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "bun2d", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create glfwwindow");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!vsync){
        glfwSwapInterval(0);
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, bun2dInput);

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

    buff = calloc(TEXT_SIZE, sizeof(Pixel *));

    fillPixelFont();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXT_X, TEXT_Y, 0, GL_RGBA, GL_UNSIGNED_BYTE, buff);
    glGenerateMipmap(GL_TEXTURE_2D);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    return 0;
}

int bun2dTick()
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwGetCursorPos(window, &mouseX, &mouseY);
    // Have to adjust for mismatch in coordinates
    mouseY = SCR_HEIGHT - mouseY;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXT_X, TEXT_Y, 0, GL_RGBA, GL_UNSIGNED_BYTE, buff);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
    return !glfwWindowShouldClose(window);
}

void bun2dInput(GLFWwindow *win, int key, int code, int action, int mod)
{
    keys[key] = action;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
#endif
