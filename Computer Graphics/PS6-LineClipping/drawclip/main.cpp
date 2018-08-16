#include<GL/glut.h>
#include<stdio.h>
#include<iostream>
#include<math.h>
#include<stdlib.h>

#define LEFT 4
#define RIGHT 3
#define BOTTOM 2
#define TOP 1

using namespace std;
int xmin,ymin,xmax,ymax,k=0;

char ch;

class Vertex
{
    public:
        int x,y;
        Vertex()
        {}
        Vertex(int a,int b)
        {
            x=a;y=b;
        }
}outV[100];

void writepixel(int x,int y)
{
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
}



void DrawClip()
{
    glColor3f(0.0,0.2,0.6);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin,ymin);
    glVertex2i(xmax,ymin);
    glVertex2i(xmax,ymax);
    glVertex2i(xmin,ymax);
    glVertex2i(xmin,ymin);
    glEnd();
    glFlush();
}

bool Inside(Vertex v,int code)
{
    switch(code)
    {
        case 1: if(v.y>ymax)
                    return false;
                return true;
                break;
        case 2: if(v.y<ymin)
                    return false;
                return true;
                break;
        case 3: if(v.x>xmax)
                    return false;
                return true;
                break;
        case 4: if(v.x<xmin)
                    return false;
                return true;
                break;
    }
}

void delay(double ms)
{
    ms*=1000;
    clock_t g1=clock();
    clock_t g2=clock();
    while((g2-g1)<ms)
    {
        g2=clock();
       // cout<<g2<<endl;
    }
}
Vertex Intersect(Vertex S,Vertex P,int code)
{
    int x1,y1,x2,y2;
    if(S.x==P.x)
    {
        x1=S.x;
        x2=S.x;
        if(S.y<P.y)
        {
            y1=S.y;
            y2=P.y;
        }
        else
        {
            y1=P.y;
            y2=S.y;
        }
    }
    x1 = S.x < P.x ? S.x:P.x;

    if(x1==S.x)
    {
        x2=P.x;
        y1=S.y;
        y2=P.y;
    }
    else
    {
        x2=S.x;
        y1=P.y;
        y2=S.y;
    }
    float m=(float)(y2-y1)/(x2-x1);
    Vertex V;

    switch(code)
    {
        case 1: V.y=ymax;
                V.x=x1+(1/m)*(ymax-y1);
                break;
        case 2: V.y = ymin;
                V.x=x1+(1/m)*(ymin-y1);
                break;
        case 3: V.x=xmax;
                V.y=y1+m*(xmax-x1);
                break;
        case 4: V.x=xmin;
                V.y=y1+m*(xmin-x1);
                break;
    }
    return V;
}

void Output(Vertex V)
{
    outV[k].x=V.x;
    outV[k].y=V.y;
    k++;
}

void shpc(Vertex inV[],int inL,int code)
{
    Vertex S,P,i;
    S=inV[inL-1];

    for(int j=0;j<inL;j++)
    {
        P=inV[j];
        if(Inside(P,code))
        {
            if(Inside(S,code))
                Output(P);
            else
            {
                i=Intersect(S,P,code);
                Output(i);
                Output(P);
            }
        }
        else
        {
            if(Inside(S,code))
            {
                i=Intersect(S,P,code);
                Output(i);
            }
        }
        S=P;
    }
    cout<<"\n Clipping Function";
    cout<<S.x<<"   "<<P.x;
}

void DrawClipped()
{

    int x1,y1,x2,y2;
    Vertex S=outV[k-1];
    Vertex P;

    for(int j=0;j<k;j++)
    {
        P=outV[j];
        if(S.x == P.x)
        {
            x1=S.x;
            x2=S.x;
            if(S.y<P.y)
            {
                y1=S.y;
                y2=P.y;
            }
            else
            {
                y1=P.y;
                y2=S.y;
            }
        }
        else
        {
            x1=S.x<P.x?S.x:P.x;
            if(x1==S.x)
            {
                x2=P.x;
                y1=S.y;
                y2=P.y;
            }
            else
            {
                x2=S.x;
                y1=P.y;
                y2=S.y;
            }
        }
        cout<<"\n Draw Clipped ";
        cout<<x1<<","<<y1<<"   "<<x2<<","<<y2<<endl;
        glColor3f(0.1,0.5,0.9);
        glBegin(GL_LINES);
        glVertex2i(x1,y1);
        glVertex2i(x2,y2);
        glEnd();
        glFlush();
        S=P;
        delay(1000);
    }
}

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(0.0,640.0,0.0,480.0);
}

void clipAll(Vertex inV[],int inL)
{
    //just Do all of them
    //Clip Left
    shpc(inV,inL,4);
    for(int i=0;i<k;i++)
        inV[i]=outV[i];
    inL=k;
    k=0;

    //Clip Right
    shpc(inV,inL,3);
    for(int i=0;i<k;i++)
        inV[i]=outV[i];
    inL=k;
    k=0;

    //Clip Bottom
    shpc(inV,inL,2);
    for(int i=0;i<k;i++)
        inV[i]=outV[i];
    inL=k;
    k=0;
    shpc(inV,inL,1);

    glFlush();
    DrawClipped();

}

void display()
{
    glClearColor(1.0,1.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.5);


    xmin=50;
    ymin=100;
    xmax=250;
    ymax=300;
    glBegin(GL_LINE_LOOP);
  glVertex2i(30,200),
    glVertex2i(100,250),
    glVertex2i(150,320),
    glVertex2i(200,250),
    glVertex2i(270,200),
    glVertex2i(200,150),
    glVertex2i(150,80),
    glVertex2i(100,150),
    glEnd();
    glFlush();

    Vertex inV[100]={Vertex(30,200),
    Vertex(100,250),
    Vertex(150,320),
    Vertex(200,250),
    Vertex(270,200),
    Vertex(200,150),
    Vertex(150,80),
    Vertex(100,150),
    };

    int inL=8;
    DrawClip();

    clipAll(inV,inL);

    return;
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutCreateWindow("Polygon_Clipping");
    init();
    glutDisplayFunc(display);
    //glutKeyboardFunc(myKey);
    glutMainLoop();
    return 0;
}
