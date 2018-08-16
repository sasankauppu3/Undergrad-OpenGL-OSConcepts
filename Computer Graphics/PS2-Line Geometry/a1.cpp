#include<GL/glut.h>
#include<GL/glu.h>
#include<GL/gl.h>
#include<iostream>
#include<math.h>

using namespace std;

int step=1;
int r=1,g=1,b=1;

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200,200,-200,200);
}

void setPixel(GLdouble x, GLdouble y)
{
    glColor3f(::r,::g,::b);
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
char IncFlag;
void BresenhamLine(int x1,int y1,int x2,int y2)
{
     int S,O,End;
    int P;
    int dx = abs(x1 - x2);
    int dy = abs(y1 - y2);
    float Slope;
    int PInc,NInc,XInc,YInc;
    if (dx != 0)  //Slope Infinite
    {
        Slope = (float)(y1 - y2) / (x1 - x2);
        if (abs(y1-y2)<abs(x1-x2) && abs(y1-y2)>abs(x1-x2))
        {
            IncFlag = 'X';
            PInc = 2 * (dy - dx);
            NInc = 2 * dy;
            P = 2 * dy - dx;
            if (x1>x2)
            {
                S = x2;
                O = y2;
                End = x1;
            }
            else
            {
                S = x1;
                O = y1;
                End = x2;
            }
//            DrawLine(x,y,End,PInc,NInc,P,XInc,YInc);
        }
        else
        {
            IncFlag = 'Y';
            PInc = 2 * (dx - dy);
            NInc = 2 * dx;
            P = 2 * dx - dy;
            if (y1 > y2)
            {
                O = x2;
                S = y2;
                End = y1;
            }
            else
            {
                O = x1;
                S = y1;
                End = y2;
            }
        }
        if (IncFlag == 'X')
            setPixel(S,O);
        else
            setPixel(O,S);
        while (S <= End)
        {
            S++;
            if (P<0)
                P = P + NInc;
            else
            {
                P = P + PInc;
                if (Slope>0.0)
                    O++;
                else
                    O--;
            }
            if (IncFlag == 'X')
                setPixel(S,O);
            else
                setPixel(O,S);
        }
    }

}



void AllCasesMidPointLine(int x1,int y1,int x2,int y2)
{
    bool steep = abs(y2 - y1) > abs(x2 - x1);
    if(steep)
    {
        // swap x1 and y1
        int tmp = x1;
        x1 = y1;
        y1 = tmp;
        // swap x2 and y2
        tmp = x2;
        x2 = y2;
        y2 = tmp;
    }

    if(x1 > x2)
    {
        // swap x1 and x2
        int tmp = x1;
        x1 = x2;
        x2 = tmp;
        // swap y1 and y2
        tmp = y1;
        y1 = y2;
        y2 = tmp;
    }

    int dx, dy, error, ystep, y;

    dx = x2 - x1;
    dy = abs(y2 - y1);
    error = dx / 2;
    y = y1;

    if(y1 < y2)
        ystep = 1;
    else
        ystep = -1;


    for (int x = x1; x <= x2; x++)
    {
        if(steep)
            setPixel(y, x);
        else
            setPixel(x, y);
        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }

}

void DDAdisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);

    GLdouble x1,y1,x2,y2;

    cout<<"\n Enter x1,y1,x2 and y2 \n";
    cin>>x1>>y1>>x2>>y2;

    DDALine(x1,y1,x2,y2);

}

void BLAdisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);

    int x0,y0,x1,y1;

    cout<<"\n Enter x0,y0,x1 and y1 \n";
    cin>>x0>>y0>>x1>>y1;

    BresenhamLine(x0,y0,x1,y1);

}


void image()
{
    glClear(GL_COLOR_BUFFER_BIT);


    DDALine(40,40,120,40);
    DDALine(80,0,80,80);
    DDALine(50,30,110,50);
    DDALine(50,50,110,30);
    DDALine(70,10,90,70);
    DDALine(90,10,70,70);
}

void MPdisplay2()
{
    glClear(GL_COLOR_BUFFER_BIT);

    int x0,y0,x1,y1;

    cout<<"\n Enter x0,y0,x1 and y1 \n";
    cin>>x0>>y0>>x1>>y1;

    AllCasesMidPointLine(x0,y0,x1,y1);
}

int main(int argc,char** argv)
{
    glutInit(&argc , argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(500,380);
    glutCreateWindow("Line Program ");
    init();

    int ch,dottedChoice,R,G,B;
    char choice;

    do
    {

    /*
    cout<<"\n Do you want dotted lines ? ";
    cin>>choice;

    if(choice=='y'||choice=='Y')
    {
        ::step=4;
    }

    */

    cout<<"\n Enter Color in R,G,B \n";
    cin>>::r>>::g>>::b;

    cout<<"\n Menu \n 1.DDA Line \n 2. Bresenham's Line \n 3.Mid Point Line 4.Image";
    cout<<"\n Enter Choice ";
    cin>>ch;

    switch(ch)
    {
        case 1:

        glutDisplayFunc(DDAdisplay);
        glutMainLoop();
        break;

        case 2:

        glutDisplayFunc(BLAdisplay);
        glutMainLoop();
        break;

        case 3:

        glutDisplayFunc(MPdisplay2);
        glutMainLoop();
        break;
 case 4:

        glutDisplayFunc(image);
        glutMainLoop();
        break;
        default:
        exit(0);

    }

    }
    while(1);

    //glutMainLoop();




}

