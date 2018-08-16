#include<GL/glut.h>
#define outcode int
#include<GL/glu.h>
#include<GL/gl.h>
#include<iostream>
#include<math.h>
double xmin=0,ymin=0,xmax=200,ymax=200;       //window boundaries
double xvmin=100,yvmin=100,xvmax=400,yvmax=400; //viewport boundarie
const int RIGHT=8;
const int LEFT=2;
const int TOP=4;
const int BOTTOM=1;
outcode ComputeOutCode(double x,double y);

void init(void)
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500,500,-500,500);
}
void setPixel(GLdouble x, GLdouble y)
{
    glColor3f(0,1,1);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
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
void cs(double x0,double y0,double x1,double y1)
{
    outcode outcode0,outcode1,outcodeOut;
    bool accept=false,done=false;
    outcode0=ComputeOutCode(x0,y0);
    outcode1=ComputeOutCode(x1,y1);
    do
    {
        if(!(outcode0|outcode1))
        {
            accept=true;
            done=true;
        }
        else if(outcode0 & outcode1)
            done=true;
        else
        {
            double x,y;
            outcodeOut=outcode0?outcode0:outcode1;
            if(outcodeOut & TOP)
            {
                x=x0+(x1-x0)*(ymax-y0)/(y1-y0);
                y=ymax;
            }
            else if(outcodeOut & BOTTOM)
            {
                x=x0+(x1-x0)*(ymin-y0)/(y1-y0);
                y=ymin;
            }
            else if(outcodeOut & RIGHT)
            {
                y=y0+(y1-y0)*(xmax-x0)/(x1-x0);
                x=xmax;
            }
            else if(outcodeOut & LEFT)
            {
                y=y0+(y1-y0)*(xmin-x0)/(x1-x0);
                x=xmin;
            }
            if(outcodeOut==outcode0)
            {
                x0=x;
                y0=y;
                outcode0=ComputeOutCode(x0,y0);
            }
            else
            {
                x1=x;
                y1=y;
                outcode1=ComputeOutCode(x1,y1);
            }
        }
    }while(!done);
    if(accept)
    {
        double sx=(xvmax-xvmin)/(xmax-xmin);
        double sy=(yvmax-yvmin)/(ymax-ymin);
        double vx0=xvmin+(x0-xmin)*sx;
        double vy0=yvmin+(y0-ymin)*sy;
        double vx1=xvmin+(x1-xmin)*sx;
        double vy1=yvmin+(y1-ymin)*sy;
        glColor3f(1,0,0);
        glBegin(GL_LINE_LOOP);
        DDALine(xvmin,yvmin,xvmax,yvmin);
        DDALine(xvmax,yvmin,xvmax,yvmax);
        DDALine(xvmax,yvmax,xvmin,yvmax);
        DDALine(xvmin,yvmax,xvmin,yvmin);

        glEnd();
        glColor3f(0,0,1);
        glBegin(GL_LINES);
        glVertex2d(vx0,vy0);
        glVertex2d(vx1,vy1);
        glEnd();
        glFlush();
    }
}

outcode ComputeOutCode(double x,double y)
{
    outcode code=0;
    if(y>ymax)
        code |= TOP;
    else if(y<ymin)
        code |= BOTTOM;
    if(x>xmax)
        code |= RIGHT;
    else if(x<xmin)
        code |= LEFT;
    return code;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    cs(210,50,240,300); //totally outside the window
    cs(50,50,175,180); //totally inside the window
    cs(110,75,220,-90); //one pt. in window, other outside
    cs(-10,50,100,210); //mid segment of line in window
    glFlush();
}

int main(int v,char** w)
{
    glutInit(&v,w);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(400,400);
    glutCreateWindow("Cohen Sutherland");
    init();
    glutDisplayFunc(&display);
    glutMainLoop();
    return 0;
}
