#include "GL/glut.h"
#include <math.h>;

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

float angulo;

void dibujar() {

	glClear(GL_COLOR_BUFFER_BIT);
	glRotatef(angulo, 0.0, 0.0, 1.0);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(15, 15, 0);
	glVertex3f(100, 100, 0);
	glVertex3f(180, 15, 0);
	glEnd();
	glutSwapBuffers();
	angulo++;
}


typedef struct {
	GLfloat x, y;
}wcPt2D;

void rotatePolygon(wcPt2D * verts, GLint nVerts, wcPt2D pivPt, GLdouble theta) {
	wcPt2D * vertsRot;
	GLint k;
	for (k = 0; k < nVerts; k++) {
		vertsRot[k].x = pivPt.x + (verts[k].x - pivPt.x) * cos(theta) - (verts[k].y - pivPt.y) * sin(theta);
		vertsRot[k].y = pivPt.y + (verts[k].x - pivPt.x) * sin(theta) + (verts[k].y - pivPt.y) * cos(theta);
	}
	glBegin(GL_POLYGON);
	for (k = 0; k < nVerts; k++)
		glVertex2f(vertsRot[k].x, vertsRot[k].y);
	glEnd();
}


void main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("Ejemplo");
	init();
	angulo = 5.0;
	GLint k;
	glBegin(GL_TRIANGLES);
	for (k = 0; k < 3; k++)
		glVertex2f(verts[k].x, verts[k].y);
	glEnd();
	GLint nVerts = 3;
	wcPt2D verts[3] = { { 50.0, 25.0 },{ 150.0, 25.0 },{ 100.0, 100.0 } };
	/* Calculate position of triangle centroid. */
	wcPt2D centroidPt;
	GLint k, xSum = 0, ySum = 0;
	for (k = 0; k < nVerts; k++) {
		xSum += verts[k].x;
		ySum += verts[k].y;
	}
	centroidPt.x = GLfloat(xSum) / GLfloat(nVerts);
	centroidPt.y = GLfloat(ySum) / GLfloat(nVerts);
	glutDisplayFunc(rotatePolygon(vert, 3, fig, pi / 2));
	//glutDisplayFunc(dibujar);
	//glutIdleFunc(dibujar);
	glutMainLoop();
}