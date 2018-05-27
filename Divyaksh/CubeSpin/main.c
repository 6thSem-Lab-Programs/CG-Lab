#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

GLfloat vertices[][3] = {{-1.0, -1.0, -1.0},
                          {1.0, -1.0, -1.0},
                          {1.0, 1.0, -1.0},
                          {-1.0, 1.0, -1.0},
                          {-1.0, -1.0, 1.0},
                          {1.0, -1.0, 1.0},
                          {1.0, 1.0, 1.0},
                          {-1.0, 1.0, 1.0}};
GLfloat colors[][3] = {{0.0, 0.0, 0.0},
                        {1.0, 0.0, 0.0},
                        {1.0, 1.0, 0.0},
                        {0.0, 1.0, 0.0},
                        {0.0, 1.0, 1.0},
                        {0.0, 0.0, 1.0},
                        {1.0, 0.0, 1.0},
                        {1.0, 1.0, 1.0}};
GLfloat viewer[3] = {0.0, 0.0, 5.0};

void polygon(int a, int b, int c, int d) {
    glBegin(GL_POLYGON);
    glColor3fv(colors[a]);
    glVertex3fv(vertices[a]);
    glColor3fv(colors[b]);
    glVertex3fv(vertices[b]);
    glColor3fv(colors[c]);
    glVertex3fv(vertices[c]);
    glColor3fv(colors[d]);
    glVertex3fv(vertices[d]);
    glEnd();
}

void colorCube() {
    polygon(0, 3, 2, 1);
    polygon(2, 3, 7, 6);
    polygon(1, 2, 6, 5);
    polygon(0, 4, 7, 3);
    polygon(4, 5, 6, 7);
    polygon(0, 1, 5, 4);
}

static GLfloat theta[] = {0.0, 0.0, 0.0};
static GLint axis = 2;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //glRotatef(theta[0], 1, 0, 0);
    //glRotatef(theta[1], 0, 1, 0);
    //glRotatef(theta[2], 0, 0, 1);
    gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 5.0, 0.0);
    colorCube();
    glFlush();
    glutSwapBuffers();
}

void spinCube() {
    theta[axis] += 1.0;

    if(theta[axis] > 360.0)	theta[axis] -= 360.0;

    glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y) {
    if(btn == GLUT_LEFT_BUTTON)		axis = 0;
    if(btn == GLUT_MIDDLE_BUTTON)	axis = 1;
    if(btn == GLUT_RIGHT_BUTTON)	axis = 2;
}

void keys(unsigned char key, int x, int y) {
    switch(key) {
	case 'x':	viewer[0] -= 1.0; break;
	case 'X':	viewer[0] += 1.0; break;
	case 'y':	viewer[1] -= 1.0; break;
	case 'Y':	viewer[1] += 1.0; break;
	case 'z':	viewer[2] -= 1.0; break;
	case 'Z':	viewer[2] += 1.0; break;
    }
    display();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w <= h) {
	glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    } else {
	glOrtho(-2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0, -10.0, 10.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Cube Spin");
    glutInitWindowSize(500, 500);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
//    glutIdleFunc(spinCube);
    // glutMouseFunc(mouse);
    glutKeyboardFunc(keys);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}
