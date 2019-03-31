#ifndef _DRAW_H
#define _DRAW_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 720

typedef struct GLPixel
{
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
} GLPixel;

typedef struct GLImage
{
    struct GLPixel *image;
    GLfloat depth[WINDOW_HEIGHT][WINDOW_WIDTH];

    void (*drawPoint)(struct GLImage*,int,int,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
    void (*clear)(struct GLImage*);
} GLImage;

void drawImagePoint(struct GLImage*,int x,int y,GLfloat r,GLfloat g,GLfloat b,GLfloat a,GLfloat d);
void clearImage(struct GLImage*);

int initDraw(void (*onDraw)(const struct GLImage*));

#endif
