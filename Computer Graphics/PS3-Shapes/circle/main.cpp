# include <GL/glut.h>
# include <cmath>

void Init ()
{
    glClearColor(1.0,0.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,500,0,500);
}

void DrawCircle (int x, int y, int xc, int yc)
{
    glBegin (GL_POINTS);
    glColor3f (0.0, 0.0, 0.0);
    glVertex2i ((x+xc), y+yc);
    glVertex2i (y+xc, x+yc);
    glVertex2i (-y+xc, -x+yc);
    glVertex2i (x+xc, -y+yc);
    glVertex2i (-x+xc, -y+yc);
    glVertex2i (-y+xc, x+yc);
    glVertex2i (y+xc, -x+yc);
    glVertex2i (-x+xc, y+yc);
    glEnd ();
    glFlush ();
}

void MyCircle (int r, int xc, int yc)
{
    int d=1-r, x=0, y=r;
    DrawCircle (x, y, xc, yc);
    while (y>x)
    {
        if (d<0)
        {
            d = d + 2*x +3;
            x++;
        }
        else if (d>=0)
        {
            d = d + 2*x - 2*y + 5;
            x++;
            y--;
        }
        DrawCircle (x, y, xc, yc);
    }
}

void display ()
{
    glClearColor (1.0, 1.0, 0.0, 1.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 1.0);

MyCircle (100, 250, 250);
    glFlush ();
}

int main (int argc, char ** argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("My Circle");
    Init();
    glutDisplayFunc(&display);
    glutMainLoop();
}
