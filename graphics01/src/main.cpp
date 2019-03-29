#include <iostream>
#include <GLFW/glfw3.h>

#define WINDOW_TITLE "graphics"

struct GLPixel {
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;

    void drawPixel(float r, float g, float b, float a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 720;

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

    GLPixel (*image)[WINDOW_WIDTH] = new GLPixel[WINDOW_HEIGHT][WINDOW_WIDTH];

    while (!glfwWindowShouldClose(window)) {
        onKeyInput(window);

        for (int y = 0; y < WINDOW_HEIGHT; ++y) {
            for (int x = 0; x < WINDOW_WIDTH; ++x) {
                image[y][x].r = 1.0f * ((float) x / WINDOW_WIDTH);
                image[y][x].g = 0.2 + 0.8f * ((float) y / WINDOW_HEIGHT);
                image[y][x].b = 0.3 + 0.5f * ((float) x / WINDOW_WIDTH);
                image[y][x].a = 1.0f;
            }
        }

        // 清除颜色缓冲
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // 初始化坐标系
        glLoadIdentity();
        // 原点移动到左下角
        glTranslatef(-1.0f, -1.0f, -1.0f);

        glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_FLOAT, image);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete[] image;

    glfwTerminate();
    return 0;
}

void onKeyInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}