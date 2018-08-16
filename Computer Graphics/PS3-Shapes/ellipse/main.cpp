#include<GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>
#include<math.h>

int yc =0,xc=0;
void myinit(void)
{
    glClearColor(0.0,0.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-400,400,-400,400);

}


void SetPixel(GLdouble x , GLdouble y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
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
glColor3f (0.0, 0.0, 0.0);
xc=80;yc=0;
MidPointEllipse(40,10);
xc=-80;yc=0;
MidPointEllipse(40,10);
xc=0;yc=80;
MidPointEllipse(10,40);
xc=0;yc=-80;
MidPointEllipse(10,40);

  glColor3f (1.0, 0.0, 0.0);
xc=0;yc=0;
MidPointEllipse(40,40);

}
int main(int argc, char** argv)
{
    glutInit(&argc , argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(500,380);
    glutCreateWindow("Midpoint ellipse");
    myinit();
    glutDisplayFunc(&display);
    glutMainLoop();
    return 0;
}
