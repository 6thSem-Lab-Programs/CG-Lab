#include<GL/glut.h>
#include<stdio.h>

int x1,x2,Y1,y2;

void myinit() {
	gluOrtho2D(0, 500, 0, 500);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void drawPixel(int x, int y) {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
	glFlush();
}

void drawLine(int x1, int x2, int Y1, int y2) {
	int dx=(x2-x1), dy=(y2-Y1);
	int i, e, incx=1, incy=1, inc1, inc2, x, y;
	if(dx<0) dx=-dx;
	if(dy<0) dy=-dy;
	if(x2<x1) incx=-1;
	if(y2<Y1) incy=-1;
	x=x1;y=Y1;

	if(dx>dy) {
		drawPixel(x, y);
		e = 2*dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for(i=0;i<dx;++i) {
			if(e>=0) {
				y+=incy;
				e+=inc1;
			} else
				e+=inc2;
			x+=incx;
			drawPixel(x, y); 
		}
	} else {
		drawPixel(x, y);
		e = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for(i=0;i<dy;++i) {
			if(e>=0) {
				x+=incx;
				e+=inc1;
			} else
				e+=inc2;
			y+=incy;
			drawPixel(x, y); 
		}
	}
}

void myDisp() {
	drawLine(x1, x2, Y1, y2);
}

int main(int argc, char **argv) {
	printf("\nEnter the End points of the line\n");
	printf("Enter value of x1 : ");
	scanf("%d", &x1);
	printf("Enter value of x2 : ");
	scanf("%d", &x2);
	printf("Enter value of Y1 : ");
	scanf("%d", &Y1);
	printf("Enter value of y2 : ");
	scanf("%d", &y2);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutCreateWindow("Bresenham's Line drawing procedure");
	glutDisplayFunc(myDisp);
	myinit();
	glutMainLoop();
	return 0;
}
