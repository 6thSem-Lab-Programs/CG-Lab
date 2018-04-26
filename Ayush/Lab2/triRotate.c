#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

int h, k, theta;
GLfloat mat[3][3] = {{100.0,175.0,250.0},{100.0, 250.0, 100.0},{1.0, 1.0, 1.0}}, rot_mat[3][3], res[3][3];

void myinit() {
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glPointSize(6.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void drawTriangle(int opt) {
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
		glVertex2i(h, k);
	glEnd();
	if(opt==1) {
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_TRIANGLES);
			glVertex2i(mat[0][0], mat[1][0]);
			glVertex2i(mat[0][1], mat[1][1]);
			glVertex2i(mat[0][2], mat[1][2]);
		glEnd();
	}
	else if(opt==2) {
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_TRIANGLES);
			glVertex2i(res[0][0], res[1][0]);
			glVertex2i(res[0][1], res[1][1]);
			glVertex2i(res[0][2], res[1][2]);
		glEnd();
	}
	glFlush();
}

void rotate() {
	float angle = (theta*3.1459)/180.0;
	rot_mat[0][0] = cos(angle);
	rot_mat[0][1] = -sin(angle);
	rot_mat[0][2] = h*(1-cos(angle))+k*sin(angle);
	rot_mat[1][0] = sin(angle);
	rot_mat[1][1] = cos(angle);
	rot_mat[1][2] = k*(1-cos(angle))-h*sin(angle);
	rot_mat[2][0] = 0;
	rot_mat[2][1] = 0;
	rot_mat[2][2] = 1;

	//Rotating Matrix
	int i,j,k;
	for(i=0;i<3;++i)
		for(j=0;j<3;++j) {
			res[i][j]=0;
			for(k=0;k<3;++k) {
				res[i][j] += rot_mat[i][k]*mat[k][j];
			}
			printf("%f  ",res[i][j]);
		}
}
           
void myDisp() {
	drawTriangle(1);
	rotate();
	drawTriangle(2);
}

int main(int argc, char **argv) {
	printf("\nEnter the Point of Rotation\n");
	printf("Enter value of xc : ");
	scanf("%d", &h);
	printf("Enter value of yc : ");
	scanf("%d", &k);
	printf("Enter Angle of Rotation : ");
	scanf("%d", &theta);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutCreateWindow("Rotating Triangle about a point");
	glutDisplayFunc(myDisp);
	myinit();
	glutMainLoop();
	return 0;
}
