#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

void setPixel (int x, int y) {
    glBegin (GL_POINTS);
    glVertex2i (x, y);
    glEnd ();
}

void draw_line (int x1, int y1, int x2, int y2) {
    int dx, dy, i, p;
    int incx, incy, inc1, inc2;
    int x, y;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);

    incx = 1; incy = 1;

    if (x2 < x1)    incx = -1;
    if (y2 < y1)    incy = -1;

    x = x1; y = y1;

    if (dx > dy) {
        setPixel (x, y);

        p = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;

        for (i = 0; i < dx; i++) {
            if (p >= 0) {
                y += incy;
                p += inc1;
            } else {
                p += inc2;
            }
            x += incx;
            setPixel (x, y);
        }
    } else {
        setPixel (x, y);

        p = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;

        for (i = 0; i < dy; i++) {
            if (p >= 0) {
                x += incx;
                p += inc1;
            } else {
                p += inc2;
            }
            y += incy;
            setPixel (x, y);
        }
    }
}

void display () {
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);
    draw_line (50, 100, 400, 100);
    glFlush ();
    glColor3f (0.0, 0.0, 0.0);
    draw_line (100, 50, 100, 400);
    glFlush ();
    glColor3f (1.0, 0.0, 0.0);
    draw_line (150, 350, 350, 150);
    glFlush ();
    glColor3f (1.0, 0.0, 0.0);
    draw_line (150, 150, 350, 350);
    glFlush ();
}

void myinit () {
    glClearColor (1.0, 1.0, 1.0, 1.0);
    gluOrtho2D (0.0, 500.0, 0.0, 500.0);
}

void main (int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresnan Line");
    glutDisplayFunc(display);

    myinit();

    glutMainLoop();
}
