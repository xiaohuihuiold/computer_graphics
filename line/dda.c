#include <stdio.h>
#include <math.h>
#include "draw.h"

int startx;
int starty;
int endx;
int endy;

void dda(const GLImage *image,int x0,int y0,int x1,int y1)
{
    /** 只考虑了一种情况
    float dx=x1-x0;
    float dy=y1-y0;
    float k=dx/dy;
    float x=x0;

    for(;y0<=y1;++y0)
    {
        image->drawPoint(image,(int)(x+0.5),y0,1.0f,1.0f,1.0f,1.0f,2.0f);
        x+=k;
    }
    **/

    // 适合绘制所有直线
    float dx=x1-x0;
    float dy=y1-y0;
    int steps=abs(y1-y0);

    float xInc;
    float yInc;
    float x=x0;
    float y=y0;

    if(fabs(dx)>fabs(dy))
        steps=fabs(x1-x0);

    xInc=dx/steps;
    yInc=dy/steps;

    image->drawPoint(image,round(x),round(y),1.0f,1.0f,1.0f,1.0f,2.0f);
    for(int i=0;i<steps;i++)
    {
        x+=xInc;
        y+=yInc;
        image->drawPoint(image,round(x),round(y),1.0f,1.0f,1.0f,1.0f,2.0f);
    }
}

void draw(const GLImage *image)
{
    dda(image,startx,starty,endx,endy);
}

int main()
{
    scanf("%d %d %d %d",&startx,&starty,&endx,&endy);
    initDraw(draw);
    return 0;
}
