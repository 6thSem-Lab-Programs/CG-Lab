#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.146
GLsizei winWidth = 600, winHeight = 600;
GLfloat xwcMin = 0.0, xwcMax = 130.0;
GLfloat ywcMin = 0.0, ywcMax = 130.0;
int choice = 0;
typedef struct WCPt3D {
	GLfloat x, y, z;
}wcPt3D;

void bino(GLint n, GLint *c) {
	GLint k,j;
	for(k=0;k<=n;++k) {
		c[k]=1;
		for(j=n;j>=k+1;--j) c[k]*=j;
		for(j=n-k;j>=2;--j) c[k]/=j;
	}
}

void computeBezPt(GLfloat u, wcPt3D *bezPt, GLint nCtrlPts, wcPt3D *CtrlPts, GLint *c) {
	GLint k, n=nCtrlPts-1;
	GLfloat bezBlendFcn;
	bezPt->x=bezPt->y=bezPt->z=0.0;
	for(k=0; k<nCtrlPts; ++k) {
		bezBlendFcn=c[k]*pow(u,k)*pow(1-u, n-k);
		bezPt->x+=CtrlPts[k].x*bezBlendFcn;
		bezPt->y+=CtrlPts[k].y*bezBlendFcn;
		bezPt->z+=CtrlPts[k].z*bezBlendFcn;
	}
}

void bezier(wcPt3D *ctrlPts, GLint nCtrlPts, GLint nBezCurvePts) {
	wcPt3D bezCurvePt;
	GLfloat u;
	GLint k;
	GLint *c = new GLint[nCtrlPts];
	bino(nCtrlPts-1, c);
	glBegin(GL_LINE_STRIP);
	for(k=0; k<=nBezCurvePts; ++k) {
		u=GLfloat(k)/GLfloat(nBezCurvePts);
		computeBezPt(u, &bezCurvePt, nCtrlPts, ctrlPts, c);
		glVertex2f(bezCurvePt.x, bezCurvePt.y);
	}
	glEnd();
	delete[] c;

}

void display() {
	int i;
	GLint nCtrlPts=4, nBezCurvePts=20;
	static float theta = 0;
	wcPt3D ctrlPts[4] = {{20, 100, 0}, {30, 110, 0}, {50, 90, 0}, {60, 100, 0}};
	ctrlPts[1].x+=10*sin(theta*PI/180.0);
	ctrlPts[1].y+=5*sin(theta*PI/180.0);
	ctrlPts[2].x-=10*sin((theta+30)*PI/180.0);
	ctrlPts[2].y-=10*sin((theta+30)*PI/180.0);
	ctrlPts[3].x-=4*sin(theta*PI/180.0);
	ctrlPts[3].y+=sin((theta-30)*PI/180.0);
	if(choice==2)
		theta += 1.0;
	else if(choice==1)
		theta = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	glPointSize(5);
	glPushMatrix();
	glLineWidth(5);
	if(choice==1||choice==2) {
		glColor3f(255/255.0, 153/255.0, 51/255.0);
		for(i=0;i<8;++i) {
			glTranslatef(0, -0.8, 0);
			bezier(ctrlPts, nCtrlPts, nBezCurvePts);
		}
		glColor3f(1.0, 1.0, 1.0);
		for(i=0;i<8;++i) {
			glTranslatef(0, -0.8, 0);
			bezier(ctrlPts, nCtrlPts, nBezCurvePts);
		}
		glColor3f(19/255.0, 136/255.0, 8/255.0);
		for(i=0;i<8;++i) {
			glTranslatef(0, -0.8, 0);
			bezier(ctrlPts, nCtrlPts, nBezCurvePts);
		}
		glPopMatrix();
		glColor3f(0.7, 0.5, 0.3);
		glLineWidth(5);
		glBegin(GL_LINES);
		glVertex2f(20, 100);
		glVertex2f(20, 40);
		glEnd();
		glFlush();
	}
	glutPostRedisplay();
	glutSwapBuffers();


}

void winReshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);
	glClear(GL_COLOR_BUFFER_BIT);
}

void mymenu(int id) {
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

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Bezier Curve");
	int sub_menu = glutCreateMenu(mymenu);
	glutAddMenuEntry("Draw Flag",2);
	glutAddMenuEntry("Animate Flag",3);
	glutCreateMenu(mymenu);
	glutAddMenuEntry("Exit",1);
	glutAddSubMenu("Flag",sub_menu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(display);
	glutReshapeFunc(winReshape);
	glutMainLoop();
	return 0;
}
