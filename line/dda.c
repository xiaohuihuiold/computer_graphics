#include <stdio.h>
#include "draw.h"

void draw(const GLImage *image)
{
    /**for(int i=0;i<500;i++)
      {
      image->drawPoint(image,i,10,1.0f,1.0f,1.0f,1.0f,2.0f);
      }**/
    for(int y=0;y<WINDOW_HEIGHT;++y){
        for(int x=0;x<WINDOW_WIDTH;++x){
            image->drawPoint(image,x,y,1.0f,1.0f,1.0f,1.0f,2.0f);
            GLfloat r = 1.0f * ((float) x / WINDOW_WIDTH);
            GLfloat g = 0.2 + 0.8f * ((float) y / WINDOW_HEIGHT);
            GLfloat b = 0.3 + 0.5f * ((float) x / WINDOW_WIDTH);
            GLfloat a = 1.0f;
            image->drawPoint(image,x, y, r, g, b, a, 2.0f);
        }
    }
}

int main()
{
    initDraw(draw);
    return 0;
}
