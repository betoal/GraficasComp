#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "GL/glu.h"
//#include gl.h>
#include "GL\glut.h"

bool  movingUp = false;
float alpha = 0.0f, newAlpha = 0.0f;
float yRotationAngle = 0.0f;
float xInit = -2.0, yInit = -2.0;


void Draw_Spheres(float yloc)
{
	int b;
	static float balls[2][3];
	static boolean first = true;

	if (first) {
		first = false;
		for (b = 0; b < 2; b++) {
			if (b == 0)
			{
				balls[b][0] = xInit;
				balls[b][1] = yInit;
				balls[b][2] = 0.0;
			}
			else
			{
				balls[b][0] = -xInit;
				balls[b][1] = -yInit;
				balls[b][2] = 0.0;
			}
		}
	}

	for (b = 0; b < 2; b++) {
		if (b == 0)
		{
			glColor3f(0.8, 0.2, 0.1);
			glPushMatrix();
			glTranslatef(balls[b][0], balls[b][1], 0.0);
			glTranslatef(yloc, yloc, 0.0);
			glutSolidSphere(1, 20, 50);
			glPopMatrix();
		}
		else
		{
			glColor3f(0.1, 0.2, 0.8);
			glPushMatrix();
			glTranslatef(balls[b][0], balls[b][1], 0.0);
			glTranslatef(-yloc, -yloc, 0.0);
			glutSolidSphere(1, 20, 50);
			glPopMatrix();
		}
	}
}

void display(void) {

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -5.0f);

	Draw_Spheres(alpha);

	glRotatef(yRotationAngle, 0.0f, 1.0f, 0.0f);

	glFlush();

	if (movingUp)
		alpha -= 0.001f;
	else
		alpha += 0.001f;

	if (alpha < -1.5f)
		movingUp = true;
	else if (alpha > 1.5f)
		movingUp = true;

	yRotationAngle += 0.005f;
	if (yRotationAngle > 360.0f)
		yRotationAngle -= 360.0f;
}

void reshape(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:  // ESC key: sale del programa
		exit(0); break;
	case 'x': // rota eje x
		newAlpha = 0.001;
		break;
	case 'y': // rota eje y
		newAlpha = 0.005;
		break;
	case 'z': //rota eje z
		newAlpha = 0.01;
		break;
	default: break;
	}
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(500, 200);
	glutCreateWindow("Final");

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutMainLoop();
}