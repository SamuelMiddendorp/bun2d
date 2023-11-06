#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdbool.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
int bun2dTick();
void bun2dClear();
void bun2dClearPixel();

#define TEXT_X 800
#define TEXT_Y 800
#define TEXT_SIZE TEXT_X *TEXT_Y
#define CIRCLE_RAD 25

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int angle = 40;
int max_iterations = 10;

int playerX = 0;
int playerY = 0;

int rectangleWidth = 100;
int rectangleHeight = 100;

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

typedef struct Pixel
{
    unsigned char r, g, b, a
} Pixel;

typedef struct Point
{
    int x, y
} Point;

Pixel *buff;

Point rotatePoint(Point point, Point origin, int rot)
{

    float angle = rot * (3.14159265358979323846 / 180);
    Point p;

    p.x = cos(angle) * (point.x - origin.x) - sin(angle) * (point.y - origin.y) + origin.x;
    p.y = sin(angle) * (point.x - origin.x) + cos(angle) * (point.y - origin.y) + origin.y;

    return p;
}

void putColorPixel(int x, int y, Pixel color)
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
    if (x > TEXT_X || x < 0 || y > TEXT_Y || y < 0)
    {
        return;
    }

    buff[TEXT_X * y + x].r = 144;
    buff[TEXT_X * y + x].g = 255;
    buff[TEXT_X * y + x].b = 255;
    buff[TEXT_X * y + x].a = 200;
}
void bun2dClear()
{
    memset(buff, 0, TEXT_X * TEXT_Y * sizeof(Pixel));
}

void bun2dClearPixel(int x, int y){
    if (x > TEXT_X || x < 0 || y > TEXT_Y || y < 0)
    {
        return;
    }

    buff[TEXT_X * y + x].r = 0;
    buff[TEXT_X * y + x].g = 0;
    buff[TEXT_X * y + x].b = 0;
    buff[TEXT_X * y + x].a = 0;

}

void drawLine(int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    for (;;)
    { /* loop */
        putPixel(x0, y0);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        } /* e_xy+e_x > 0 */
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        } /* e_xy+e_y < 0 */
    }
}

void drawRectangle(int x, int y, int width, int height, int rotation, Pixel color)
{
    Point origin = {x, y};

    for (int i = 0; i < height; i++)
    {
        if (i == 0 || i == height - 1)
        {
            for (int j = 0; j < width; j++)
            {
                Point p = {j + x, i + y};
                Point rotatedPoint = rotatePoint(p, origin, rotation);
                putColorPixel(rotatedPoint.x, rotatedPoint.y, color);
            }
        }
        else
        {
            Point pA = {x, i + y};
            Point rotatedPoint = rotatePoint(pA, origin, rotation);
            putColorPixel(rotatedPoint.x, rotatedPoint.y, color);

            Point pB = {x + width, i + y};
            rotatedPoint = rotatePoint(pB, origin, rotation);
            putColorPixel(rotatedPoint.x, rotatedPoint.y, color);
        }
    }
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

void bun2dCircle(int xc, int yc, int r)
{

    int x = 0, y = r;
    int d = 3 - 2 * r;
    drawCircle(xc, yc, x, y);
    while (y >= x)
    {
        x++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        drawCircle(xc, yc, x, y);
    }
}

void drawNode(int x, int y, int iteration)
{
    int newX = x + angle;
    int newX2 = x - angle;
    int newY = y + 70 - (iteration * 5);

    drawLine(x, y, newX, newY);
    drawLine(x, y, newX2, newY);

    if (iteration > max_iterations)
    {
        return;
    }
    drawNode(newX, newY, iteration + 1);
    drawNode(newX2, newY, iteration + 1);
}

void fractal(int x, int y)
{
    drawNode(x, y, 0);
}

int main()
{
    bun2dSetup();
    while (bun2dTick())
    {
        bun2dClear();
        bun2dCircle(playerX     ,20,20);
    }
}

int bun2dSetup()
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // top right
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom left
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
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

    // Allocate pixel buffer here
    buff = calloc(TEXT_SIZE, sizeof(Pixel *));

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXT_X, TEXT_Y, 0, GL_RGBA, GL_UNSIGNED_BYTE, buff);
    glGenerateMipmap(GL_TEXTURE_2D);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
}

int bun2dTick()
{
    processInput(window);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TEXT_X, TEXT_Y, 0, GL_RGBA, GL_UNSIGNED_BYTE, buff);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window);
    glfwPollEvents();
    return !glfwWindowShouldClose(window);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        bun2dClear();
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        playerX++;
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        for (int i = 0; i < TEXT_SIZE; i++)
        {
            buff[i].r = rand() % 255;
            buff[i].g = rand() % 255;
            buff[i].b = rand() % 222;
            buff[i].a = 255;
        }
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        bun2dCircle(xpos, 800-ypos, 20);
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        bun2dClearPixel(xpos, 800-ypos);
    }
    
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        rectangleWidth++;
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        rectangleWidth--;
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
