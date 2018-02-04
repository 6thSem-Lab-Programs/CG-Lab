#include<stdio.h>
#include<GL/glut.h>

GLfloat vertex[4][3] = {{0.0,0.0,1.0},{0,0.942809,-0.3333},{-0.816497,-0.471405,-0.3333},{0.816497,-0.471405,-0.3333}};
int n;

void drawTetra(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d)
{
	glColor3f(0,1,0);
	glBegin(GL_POLYGON);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glEnd();

	
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(d);
	glEnd();

	
	glColor3f(0,0,1);
	glBegin(GL_POLYGON);
	glVertex3fv(a);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();

	
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();
}

void divideTetra(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d,int m)
{
	GLfloat v[6][3];

	if(m > 0)
	{
		for(int j = 0;j < 3;j++)
			v[0][j] = (a[j] + b[j])/2;
		
		for(int j = 0;j < 3;j++)
			v[1][j] = (a[j] + c[j])/2;

		for(int j = 0;j < 3;j++)
			v[2][j] = (a[j] + d[j])/2;

		for(int j = 0;j < 3;j++)
			v[3][j] = (b[j] + c[j])/2;


		for(int j = 0;j < 3;j++)
			v[4][j] = (c[j] + d[j])/2;

		for(int j = 0;j < 3;j++)
			v[5][j] = (b[j] + d[j])/2;

		divideTetra(a,v[0],v[1],v[2],m-1);
		divideTetra(v[0],b,v[3],v[5],m-1);
		divideTetra(v[1],v[3],c,v[4],m-1);
		divideTetra(v[2],v[5],v[4],d,m-1);
	}else{
		drawTetra(a,b,c,d);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	divideTetra(vertex[1],vertex[2],vertex[3],vertex[0],n);
	glFlush();
}

void myInit()
{
	glOrtho(-2,2,-2,2,-10,10);
	glClearColor(1,1,1,1);
}

void main(int argc,char **argv)
{
	printf("Enter number of divisions :  ");
	scanf("%d",&n);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutCreateWindow("3D gasket");
	glutDisplayFunc(display);
	myInit();
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
