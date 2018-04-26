#include<stdio.h>
#include<GL/glut.h>
#include<stdbool.h>:
#define outcode int
double xmin=50,ymin=50,xmax=100,ymax=100;
double xvmin=200,yvmin=200,xvmax=300,yvmax=300;
float x0[4],y0[4],x1[4],y1[4];
const int RIGHT=2;
const int LEFT=1;
const int TOP=8;
const int BOTTOM=4;
int i;
outcode Computeoutcode(double x, double y);
void cohensutherlandlineclipanddraw(double x0,double y0,double x1,double y1)
{
    outcode outcode0,outcode1,outcodeout;
    bool accept=false,done=false;
    outcode0=Computeoutcode(x0,y0);
    outcode1=Computeoutcode(x1,y1);
    do
    {
     if(!(outcode0 | outcode1))
     {
         accept=true;
         done=true;
     }
     else if(outcode0 &outcode1)
        done=true;
     else
     {

         double x,y;
         outcodeout=outcode0? outcode0:outcode1;
         if(outcodeout & TOP)
         {
             x=x0+(x1-x0) * (ymax-y0)/(y1-y0);
             y=ymax;
         }
         else if(outcodeout & BOTTOM)
         {
             x=x0+(x1-x0) * (ymin-y0)/(y1-y0);
             y=ymin;
         }
         else if(outcodeout & RIGHT)
         {
             y=y0+(y1-y0) * (xmax-x0)/(x1-x0);
             x=xmax;
         }
         else
         {
           y=y0+(y1-y0) * (xmin-x0)/(x1-x0);
           x=xmin;
         }
         if(outcodeout==outcode0)
         {
             x0=x;
             y0=y;
             outcode0=Computeoutcode(x0,y0);
         }
         else
         {
             x1=x;
             y1=y;
             outcode1=Computeoutcode(x1,y1);
         }
     }
    }
    while(!done);
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xvmin,yvmin);
    glVertex2f(xvmax,yvmin);
    glVertex2f(xvmax,yvmax);
    glVertex2f(xvmin,yvmax);
    glEnd();
    printf("\n %f %f: %f %f",x0,y0,x1,y1);
    if(accept)
    {
        double sx=(xvmax-xvmin)/(xmax-xmin);
        double sy=(yvmax-yvmin)/(ymax-ymin);
        double vx0=xvmin+(x0-xmin)*sx;
        double vy0=yvmin+(y0-ymin)*sy;
        double vx1=xvmin+(x1-xmin)*sx;
        double vy1=yvmin+(y1-ymin)*sy;
        glColor3f(0.0,0.0,1.0);
        glBegin(GL_LINES);
        glVertex2d(vx0,vy0);
        glVertex2d(vx1,vy1);
        glEnd();

    }
}
outcode Computeoutcode(double x,double y)
{
    outcode code=0;
    if(y>ymax)
    code |=TOP;
    else if(y<ymin)
    code |=BOTTOM;
    if(x>xmax)
    code |=RIGHT;
    else if(x<xmin)
    code |=LEFT;
    return code;
}
void display()
{
   // double x0=120,y0=16,x1=40,y1=130;
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    for(i=0;i<4;i++){
        glVertex2d(x0[i],y0[i]);
        glVertex2d(x1[i],y1[i]);
    }
    glEnd();
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin,ymin);
    glVertex2f(xmax,ymin);
    glVertex2f(xmax,ymax);
    glVertex2f(xmin,ymax);
    glEnd();
    for(i=0;i<4;i++){
    cohensutherlandlineclipanddraw(x0[i],y0[i],x1[i],y1[i]);
   } glFlush();
}
void myinit()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(1.0,0.0,0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
}
int main(int argc,char** argv)
{
    printf("Enter the EndPoints");
    for( i=0;i<4;i++){
            scanf("%f %f %f %f",&x0[i],&y0[i],&x1[i],&y1[i]);
    }
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("cohen Sutherland Line clipping algorithm");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
}
