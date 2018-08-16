#include<GL/glut.h>
#include <unistd.h>
#include<stdio.h>
#include<iostream>

using namespace std;

#define WINDOW_HEIGHT 480

void setPixel(int x, int y);


typedef struct tdcPt{
    int x;
    int y;
}dcPt;

typedef struct tEdge {
    int yUpper;
    float xIntersect, dxPerScan;
    struct tEdge * next;
}Edge;


void insertEdge(Edge *list, Edge *edge)
{
    Edge *p, *q = list;
    p = q->next;
    while(p != NULL) {
        if(edge->xIntersect < p->xIntersect)
            p = NULL;
        else {
            q = p;
            p = p->next;
        }
    }
    edge->next = q->next;
    q->next = edge;
}

int yNext(int k, int cnt, dcPt *pts)
{
    int j;
    if((k+1) > (cnt-1))
        j = 0;
    else
        j = k+1;
    while(pts[k].y == pts[j].y)
        if((j+1) > (cnt-1))
            j=0;
        else
            j++;
    return pts[j].y;
}



void makeEdgeRec(dcPt lower, dcPt upper, int yComp, Edge *edge, Edge *edges[])
{
    edge->dxPerScan = (float) (upper.x - lower.x) / (upper.y - lower.y);
    edge->xIntersect = lower.x;
    if(upper.y < yComp)
        edge->yUpper = upper.y - 1;
    else
        edge->yUpper = upper.y;
    insertEdge(edges[lower.y], edge);
}

void buildEdgeList(int cnt, dcPt *pts, Edge *edges[])
{
    Edge *edge;
    dcPt v1, v2;
    int i, yPrev = pts[cnt - 2].y;
    v1.x = pts[cnt-1].x;
    v1.y = pts[cnt-1].y;

    for (i=0; i<cnt; i++) {
        v2 = pts[i];
        if(v1.y != v2.y) {
            edge = (Edge*)malloc(sizeof(Edge));
            if(v1.y < v2.y)
                makeEdgeRec(v1, v2, yNext(i, cnt, pts), edge, edges);
            else
                makeEdgeRec(v2, v1 , yPrev, edge, edges);
        }
        yPrev = v1.y;
        v1 = v2;
    }
}

void buildActiveList(int scan, Edge *active, Edge *edges[])
{
    Edge *p, *q;
    p = edges[scan]->next;
    while(p) {
        q = p->next;
        insertEdge(active,p);
        p = q;
    }
}

void fillScan(int scan, Edge *active)
{
    Edge *p1, *p2;
    int i;
    p1 = active->next;
    while (p1) {
        p2 = p1->next;
        for(i=p1->xIntersect; i< p2->xIntersect; i++)
             setPixel((int) i, scan);
        p1 = p2->next;
    }
}

void deleteAfter(Edge *q)
{
    Edge *p = q->next;
    q->next = p->next;
    free(p);
}



void updateActiveList(int scan, Edge *active)
{
    Edge *q = active, *p = active->next;
    while(p)
        if(scan >= p->yUpper){
            p = p->next;
            deleteAfter(q);
        }
        else {
            p->xIntersect = p->xIntersect + p->dxPerScan;
            q = p;
            p = p->next;
        }
}

void resortActiveList(Edge *active)
{
    Edge *q, *p = active->next;
    active->next = NULL;
    while(p){
        q = p->next;
        insertEdge(active, p);
        p = q;
    }
}

void scanFill(dcPt *pts,int cnt)
{
    Edge *edges[WINDOW_HEIGHT], *active;
    int i, scan;
    for (i=0; i<WINDOW_HEIGHT;i++){
        edges[i] = (Edge*)malloc(sizeof(Edge));
        edges[i]->next = NULL;

    }
    buildEdgeList(cnt, pts, edges);
    active = (Edge*)malloc(sizeof(Edge));
    active->next = NULL;
    for(scan=0;scan<WINDOW_HEIGHT;scan++){
        buildActiveList(scan, active, edges);
        if(active->next){
            fillScan(scan, active);
            updateActiveList(scan, active);
            resortActiveList(active);
        }
    }
}


float boundaryColor[3] = {1,0,0};
float fillColor[3] = {1,1,0};

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
void setPixel(int x, int y)
{
    glColor3fv(fillColor);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}

void drawPolygon(dcPt *points, int n)
{
    glColor3fv(boundaryColor);
    glBegin(GL_LINE_LOOP);
    for(int i=0;i<n;i++)
       glVertex2i(points[i].x, points[i].y);
    glEnd();
}


/******
Make Array of points
Input : (int [])x1,y1,x2,y2....,size
Output : array of points [size]
******/

dcPt *makePoints(int *pts,int n)
{
    dcPt *points = new dcPt[n];

    for(int i=0,j=0;i<n;i++)
    {
        points[i].x = pts[j++];
        points[i].y = pts[j++];
    }
    return points;
}

void display()
{

    int a[]={30,50,90,50,90,90,30,90,20,60,10,100,30,120,100,120,120,70,100,30,30,30};
    dcPt *polygon1 = makePoints(a,11);
    drawPolygon(polygon1,11);
    scanFill(polygon1,11);


    glFlush();
}

int main(int argc, char**argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Scan Line Filling");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}
