#include <stdio.h>
#include <GL/glut.h>
#define outcode int

double xmin = 50, ymin = 50, xmax = 100, ymax = 100;
double xvmin = 200, yvmin = 200, xvmax = 300, yvmax = 300;

const int RIGHT = 2, LEFT = 1, TOP = 8, BOTTOM = 4;

int n;

int *xa, *ya;

void cohenSutherland(double x0, double y0, double x1, double y1) {
	outcode outcode0, outcode1, outcodeout;

	int accept = 0, done = 0;
	outcode0 = computeoutcode(x0, y0);
	outcode1 = computeoutcode(x1, y1);

	do {
		if(!(outcode0 | outcode1)) {
			accept = 1;
			done = 1;
		} else if(outcode0 & outcode1) {
			done = 1;
		} else {
			double x, y;

			outcodeout = outcode0 ? outcode0 : outcode1;

			if(outcodeout & TOP) {
				x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
				y = ymax;
			} else if(outcodeout & BOTTOM) {
				x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
				y = ymin;
			} else if(outcodeout & RIGHT) {
				y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				x = xmax;
			} else {
				y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				x = xmin;
			}

			if(outcodeout == outcode0) {
				x0 = x;
				y0 = y;
				outcode0 = computeoutcode(x0, y0);
			} else {
				x1 = x;
				y1 = y;
				outcode1 = computeoutcode(x1, y1);
			}
		}
	} while(!done);

	if(accept) {
		double sx = (xvmax - xvmin) / (xmax - xmin),
			   sy = (yvmax - yvmin) / (ymax - ymin),
			   vx0 = xvmin + (x0 - xmin) * sx,
			   vy0 = yvmin + (y0 - ymin) * sy,
			   vx1 = xvmin + (x1 - xmin) * sx,
			   vy1 = yvmin + (y1 - ymin) * sy;

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xvmin, yvmin);
		glVertex2f(xvmax, yvmin);
		glVertex2f(xvmax, yvmax);
		glVertex2f(xvmin, yvmax);
		glEnd();

		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINES);
		glVertex2f(vx0, vy0);
		glVertex2f(vx1, vy1);
		glEnd();
	}
}

outcode computeoutcode(double x, double y) {
	outcode code = 0;

	if(y > ymax) {
		code |= TOP;
	} else if(y < ymin) {
		code |= BOTTOM;
	}

	if(x > xmax) {
		code |= RIGHT;
	} else if(x < xmin) {
		code |= LEFT;
	}

	return code;
}

void display() {
	// double x0 = 120, y0 = 10, x1 = 40, y1 = 130;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2d(x0, y0);
	glVertex2d(x1, y1);
	// glVertex2d(60, 20);
	// glVertex2d(80, 120);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin, ymin);
	glVertex2f(xmax, ymin);
	glVertex2f(xmax, ymax);
	glVertex2f(xmin, ymax);
	glEnd();

	// cohenSutherland(x0, y0, x1, y1);
	// cohenSutherland(60, 20, 80, 120);

	glFlush();
}

void myinit() {
	glClearColor(1, 1, 1, 1);
	glColor3f(1, 0, 0);
	gluOrtho2D(0, 500, 0, 500);
}

void main(int argc, char** argv) {
	printf("Enter the no. of lines : ");
	scanf("%d", &n);

	xa = (int *)(calloc(n * 2, sizeof(int)));
	ya = (int *)(calloc(n * 2, sizeof(int)));

	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Clip");

	glutDisplayFunc(display);

	myinit();

	glutMainLoop();
}
