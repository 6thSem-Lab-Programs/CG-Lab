#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

float x1,x2,x3,x4,Y1,y2,y3,y4;
int choice = 0;
void edgedetect(float x1,float Y1,float x2,float y2,int *le,int *re) {
        float mx,x,temp;
        int i;
        if((y2-Y1)<0) {
            temp=Y1;
            Y1=y2;
            y2=temp;
            temp=x1;
            x1=x2;
            x2=temp;
        }
        if((y2-Y1)!=0)
            mx=(x2-x1)/(y2-Y1);
        else
            mx=x2-x1;
        x=x1;
        for(i=Y1;i<=y2;i++) {
                if(x<(float)le[i]) le[i]=(int)x;
                if(x>(float)re[i]) re[i]=(int)x;
                x+=mx;
        }
}

void drawpixel(int x,int y) {
        glColor3f(1.0,1.0,0.0);
        glBegin(GL_POINTS);
        	glVertex2i(x,y);
        glEnd();
    	glFlush();
}

void scanfill(float x1,float Y1,float x2,float y2,float x3,float y3,float x4,float y4) {
    int le[500],re[500];
    int i,y;
    for(i=0;i<500;i++) {
        le[i]=500;
        re[i]=0;
    }
    edgedetect(x1,Y1,x2,y2,le,re);
    edgedetect(x2,y2,x3,y3,le,re);
    edgedetect(x3,y3,x4,y4,le,re);
    edgedetect(x4,y4,x1,Y1,le,re);
    for(y=0;y<500;y++) {
        if((le[y]<=re[y]))
           for(i=(int)le[y];i<=(int)re[y];i++)
                drawpixel(i,y);
    }
}

void display() {
    x1=200.0,Y1=200.0,x2=100.0,y2=300.0,x3=200.0,y3=400.0,x4=300.0,y4=300.0;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,0.0);
    if(choice == 1) {
  	  glBegin(GL_LINE_LOOP);
    		glVertex2f(x1,Y1);
 	   	glVertex2f(x2,y2);
    		glVertex2f(x3,y3);
    		glVertex2f(x4,y4);
  	  glEnd();
    }
    if(choice == 2)
   	 scanfill(x1,Y1,x2,y2,x3,y3,x4,y4);
    glFlush();
}

void myinit() {
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(1.0,0.0,0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,500.0,0.0,500.0);
}

void mymenu(int id) {
        //glClear(GL_COLOR_BUFFER_BIT);
	choice=0;
	switch(id) {
		case 1 : exit(0);
		case 2 : choice = 1;
			 break;
		case 3 : choice = 2;
			 break;
	}
	glutPostRedisplay();
}

int main(int argc,char **argv) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Scan Line Algorithm");
    int sub_menu = glutCreateMenu(mymenu);
    glutAddMenuEntry("Draw Polygon",2);
    glutAddMenuEntry("Fill Polygon",3);
    glutCreateMenu(mymenu);
    glutAddMenuEntry("Exit",1);
    glutAddSubMenu("Polygon",sub_menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
    return 1;
}
