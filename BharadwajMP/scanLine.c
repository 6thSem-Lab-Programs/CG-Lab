#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

int x1 = 200,y1 = 200,x2 = 100,y2 = 300,x3 = 200,y3 = 400,x4 = 300,y4 = 300;
void edgeDetect(float x1,float y1,float x2,float y2,int *le,int *re)
{
	float mx,x,temp;
	int i;

	if((y2 - y1) < 0)
	{
		temp = y1;
		y1 = y2;
		y2 = temp;

		temp = x1;
		x1 = x2;
		x2 = temp;
	}

	if((y2 - y1) != 0)
		mx = (x2 - x1)/(y2 - y1);
	else
		mx = x2 - x1;
	x = x1;

	for(i = y1;i <= y2;i++)
	{
		if(x < le[i])
			le[i] = (int)x;
		if(x > re[i])
			re[i] = (int)x;
		x += mx;
	}
}

void draw_pixel(int x,int y)
{
	glColor3f(0,1,0);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	//glFlush();
} 

void scanfill(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
	int le[500],re[500];
	int i,y;

	for(i = 0;i < 500;i++)
	{
		le[i] = 500;
		re[i] = 0;
	}

	edgeDetect(x1,y1,x2,y2,le,re);
	edgeDetect(x2,y2,x3,y3,le,re);
	edgeDetect(x3,y3,x4,y4,le,re);
	edgeDetect(x4,y4,x1,y1,le,re);

	for(y = 0;y < 500;y++)
	{
		if(le[y] <= re[y])
			for(i = (int)le[y];i <= (int)re[y];i++)
				draw_pixel(i,y);
	}
}

void display()
{
//	int x1 = 200,y1 = 200,x2 = 100,y2 = 300,x3 = 200,y3 = 400,x4 = 300,y4 = 300;
//	int x1 = 200,y1 = 200,x2 = 100,y2 = 200,x3 = 100,y3 = 300,x4 = 200,y4 = 300;
//	printf("Enter polygon points:");
//	scanf("%d%d%d%d%d%d%d");
	

//	scanfill(x1,y1,x2,y2,x3,y3,x4,y4);

	glFlush();
}

void myinit()
{
	glClearColor(1,1,1,1);
	// glColor3f(1,0,0);
	glPointSize(1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,1,0);
}

void myMenu(int id)
{
	if(id == 1)
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	if(id == 3)
		exit(-1);
	if(id == 2)
	{
		glBegin(GL_LINE_LOOP);
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
			glVertex2f(x4,y4);
		glEnd();
		glFlush();
		scanfill(x1,y1,x2,y2,x3,y3,x4,y4);
		glFlush();
	}
}

void main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Scanline filling");
	//glutDisplayFunc(display);
	int menu_id = glutCreateMenu(myMenu);
	glutAddMenuEntry("Clear screen",1);
	glutAddMenuEntry("Fill polygon",2);
	glutAddMenuEntry("Exit",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	myinit();
	glutMainLoop();
}
