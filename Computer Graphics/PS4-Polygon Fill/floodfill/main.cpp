#include<GL/glut.h>
#include<iostream>
#include<math.h>
#include<stdio.h>
using namespace std;
float boundaryColor[3] = {1,1,0};
float interiorColor[3] = {0,0,0};
float fillColor[3] = {0,1,1};
float readPixel[3];
int xc,yc;
void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
}
void setPixel(int x, int y)
{
    glColor3fv(fillColor);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}
void SetPixel(GLdouble x , GLdouble y)
{

    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}
void putPixel(int x, int y)
{
    glColor3fv(boundaryColor);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void getPixel(int x, int y, float *color)
{
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);

}
void floodFill(int x, int y)
{
    getPixel(x,y,readPixel);
    if(readPixel[0] == interiorColor[0] && readPixel[1]==interiorColor[1] && readPixel[2]==interiorColor[2])
    {
        setPixel(x,y);
        floodFill(x+1,y);
        floodFill(x,y+1);
        floodFill(x-1,y);
        floodFill(x,y-1);
        /*floodFill(x+1,y+1);
        floodFill(x-1,y+1);
        floodFill(x-1,y-1);
        floodFill(x+1,y-1);*/

    }
}


void Circle_points(int x1,int x,int y1,int y)
{
        putPixel(x1+x,y1+y);
        putPixel(x1+y,y1+x);
        putPixel(x1+x,y1-y);
        putPixel(x1+y,y1-x);

        putPixel(x1-x,y1-y);
        putPixel(x1-y,y1-x);
        putPixel(x1-x,y1+y);
        putPixel(x1-y,y1+x);

}
void midPointCircle(int x1,int y1,int r)
{
    int x=0;
    int y=r;
    int d=1-r;
    Circle_points(x1,x,y1,y);
    while(x<y)
    {
        x++;
        if(d<=0)
            d = d+2*x+1;
        else{
            y--;
            d=d+2*(x-y)+1;
        }
        Circle_points(x1,x,y1,y);
    }
}
void EllipsePoints(int x,int y)
{
    SetPixel(x+xc,y+yc);
    SetPixel(-x+xc,y+yc);
    SetPixel(-x+xc,-y+yc);
    SetPixel(x+xc,-y+yc);
}

void MidPointEllipse(int a, int b)
{
    double d2;
    int x=0,y=b;
    double d1=b*b-(a*a*b)+(0.25*a*a);
    EllipsePoints(x,y);
    while ((a *a *(y-0.5)) > (b*b*(x+1)))
    {
        if (d1<0)
            d1 += b*b*(2*x +3);
        else
        {
            d1 += b*b*(2*x+3)+a*a*(-2*y+2);
            y=y-1;
        }
        x=x+1;
        EllipsePoints(x,y);

    }


    d2 = (b*b*((x+0.5)*(x+0.5)) + a*a*((y-1)*(y-1)) - a*a*b*b);
    while(y>0)
    {
        if ((d2) <0)
        {
            d2 +=b*b*(2*x+2) +a*a*(-2*y +3);
            x=x+1;
        }
        else

            d2 += a*a*(-2*y+3);

        y = y-1;
        EllipsePoints(x,y);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);


    xc=165;yc=130;
    MidPointEllipse(80,30);

    midPointCircle(165,300,30);

    floodFill(165,130);

    floodFill(150,300);
    glFlush();
}

int main(int argc, char**argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("FloodFill");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
