#include<stdio.h>
#include<GL/glut.h>

double xmin = 50,ymin = 50,xmax = 100,ymax = 100;
double xvmin = 200,yvmin = 200,xvmax = 300,yvmax = 300;
float *px0,*py0,*px1,*py1;
const int R = 2;
const int L = 1;
const int T = 8;
const int B = 4;
int n;
int computeOutcode(double x,double y);

void cohenSutherland(double x0,double y0,double x1,double y1)
{
	int oc0,oc1,oc;
	int accept = 0,done = 0;
	oc0 = computeOutcode(x0,y0);
	oc1 = computeOutcode(x1,y1);
	//printf("oc0 = %d oc1 = %d\n",oc0,oc1);
	do
	{
		
		if(!(oc0 | oc1))
		{
			accept = 1;
			done = 1;
		}
		else if (oc0 & oc1)
		{
			done = 1;
		}
		else
		{
			double x,y;

			oc = oc0? oc0 : oc1;

			if(oc & T)
			{
				x = x0 + (x1 - x0)*(ymax - y0)/(y1 - y0);
				y = ymax;
			}
			else if(oc & B)
			{
				x = x0 + (x1 - x0)*(ymin - y0)/(y1 - y0);
				y = ymin;
			}
			else if(oc & R)
			{
				y = y0 + (y1 - y0)*(xmax - x0)/(x1 - x0);
				x = xmax;
			}
			else
			{
				y = y0 + (y1 - y0)*(xmin - x0)/(x1 - x0);
				x = xmin;
			}

			if(oc == oc0)
			{
				x0 = x;
				y0 = y;
				oc0 = computeOutcode(x0,y0);
			}
			else
			{
				x1 = x;
				y1 = y;
				oc1 = computeOutcode(x1,y1);
			}
		}
	}while(!done);

	if(accept)
	{
		double sx = (xvmax - xvmin)/(xmax - xmin);
		double sy = (yvmax - yvmin)/(ymax - ymin);
		double vx0 = xvmin + (x0 - xmin)*sx;
		double vx1 = xvmin + (x1 - xmin)*sx;
		double vy0 = yvmin + (y0 - ymin)*sy;
		double vy1 = yvmin + (y1 - ymin)*sy;

		glColor3f(0,0,0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(xvmin,yvmin);
			glVertex2f(xvmax,yvmin);
			glVertex2f(xvmax,yvmax);
			glVertex2f(xvmin,yvmax);
		glEnd();

		glColor3f(0,1,0);
		glBegin(GL_LINES);
			glVertex2d(vx0,vy0);
			glVertex2d(vx1,vy1);
		glEnd();

//printf("%f %f , %f %f\n",vx0,vy0,vx1,vy1);
	}
}

int computeOutcode(double x,double y)
{
	int code = 0;

	if(y > ymax)
		code |= T;
	if(y < ymin)
		code |= B;
	if(x > xmax)
		code |= R;
	if(x < xmin)
		code |= L;
	return code;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0,0,1);
	glBegin(GL_LINE_LOOP);
		glVertex2f(xmin,ymin);
		glVertex2f(xmax,ymin);
		glVertex2f(xmax,ymax);
		glVertex2f(xmin,ymax);
	glEnd();
	
	int i = 0;
	for(i = 0;i < n;i++)
	{
		glColor3f(1,0,0);
		glBegin(GL_LINES);
			glVertex2d(px0[i],py0[i]);
			glVertex2d(px1[i],py1[i]);
		glEnd();
		cohenSutherland(px0[i],py0[i],px1[i],py1[i]);
	//	printf("Got input\n");
		glColor3f(1,0,0);
	} 
	glFlush();
}

void myinit()
{
	glClearColor(1,1,1,1);
	glColor3f(1,0,0);
	gluOrtho2D(0,500,0,500);
}

void main(int argc,char **argv)
{
	printf("Enter number of lines :");
	scanf("%d",&n);
	px0 = (float *)malloc(sizeof(float));
	py0 = (float *)malloc(sizeof(float));
	px1 = (float *)malloc(sizeof(float));
	py1 = (float *)malloc(sizeof(float));
	int i = 0;
	for(i = 0;i < n;i++)
	{
		printf("\nEnter two points for line %d :",(i+1));
		scanf("%f%f%f%f",&px0[i],&py0[i],&px1[i],&py1[i]);
	}
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutCreateWindow("Clipping");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}
