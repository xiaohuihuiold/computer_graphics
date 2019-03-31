#include "draw.h"

void drawImagePoint( GLImage *image,int x,int y,GLfloat r,GLfloat g,GLfloat b,GLfloat a,GLfloat d)
{
    if(x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT || d < 0.0f || d > image->depth[y][x])return;
    image->image[y*WINDOW_WIDTH+x].r = r;
    image->image[y*WINDOW_WIDTH+x].g = g;
    image->image[y*WINDOW_WIDTH+x].b = b;
    image->image[y*WINDOW_WIDTH+x].a = a;
    image->depth[y][x] = d;
}

void clearImage( GLImage *image)
{
    for(int y = 0;y < WINDOW_HEIGHT;++y)
    {
        for(int x = 0;x < WINDOW_WIDTH;++x)
        {
            image->image[y*WINDOW_WIDTH+x].r = 0.0f;
            image->image[y*WINDOW_WIDTH+x].g = 0.0f;
            image->image[y*WINDOW_WIDTH+x].b = 0.0f;
            image->image[y*WINDOW_WIDTH+x].a = 1.0f;
            image->depth[y][x] = 2.0f;
        }
    }
}

int initDraw(void (*onDraw)(const  GLImage*))
{
    glfwInit();

    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"line",NULL,NULL);

    if(window == NULL)
    {
        perror("窗口创建失败:");

        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);

     GLImage image;
    image.image = (GLPixel*)malloc(WINDOW_HEIGHT * WINDOW_WIDTH * sizeof(GLPixel));
    image.drawPoint = &drawImagePoint;
    image.clear = &clearImage;

    while(!glfwWindowShouldClose(window))
    {
        image.clear(&image);

        onDraw(&image);

        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(-1.0f,-1.0f,-1.0f);

        glDrawPixels(WINDOW_WIDTH,WINDOW_HEIGHT,GL_RGBA,GL_FLOAT,image.image);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    free(image.image);

    glfwTerminate();
    return 0;
}
