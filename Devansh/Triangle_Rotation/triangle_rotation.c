#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define PI 3.141592653589793

GLfloat triangle[3][3] = {{0, 100, 200},
	                      {0, 0, 200},
    	                  {1, 1, 1}};
GLfloat fintriangle[3][3];

void draw_triangle(float trimat[3][3]) {
    glBegin(GL_TRIANGLES);
    glVertex2f(trimat[0][0], trimat[1][0]);
    glVertex2f(trimat[0][1], trimat[1][1]);
    glVertex2f(trimat[0][2], trimat[1][2]);
    glEnd();
}

void rot_triangle(int x, int y, int deg) {
    float result[3][3];

    float rad = (float)(deg * PI / 180);

    result[0][0] = cos(rad);
    result[0][1] = -sin(rad);
    result[0][2] = -x * cos(rad) + y * sin(rad) + x;

    result[1][0] = sin(rad);
    result[1][1] = cos(rad);
    result[1][2] = -x * sin(rad) - y * cos(rad) + y;

    result[2][0] = 0;
    result[2][1] = 0;
    result[2][2] = 1;

    int i, j, l;

    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            fintriangle[i][j] = 0;
            for(l = 0; l < 3; l++) {
                fintriangle[i][j] += result[i][l] * triangle[l][j];
            }
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    draw_triangle(triangle);

    /*int x, y, a;
    printf("Enter the fixed point coordinates: ");
    scanf("%d%d", &x, &y);
    printf("Enter the rotation angle in degrees: ");
    scanf("%d", &a);*/

    rot_triangle(0, 0, 90);

    glColor3f(0.0, 0.0, 1.0);
    draw_triangle(fintriangle);
    glFlush();
}

void myinit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Triangle Rotation");

    glutDisplayFunc(display);

    myinit();

    glutMainLoop();

    return 1;
}
