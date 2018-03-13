#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.141592

GLfloat fixed_point[2] = {100.0,0.0};
GLfloat triangle[3][3] = {{0.0,100.0,100.0},
                          {0.0,0.0,100.0},
                          {1.0,1.0,1.0}};

void draw_triangle(GLfloat triangle[3][3]) {
    glBegin(GL_TRIANGLES);
        glVertex2f(triangle[0][0], triangle[1][0]);
        glVertex2f(triangle[0][1], triangle[1][1]);
        glVertex2f(triangle[0][2], triangle[1][2]);
    glEnd();
}

void rotate_triangle(int angle) {

    int i, j, k;
    GLfloat result[3][3];
    float rot_mat[3][3];
    float theta = (float)(angle)*(PI/180.0);
    rot_mat[0][0] = cos(theta);
    rot_mat[0][1] = -sin(theta);
    rot_mat[0][2] = fixed_point[0]*(1.0-cos(theta)) + fixed_point[1]*sin(theta);
    rot_mat[1][0] = sin(theta);
    rot_mat[1][1] = cos(theta);
    rot_mat[1][2] = -fixed_point[0]*sin(theta) + fixed_point[1]*(1.0-cos(theta));
    rot_mat[2][0] = 0;
    rot_mat[2][1] = 0;
    rot_mat[2][2] = 1;

    printf("\nRotation Matrix:\n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%f\t", rot_mat[i][j]);
        }
        printf("\n");
    }

    printf("Result Matrix:\n");

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            result[i][j] = 0;
            for (k = 0; k < 3; k++) {
                result[i][j] += rot_mat[i][k] * triangle[k][j];
            }
            printf("%f\t", result[i][j]);
        }
        printf("\n");
    }

    draw_triangle(result);

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    draw_triangle(triangle);

    glColor3f(0.0, 0.0, 1.0);
    rotate_triangle(45);

    glColor3f(0.0, 1.0, 0.0);
    rotate_triangle(135);

    glColor3f(0.5, 0.0, 0.5);
    rotate_triangle(225);

    glColor3f(0.0, 0.5, 0.5);
    rotate_triangle(315);

    glFlush();

}

void myinit() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(-250.0, 250.0, -250.0, 250.0);
}

int main(int argc,char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Triangle Rotate");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
}
