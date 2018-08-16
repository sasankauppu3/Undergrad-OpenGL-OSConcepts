#include<iostream>
#include<stdio.h>
#include<GL/glut.h>
 
using namespace std;

//int radius = 90;
//int longitude=20;
//int latitude=20;

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    //glMatrixMode(GL_PROJECTION);
   // gluOrtho2D(-500,500,-500,500);
       glShadeModel (GL_FLAT);
}
int day=0;
int sphere=0,cone=0,teapot=0;

void display()
{
 glColor3f(1.0,0.0,0.0);
glClear(GL_COLOR_BUFFER_BIT);
//glTranslatef(0.0,0.0,0.0);

glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
//if(cone){
//glutWireCone(0.5, 0.9, 40, 50);
glRotatef ((GLfloat) cone, 1.0, 1.0, 0.0);
//}
glColor3f(0.0,1.0,0.0);

//if(sphere)
//glutWireSphere(0.5,20,20);

glColor3f(0.0,0.0,1.0);

//if(teapot)
glutWireTeapot(0.4);

cone=0,sphere=0,teapot=0;
glFlush();
}
/*
void delay(unsigned int sec)
{
    clock_t t = sec+clock();
    while(t>clock());
}

void display2()
{
    glColor3f(1.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    while(1)
    {
        day = (day+1)%360;
        glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
        glutWireTeapot(0.4);
        delay(99);

    }
}
*/

void mykey(unsigned char key,int,int)
{
    switch(key)
    {
        case 'c':
        cone=1;
        //day = (day + 1) % 360;
        glutPostRedisplay();
        break;
        case 's':
        sphere=1;
        //day = (day + 1) % 360;
        glutPostRedisplay();
        break;
        case 't':
        teapot=1;
        //day = (day + 1) % 360;
        glutPostRedisplay();
        case 'a':
             cone=1;
        //day = (day - 1) % 360;
        glutPostRedisplay();
        //display2();
        break;
    }
}

int main(int argc,char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(500,100);
    glutCreateWindow("3-D transformations");
    init();
     glutDisplayFunc(display);
     glutKeyboardFunc(mykey);
    glutMainLoop();
}
