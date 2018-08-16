#include<GL/glut.h>
#include<GL/gl.h>
float fillc[3]={1.0,0.0,0.0},boundc[3]={0.0,0.0,1.0};
void myinit()
{
    glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(0.0,640.0,0.0,480.0);
}
void boundcfill(float x,float y,float fillc[3],float boundc[3])
{
  float current[3];
  glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,current);
  if(((current[0] != boundc[0])||(current[1] != boundc[1])||(current[2] != boundc[2]))&&((current[0] != fillc[0])||(current[1] != fillc[1])||(current[2] != fillc[2])))
 {
	glBegin(GL_POINTS);
	glColor3f(fillc[0],fillc[1],fillc[2]);
	glVertex2f(x,y);
	glEnd();
	glFlush();
	boundcfill(x-1,y,fillc,boundc);
	boundcfill(x+1,y,fillc,boundc);
	boundcfill(x,y+1,fillc,boundc);
	boundcfill(x,y-1,fillc,boundc);
	boundcfill(x-1,y+1,fillc,boundc);
	boundcfill(x+1,y+1,fillc,boundc);
	boundcfill(x-1,y-1,fillc,boundc);
	boundcfill(x+1,y-1,fillc,boundc);
  }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINES);
    glVertex2f(20.0,100.0);
    glVertex2f(20.0,200.0);
    glVertex2f(20.0,100.0);
    glVertex2f(200.0,100.0);
    glVertex2f(200.0,100.0);
    glVertex2f(200.0,200.0);
    glVertex2f(200.0,200.0);
    glVertex2f(20.0,200.0);
    glEnd();
    glFlush();
    boundcfill(150.0,145.0,fillc,boundc);
}
int main(int argc,char *argv[])
{
glutInit(&argc,argv);
glutInitWindowSize(640,480);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutCreateWindow("boundc_Fill");
myinit();
glutDisplayFunc(display);
glutMainLoop();
return 0;
}
