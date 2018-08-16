#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,200.0,0.0,150.0);
}

void linesegment(void)
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0,0.0,0.0);
glBegin(GL_LINES);
    glVertex2i(10,75);
    glVertex2i(10,105);
    glVertex2i(40,75);
    glVertex2i(40,105);
    glVertex2i(10,75);
    glVertex2i(40,75);
    glVertex2i(10,105);
    glVertex2i(40,105);
    glVertex2i(20,75);
    glVertex2i(20,90);
    glVertex2i(30,75);
    glVertex2i(30,90);
    glVertex2i(20,90);
    glVertex2i(30,90);
    glVertex2i(10,105);
    glVertex2i(25,125);
    glVertex2i(25,125);
    glVertex2i(40,105);
    glVertex2i(12,101);
    glVertex2i(12,93);
    glVertex2i(18,101);
    glVertex2i(18,93);

    glVertex2i(32,101);
    glVertex2i(32,93);
    glVertex2i(38,101);
    glVertex2i(38,93);

    glVertex2i(12,93);
    glVertex2i(18,93);
    glVertex2i(12,101);
    glVertex2i(18,101);

    glVertex2i(32,93);
    glVertex2i(38,93);
    glVertex2i(32,101);
    glVertex2i(38,101);
glColor3f(0.5,0.4,0.0);
    glVertex2i(22,77);
    glVertex2i(22,88);
    glVertex2i(28,77);
    glVertex2i(28,88);

    glVertex2i(20,75);
    glVertex2i(22,77);
    glVertex2i(20,90);
    glVertex2i(22,88);

    glVertex2i(28,77);
    glVertex2i(30,75);
    glVertex2i(28,88);
    glVertex2i(30,90);

    glVertex2i(45,120);
    glVertex2i(55,125);
    glVertex2i(45,120);
    glVertex2i(55,115);

    glVertex2i(55,125);
    glVertex2i(60,135);
    glVertex2i(60,135);
    glVertex2i(65,125);

    glVertex2i(65,125);
    glVertex2i(75,120);
    glVertex2i(65,115);
    glVertex2i(75,120);

    glVertex2i(65,115);
    glVertex2i(60,105);
    glVertex2i(55,115);
    glVertex2i(60,105);
glEnd();
glFlush();
}

void main(int argc,char **argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowPosition(50,100);
glutInitWindowSize(400,300);
glutCreateWindow("Line Segment");
init();
glutDisplayFunc(linesegment);
glutMainLoop();
}
