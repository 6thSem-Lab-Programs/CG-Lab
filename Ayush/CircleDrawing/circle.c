#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

int xc,yc,r;

void myinit() {
	gluOrtho2D(0, 500, 0, 500);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void drawPixel(int x, int y) {
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POINTS);
		glVertex2i(xc+x, yc+y);
		glVertex2i(xc+y, yc+x);
		glVertex2i(xc+x, yc-y);
		glVertex2i(xc+y, yc-x);
		glVertex2i(xc-y, yc-x);
		glVertex2i(xc-x, yc-y);
		glVertex2i(xc-x, yc+y);
		glVertex2i(xc-y, yc+x);
	glEnd();
	glFlush();
}


void drawCircle() {
	int p = 1-r;
	int x=0, y=r;
	for(x=0;x< y;++x) {
		if(p<0) {
			p=p+(2*x)+3;
			drawPixel(x,y);
		} else {
			p=p+(2*x)-(2*y)+5;
			y-=1;
			drawPixel(x,y);
		}
	}
}

void myDisp() {
	drawCircle();
}

int main(int argc, char **argv) {
	printf("\nEnter Coordinates for the centre of the Circle :\n");
	printf("Enter value of x : ");
	scanf("%d", &xc);
	printf("Enter value of y : ");
	scanf("%d", &yc);
	printf("Enter value of Radius : ");
	scanf("%d", &r);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutCreateWindow("Circle Drawing Algorithm");
	glutDisplayFunc(myDisp);
	myinit();
	glutMainLoop();
	return 0;
}

