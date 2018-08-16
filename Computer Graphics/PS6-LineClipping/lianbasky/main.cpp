#include<GL/glut.h>
#include<iostream>
#include<math.h>
#define outcode int
using namespace std;
double xmin=0,ymin=0,xmax=200,ymax=200;
double xvmin=100,yvmin=100,xvmax=400,yvmax=400;
const int RIGHT=8;
const int LEFT=2;
const int TOP=4;
const int BOTTOM=1;
int clipTest(float p, float q, float *u1, float *u2);
void setPixel(GLdouble x, GLdouble y)
{
    glColor3f(0,1,1);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}
void init(void)
    {
        glClearColor(1,1,1,1);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(-500,500,-500,500);
    }
void DDALine(GLdouble x1,GLdouble y1,GLdouble x2,GLdouble y2)
{
    double x,y,dx,dy,length,xinc,yinc,i;
    dx = x2-x1;
    dy = y2-y1;

    if (fabs(dy)>fabs(dx))
        length = fabs(dy);
    else
        length = fabs(dx);

    xinc = dx/length;
    yinc = dy/length;
    x = x1;
    y =y1;
    setPixel(x,y);
    for(i=1;i<length;i++)
    {
        x += xinc;
        y += yinc;
        setPixel(round(x),round(y));
    }
}
void clipLine(int xmax, int xmin, int ymax, int ymin, int x0, int y0, int x2, int y2)
    {
        float u1 = 0, u2 = 1;
        int dx = x2 - x0;
        int dy = y2 - y0;


        if(clipTest(-dx, x0-xmin, &u1, &u2))
            {

                if(clipTest(dx, xmax-x0, &u1, &u2))
                    {

                        if(clipTest(-dy, y0-ymin, &u1, &u2))
                            {

                                if(clipTest(dy, ymax-y0, &u1, &u2))
                                    {

                                        if(u2 < 1)
                                            {
                                                x2 = x0 + u2 * (x2 - x0);
                                                y2 = y0 + u2 * (y2 - y0);
                                            }
                                        if(u1 > 0)
                                            {
                                                x0 = x0 + u1 * (x2 - x0);
                                                y0 = y0 + u1 * (y2 - y0);
                                            }
                                        glColor3f(1, 0, 0);
                                        glBegin(GL_LINES);
                                            glVertex2i(x0, y0);
                                            glVertex2i(x2, y2);
                                        glEnd();

                                        glFlush();
                                    }
                            }
                    }
            }
        glFlush();
    }

int clipTest(float p, float q, float *u1, float *u2)
    {

        float r;
        int returnVal = 1;

        if(p < 0)
            {
                r = q/p;
                if(r > *u2)
                    returnVal = 0;
                else if(r > *u1)
                    *u1 = r;
            }
        else if(p > 0)
            {
                r = q/p;
                if(r < *u1)
                    returnVal = 0;
                else if(r < *u2)
                    *u2 = r;
            }
        else if(q < 0)
            returnVal = 0;



        return returnVal;
        glFlush();

    }

void display()
    {
        glClear(GL_COLOR_BUFFER_BIT);

glBegin(GL_LINE_LOOP);
glColor3f(0, 0.5, 0);
           DDALine( 50, 15, 80, 100);
            DDALine(10,50,240,110);
            DDALine(10,0,110,0);
            DDALine(50,30,140,40);



        glEnd();
        glFlush();
 glColor3f(1, 0, 0);
        glBegin(GL_LINE_LOOP);
           DDALine(20, 20,220, 20);
            DDALine(220, 20,220, 220);
            DDALine(220, 220,20, 220);
            DDALine(20, 220,20, 20);

        clipLine(220,20,220,20, 50, 15, 80, 100);
        clipLine(220,20,220,20,10,50,240,110);
        clipLine(220,20,220,20,10,0,0,0);
        clipLine(220,20,220,20,50,30,140,40);


        glEnd();
        glFlush();
    }

int main(int v,char** w)
    {
        glutInit(&v,w);
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
        glutInitWindowPosition(100,100);
        glutInitWindowSize(400,400);
        glutCreateWindow("Liang Barsky");
        init();
        glutDisplayFunc(&display);
        glutMainLoop();
        return 0;
    }


