#include <iostream>
#include <math.h>
#include <GLFW/glfw3.h>

#define WINDOW_TITLE "graphics"

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 720;

struct Vec {
    GLfloat x;
    GLfloat y;
    GLfloat z;

    Vec() = default;

    Vec(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z) {}

    Vec operator+(const Vec &b) {
        return {x + b.x, y + b.y, z + b.z};
    }

    Vec operator-(const Vec &b) {
        return {x - b.x, y - b.y, z - b.z};
    }

    Vec operator*(const Vec &b) {
        return {x * b.x, y * b.y, z * b.z};
    }

    Vec operator+(GLfloat b) {
        return {x + b, y + b, z + b};
    }

    Vec operator-(GLfloat b) {
        return {x - b, y - b, z - b};
    }

    Vec operator*(GLfloat b) {
        return {x * b, y * b, z * b};
    }

    Vec operator/(GLfloat b) {
        return {x / b, y / b, z / b};
    }

    Vec normalize() {
        return *this * (1.0f / length());
    }

    Vec netate() {
        return *this * (-1.0f);
    }

    GLfloat length() {
        return sqrt(x * x + y * y + z * z);
    }

    GLfloat dot(const Vec &b) {
        return x * b.x + y * b.y + z * b.z;
    }

    Vec cross(const Vec &b) {
        return {y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x};
    }

};

struct Triangle {
    Vec a;
    Vec b;
    Vec c;

    Triangle() = default;

    Triangle(Vec a, Vec b, Vec c) : a(a), b(b), c(c) {}
};

struct GLPixel {
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;

    GLPixel() = default;

    GLPixel(GLfloat r, GLfloat g, GLfloat b, GLfloat a) : r(r), g(g), b(b), a(a) {}
};

struct GLImage {
    GLPixel (*image)[WINDOW_WIDTH] = new GLPixel[WINDOW_HEIGHT][WINDOW_WIDTH];
    GLfloat (*depth)[WINDOW_WIDTH] = new GLfloat[WINDOW_HEIGHT][WINDOW_WIDTH];

    void drawPoint(int x, int y, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat d) {
        if (d < 0 || d > depth[y][x])return;
        image[y][x].r = r;
        image[y][x].g = g;
        image[y][x].b = b;
        image[y][x].a = a;
        depth[y][x] = d;
    }

    void clearImage() {
        for (int y = 0; y < WINDOW_HEIGHT; ++y) {
            for (int x = 0; x < WINDOW_WIDTH; ++x) {
                image[y][x].r = 0.0f;
                image[y][x].g = 0.0f;
                image[y][x].b = 0.0f;
                image[y][x].a = 0.0f;
                depth[y][x] = 2.0f;
            }
        }
    }

    void freeImage() {
        delete[] image;
        delete[] depth;
    }
};

void onKeyInput(GLFWwindow *);

int main() {
    glfwInit();

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "窗口创建失败" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    GLImage image;

    while (!glfwWindowShouldClose(window)) {
        onKeyInput(window);

        image.clearImage();
        for (int y = 0; y < WINDOW_HEIGHT; ++y) {
            for (int x = 0; x < WINDOW_WIDTH; ++x) {
                GLfloat r = 1.0f * ((float) x / WINDOW_WIDTH);
                GLfloat g = 0.2 + 0.8f * ((float) y / WINDOW_HEIGHT);
                GLfloat b = 0.3 + 0.5f * ((float) x / WINDOW_WIDTH);
                GLfloat a = 1.0f;
                image.drawPoint(x, y, r, g, b, a, 2.0f);
            }
        }

        // 清除颜色缓冲
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // 初始化坐标系
        glLoadIdentity();
        // 原点移动到左下角
        glTranslatef(-1.0f, -1.0f, -1.0f);

        glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_FLOAT, image.image);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    image.freeImage();

    glfwTerminate();
    return 0;
}

void onKeyInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}