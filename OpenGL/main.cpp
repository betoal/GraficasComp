#include "GL/glut.h"

void init(void) {
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,100.0,0.0,200.0);
}

void lineSegment(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.4,0.6,0.2);
	glBegin(GL_LINES);
		glVertex3f(200,145,-1);
		glVertex3f(60,15,-1);

	glEnd();
	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(500,100);
	glutInitWindowSize(900,800);
	glutCreateWindow("Ejemplo");
	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();
}
	