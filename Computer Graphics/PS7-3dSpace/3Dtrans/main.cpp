#include<iostream>
#include<GL/glut.h>
#include<math.h>
#include<time.h>
#include<stdio.h>

using namespace std;


float x[5]={0,50,50,0,25};
float y[5]={0,0,0,0,100};
float z[5]={0,0,50,50,25};
float xc=(50+50+25)/5;
float yc=(-125)/5;
float zc=(50+50+25);

void myInit(void)
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-300,300,-300,300);
}

void WritePixel(int x,int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void drawline(int x1,int y1,int x2,int y2)
{
    glBegin(GL_LINES);
    glVertex2i(x1,y1);
    glVertex2i(x2,y2);
    glEnd();
    glFlush();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    float xp[5],yp[5];
    float xcc,ycc;
    int i;
    for(i=0;i<5;i++)
    {
       xp[i]=x[i]+((z[i]/tan(1.1))*cos(.79));
       yp[i]=y[i]+((z[i]/tan(1.1))*cos(.79));
    }
    xcc=xc+((zc/tan(1.1))*cos(.79));
    ycc=yc+((zc/tan(1.1))*cos(.79));
    glColor3f(0.1,0.1,0.1);
    glBegin(GL_POLYGON);
        glVertex2i(xp[0],yp[0]);
        glVertex2i(xp[1],yp[1]);
        glVertex2i(xp[4],yp[4]);
    glEnd();

    glColor3f(0.15,0.55,0.0);
    glBegin(GL_POLYGON);
        glVertex2i(xp[1],yp[1]);
        glVertex2i(xp[4],yp[4]);
        glVertex2i(xp[2],yp[2]);
    glEnd();

    glColor3f(0.25,0.65,0);
    glBegin(GL_POLYGON);
        glVertex2i(xp[2],yp[2]);
        glVertex2i(xp[4],yp[4]);
        glVertex2i(xp[3],yp[3]);
        glEnd();


    glColor3f(0.35,0.85,0);
    glBegin(GL_POLYGON);
        glVertex2i(xp[3],yp[3]);
        glVertex2i(xp[4],yp[4]);
        glVertex2i(xp[0],yp[0]);
    glEnd();

    glColor3f(0.8,1.0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(xp[0],yp[0]);
        glVertex2i(xp[1],yp[1]);
        glVertex2i(xp[3],yp[3]);
        glVertex2i(xp[2],yp[2]);
    glEnd();


    glFlush();
}

void translate(float tx,float ty, float tz)
{   int i;
    for(i=0;i<5;i++)
    {
        x[i]+=tx;
        y[i]+=ty;
        z[i]+=tz;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    display();
}
void scale(float sx,float sy, float sz)
{   int i;
    for(i=0;i<5;i++)
    {
        x[i]*=sx;
        y[i]*=sy;
        z[i]*=sz;
    }
    display();
}
void xrotate(float rad)
{   float  temp1,temp2,temp3;
    int i;
    for(i=0;i<5;i++)
    {
        temp1=x[i];
        temp2=y[i];
        temp3=z[i];

        y[i]=(temp2*cos(rad))-(temp3*(sin(rad)));
        z[i]=(temp2*sin(rad))+(temp3*cos(rad));
    }
    display();
}
void yrotate(float rad)
{   float  temp1,temp2,temp3;
    int i;
    for(i=0;i<5;i++)
    {
        temp1=x[i];
        temp2=y[i];
        temp3=z[i];

        x[i]=(temp1*cos(rad))+(temp3*(sin(rad)));
        z[i]=-(temp1*sin(rad))+(temp3*cos(rad));
    }
    display();
}
void zrotate(float rad)
{   float  temp1,temp2,temp3;
    int i;
    for(i=0;i<5;i++)
    {
        temp1=x[i];
        temp2=y[i];
        temp3=z[i];

        x[i]=(temp1*cos(rad))-(temp2*(sin(rad)));
        y[i]=(temp1*sin(rad))+(temp2*cos(rad));
    }
    display();
}

void rotatecent()
{

    int i,j;
    float r=1.8;
    yrotate(1.0);
    r-=0.1;
}
void myKey(unsigned char key, int x, int y)
{
    int i=0;
    if(key == 't')
    {
        cout<<"Hello";
        translate(0,10,0);
    }
    if(key == 'g')
    {
        translate(0,-10,0);
    }
    if(key == 's')
    {
        scale(1.2,1.2,1.2);
    }
    if(key == 'a')
    {
        scale(0.5,0.5,0.5);
    }
    if(key == 'x')
    {
        xrotate(.1);
    }
    if(key == 'y')
    {
        yrotate(0.1);
    }
    if(key == 'z')
    {
        zrotate(.1);
    }
}


int main(int argc,char** argv)
{
    cout<<"t.Translate \n g.Translate \n s.Scale \n a.Scale \n x.rotate(x) \n y.rotate(y) \n z.rotate(z) \n ";
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("3d");
    myInit();
    glutKeyboardFunc(&myKey);
    glutDisplayFunc(&display);
    glutMainLoop();
    return 0;
}
