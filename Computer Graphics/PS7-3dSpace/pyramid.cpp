#include<GL/glut.h>
#include<cmath>
#include<time.h>
 
using namespace std;

float phi = (3.141/180)*45;
float alpha = (3.141/180)*63.4;
float theta = (3.141/180)*15;


float py[4][6] = {-50,  50,50,-50, 0, 0,
                  0, 0, 0, 0, 100, -100,
                  -50, -50, 50, 50, 0, 0,
                  1, 1, 1, 1,1,1,
                    };

float m[4][4] = { 1, 0, cos(phi)/tan(alpha), 0 ,
                  0, 1, sin(phi)/tan(alpha), 0,
                  0, 0, 0, 0,
                  0, 0, 0, 1
                };

float Ry[4][4] = { cos(theta),   0,     sin(theta),  0,
                    0,           1,      0,          0,
                   -sin(theta),  0,      cos(theta), 0,
                    0,           0,      0,          1
                    };

float p1[4][1] = {0};
float p2[4][1] = {0};

float a[3][6] = {0};

void myInit() {
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-400,400,-400,400);
}


void delay (unsigned int sec) {
    clock_t t = sec + clock();
    while(t>clock());
}


void MatMul(float a[4][4],float b[4][1], float c[4][1]) {
    for(int i=0;i<4;i++)
        for(int j=0,k=0;j<4;j++,k++)
            c[i][0] += a[i][k] * b[k][0];

}

void DrawPyramid()
{
    glClear(GL_COLOR_BUFFER_BIT);
    float r = (rand()%100)/100.0;
    float g = (rand()%100)/100.0;
    float b = (rand()%100)/100.0;

    glColor3f(r,g,b);

    for(int j=0;j<6;j++) {           //Number of Points of Polygon
        for(int i=0;i<4;i++) {
            p2[i][0]=0;
            p1[i][0]=py[i][j];
        }

        MatMul(m,p1,p2);
        a[0][j]=p2[0][0];
        a[1][j]=p2[1][0];
        a[2][j]=p2[3][0];
    }

    glBegin(GL_LINE_LOOP);

    for(int i=0;i<4;i++)
        glVertex2i(a[0][i],a[1][i]);

    glEnd();

    glBegin(GL_LINES);
        //Top Edge
        glVertex2i(a[0][0],a[1][0]);
        glVertex2i(a[0][4],a[1][4]);

        glVertex2i(a[0][1],a[1][1]);
        glVertex2i(a[0][4],a[1][4]);

        glVertex2i(a[0][2],a[1][2]);
        glVertex2i(a[0][4],a[1][4]);

        glVertex2i(a[0][3],a[1][3]);
        glVertex2i(a[0][4],a[1][4]);

        //Bottom Edge
        glVertex2i(a[0][0],a[1][0]);
        glVertex2i(a[0][5],a[1][5]);

        glVertex2i(a[0][1],a[1][1]);
        glVertex2i(a[0][5],a[1][5]);

        glVertex2i(a[0][2],a[1][2]);
        glVertex2i(a[0][5],a[1][5]);

        glVertex2i(a[0][3],a[1][3]);
        glVertex2i(a[0][5],a[1][5]);

    glEnd();

    glFlush();
}

void mykey(unsigned char key, int , int ) {
    if(key=='r') {
        while(true) {
            for(int j=0;j<6;j++) {           //Number of Points of Polygon
                for(int i=0;i<4;i++) {
                    p2[i][0]=0;
                    p1[i][0]=py[i][j];
                }

                MatMul(Ry,p1,p2);

                for(int i=0;i<4;i++)
                    py[i][j] = p2[i][0];
            }
            DrawPyramid();
            delay(90000);
        }
    }
}

void display() {
    glClearColor(1.0,1.0,0.5,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);

    DrawPyramid();
}

int main(int argc, char** argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(650,650);
    glutInitWindowPosition(50,50);
    glutCreateWindow("3-D Transformations");
    myInit();

    glutDisplayFunc(&display);
    glutKeyboardFunc(mykey);
    glutMainLoop();
}
