#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();
//    glFlush();
}

void draw_circle(int x, int y, int r) {
    int x1 = x, y1 = y+r;
    int x2 = x1, y2 = y1;
    int p = 1-r;

//    glColor3f(1.0, 0.0, 0.0);
//    glBegin(GL_LINES);
//        glVertex2f(x1, y1);
//        glVertex2f(x, y);
//    glEnd();
//    glColor3f(0.0, 0.0, 0.0);

    setPixel(x1, y1);

    while(x2-x < y2-y) {

        if(p <= 0) {
            p = p + 2*(++x2) + 1;
        }
        else {
            p = p + 2*(++x2) - 2*(y2--) + 1;
        }
        setPixel(x2,y2);
        printf("%d, %d\n", x2, y2);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,0.0);
    draw_circle(0, 0, 10);
    glFlush();
}

void myinit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(-10.0, 10.0, 0.0, 10.0);
    glPointSize(2);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Trial");
    glutDisplayFunc(display);
    myinit();

    glutMainLoop();
}
