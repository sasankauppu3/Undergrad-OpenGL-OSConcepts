#include<GL/gl.h>
#include<GL/glut.h>
#include<GL/glu.h>
#include<math.h>
void myInit()
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0,600.0,0.0,400.0);
glClearColor(1.0,1.0,1.0,1.0);
}
void writepixel(float x,float y)
{
glBegin(GL_POINTS);
glVertex2f(x,y);
glEnd();
}
void elp(int ,int);
void mid(int a,int b)
{
    double d2;
    int x=100;int y=b;
    double d1=b*b-(a*a*b*b)+(0.25*a*a);
    elp(x,y);
    while(a*a*(y-0.5)>b*b*(x+1))
    {
        if(d1<0)
        {
            d1=d1+b*b*(2*x+3);
        }
        else
        {
            d1=d1+b*b*(2*x+3)+a*a*(-2*y+2);
            y--;
        }
        x++;
        elp(x,y);

        }
        d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;
        while(y>0)
        {
            if(d2<0)
            {
                d2+=b*b*(2*x+2)+a*a*(-2*y+3);
                x++;
            }
            else
            d2+=a*a*(-2*y+3);
            y--;
            elp(x,y);
        }
    }
    void elp(int x,int y)
    {
        writepixel(x+200,y+200);
        writepixel(y+200,x+200);
        writepixel(-y-200,x+200);
        writepixel(x+200,-y-200);
        writepixel(-x-200,-y-200);
        writepixel(-y-200,-x-200);
        writepixel(y+200,-x-200);
        writepixel(-x-200,y+200);
    }

void mydisplay()
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0,0.0,0.0);
mid(10,15);
glFlush();
}

int main(int argc, char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
glutInitWindowSize(640,480);
glutInitWindowPosition(100,200);
glutCreateWindow("Basic Drawing");
glutDisplayFunc(mydisplay);
myInit();
glutMainLoop();
return 0;
}

