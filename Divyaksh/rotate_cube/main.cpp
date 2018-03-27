#include <GL/glut.h>
#include <stdio.h>

GLfloat vertices[][3] = {{-1.0, -1.0, -1.0},
                         { 1.0, -1.0, -1.0},
                         { 1.0,  1.0, -1.0},
                         {-1.0,  1.0, -1.0},
                         {-1.0, -1.0,  1.0},
                         { 1.0, -1.0,  1.0},
                         { 1.0,  1.0,  1.0},
                         {-1.0,  1.0,  1.0}};

GLfloat colors[][3] = {{0.0, 0.0, 0.0},
                       {1.0, 0.0, 0.0},
                       {1.0, 1.0, 0.0},
                       {0.0, 1.0, 0.0},
                       {0.0, 1.0, 1.0},
                       {0.0, 0.0, 1.0},
                       {1.0, 0.0, 1.0},
                       {1.0, 1.0, 1.0}};

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

void color_cube() {
    polygon(0, 1, 2, 3);
    polygon(2, 3, 7, 6);
    polygon(1, 2, 6, 5);
    polygon(0, 4, 7, 3);
    polygon(4, 5, 6, 7);
    polygon(0, 1, 5, 4);
}

static GLfloat theta[] = {0.0, 0.0, 0.0};
static int axis = 2;
static GLfloat viewer[] = {0.0, 0.0, 5.0};

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);
    color_cube();
    glFlush();
    glutSwapBuffers();
}

void spinCube() {
    theta[axis] += (GLfloat)1.0;
    if(theta[axis]>360) theta[axis] -= 360;
    glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y) {
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        axis = 0;
    if(btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
        axis = 1;
    if(btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        axis = 2;
}

void myReShape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h/(GLfloat)w, 2.0 * (GLfloat)h/(GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat)w/(GLfloat)h, 2.0 * (GLfloat)w/(GLfloat)h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void keys(unsigned char key, int x, int y) {
    if(key == 'x'){
        viewer[0] -= 1.0;
    }
    switch(key) {
    case 'X':
        viewer[0] += 1.0;
        break;
    case 'y':
        viewer[1] -= 1.0;
        break;
    case 'Y':
        viewer[1] += 1.0;
        break;
    case 'z':
        viewer[2] -= 1.0;
        break;
    case 'Z':
        viewer[2] += 1.0;
        break;
    }
    display();
}

int main (int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Spinning Cube");
    glutReshapeFunc(myReShape);
    glutDisplayFunc(display);
    glutIdleFunc(spinCube);
    glutMouseFunc(mouse);
    // glutKeyboardFunc(keys);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
