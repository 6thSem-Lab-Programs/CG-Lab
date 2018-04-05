#include<GL/glut.h>

void wall(double thickness){
//	glColor3f(1,1,1);
	glPushMatrix();
	glTranslated(0.5,0.5*thickness,0.5);
	glScaled(1.0,thickness,1.0);
	glutSolidCube(1.0);
	glPopMatrix();
}

void tableLeg(double thick,double len){
//	glColor3f(0.8,0.1,0);
	glPushMatrix();
	glTranslated(0,len/2,0);
	glScaled(thick,len,thick);
	glutSolidCube(1.0);
	glPopMatrix();
}

void table(double tw,double tt,double lt,double ll){
	glColor3f(0.52,0.37,0.26);
	glPushMatrix();
	glTranslated(0,ll,0);
	glScaled(tw,tt,tw);
	glutSolidCube(1.0);
	glPopMatrix();
	double dist = 0.95 * tw/2.0 - lt/2.0;
	glPushMatrix();
	glTranslated(dist,0,dist);
	tableLeg(lt,ll);
	glTranslated(0,0,-2*dist);
	tableLeg(lt,ll);
	glTranslated(-2*dist,0,2*dist);
	tableLeg(lt,ll);
	glTranslated(0,0,-2*dist);
	tableLeg(lt,ll);
	glPopMatrix();
}

void displaySolid(){
	float mat_amb[] = {1,1,1,1.0};
	float mat_diff[] = {0.5,0.5,0.5,1.0};
	float mat_spec[] = {1.0,1.0,1.0,1.0};
	float mat_shine[] = {50.0};

	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_amb);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diff);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_spec);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shine);

	float lightIntensity[] = {0.7,0.7,0.7,1.0};
	float light_pos[] = {2.0,6.0,3.0,0.0};
	glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double wh = 1.0;
	glOrtho(-wh*64/48,wh*64/48,-wh,wh,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.3,1.3,2.0,0.0,0.25,0.0,0.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslated(0.6,0.38,0.5);
	glRotated(90,0,1,0);
	glColor3f(0.4,0.4,0.4);
	glutSolidTeapot(0.08);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.4,0,0.4);
	table(0.6,0.02,0.02,0.3);
	glPopMatrix();
	glColor3f(1,0.9,0.9);
	wall(0.02);
	glPushMatrix();
	glColor3f(0.8,0.2,0.3);
	glRotated(90,0,0,1);
	wall(0.02);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.8,0.2,0.3);
	glRotated(-90,1,0,0);
	wall(0.02);
	glPopMatrix();
	glFlush();
}

void main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutCreateWindow("Teapot");
	glutDisplayFunc(displaySolid);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.1,0.1,0.1,0.0);
	glViewport(0,0,640,480);
	glutMainLoop();
}
