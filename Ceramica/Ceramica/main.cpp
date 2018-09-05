#include "GL/glut.h"

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 100.0, 0.0, 200.0);
}

void lineSegment(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.4, 0.6, 0.2);
	glBegin(GL_LINES);
	glVertex3f(200, 145, -1);
	glVertex3f(60, 15, -1);

	glEnd();
	glFlush();
}

void borde(void) {
	int offset = 1;
	int xinit = 5;
	int xfin = 150;
	int yinit = 5;
	int yfin = 150;
	int tam = 3;
	int cont = 0;
	while (cont < 3) {
		for (int i = xinit; i < xfin; i += 3) {
			glClear(GL_COLOR_BUFFER_BIT);
			glColor3f(0, 0, 0);
			glBegin(GL_QUADS);
			glVertex3f(xinit, i, -1);
			glVertex3f(xinit + i, i, -1);
			glVertex3f(xinit + i, 2*i, -1);
			glVertex3f(xinit, 2*i, -1);
		}


	}

	
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(900, 800);
	glutCreateWindow("Ejemplo");
	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();
}