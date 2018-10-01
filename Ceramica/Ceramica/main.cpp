#include <string>
#include<ctime>
#include "GL/glut.h"

GLfloat angle = 45.0f;
int refresh = 1000.0 / 60.0;

void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(refresh, timer, 0);
}

void init(void) {
	glClearColor(128, 128, 128, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 155.0, 0.0, 155.0);

}

// Matriz con los valores de cada celda de la cer�mica
int mat[50][50] = {
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,4,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,4,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3,3,3,2,2,2,2,1,1,4,1,1,2,2,2,2,3,3,3,3,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,2,2,3,3,1,3,3,2,2,2,2,1,4,4,4,1,2,2,2,2,3,3,5,3,3,2,2,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,2,3,3,1,3,3,2,2,2,2,1,1,4,3,4,1,1,2,2,2,2,3,3,5,3,3,2,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,3,3,1,3,3,2,2,2,2,2,1,4,4,3,4,4,1,2,2,2,2,2,3,3,5,3,3,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,3,3,1,3,3,3,2,2,2,2,2,1,4,3,3,3,4,1,2,2,2,2,2,3,3,3,5,3,3,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,3,3,1,3,3,3,2,2,2,2,2,1,1,4,3,5,3,4,1,1,2,2,2,2,2,3,3,3,5,3,3,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,3,3,1,3,3,3,2,2,2,2,2,2,1,4,4,3,5,3,4,4,1,2,2,2,2,2,2,3,3,3,5,3,3,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,3,3,1,3,3,3,2,2,2,2,2,2,1,1,4,3,3,5,3,3,4,1,1,2,2,2,2,2,2,3,3,3,5,3,3,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,3,1,3,3,3,2,2,2,2,2,2,2,1,4,4,3,5,5,5,3,4,4,1,2,2,2,2,2,2,2,3,3,3,5,3,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,3,3,3,3,2,2,2,2,2,2,2,1,1,4,3,3,5,2,5,3,3,4,1,1,2,2,2,2,2,2,2,3,3,3,3,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,3,3,2,2,2,2,2,2,2,1,1,1,4,4,3,5,5,2,5,5,3,4,4,1,1,1,2,2,2,2,2,2,2,3,3,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,1,1,1,4,4,3,3,5,2,2,2,5,3,3,4,4,1,1,1,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,2,2,1,1,1,4,4,4,3,3,5,5,2,2,2,5,5,3,3,4,4,4,1,1,1,2,2,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,1,1,1,4,4,4,3,3,3,5,5,2,2,2,2,2,5,5,3,3,3,4,4,4,1,1,1,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,1,1,1,1,4,4,3,3,3,5,5,5,2,2,2,2,2,2,2,5,5,5,3,3,3,4,4,4,1,1,1,1,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,1,1,1,1,4,4,4,4,3,3,5,5,5,2,2,2,2,2,1,2,2,2,2,2,5,5,5,3,3,3,4,4,4,4,1,1,1,1,2,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,4,4,4,4,3,3,3,3,5,5,2,2,2,2,2,2,1,1,1,2,2,2,2,2,2,5,5,5,3,3,3,3,4,4,4,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,4,4,4,3,3,3,3,5,5,5,5,2,2,2,2,2,2,1,1,5,1,1,2,2,2,2,2,2,5,5,5,5,3,3,3,3,4,4,4,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,4,4,4,4,3,3,3,3,5,5,2,2,2,2,2,2,1,1,1,2,2,2,2,2,2,5,5,5,3,3,3,3,4,4,4,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,2,2,1,1,1,1,4,4,4,4,3,3,5,5,5,2,2,2,2,2,1,2,2,2,2,2,5,5,5,3,3,3,4,4,4,4,1,1,1,1,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,1,1,1,1,4,4,3,3,3,5,5,5,2,2,2,2,2,2,2,5,5,5,3,3,3,4,4,4,1,1,1,1,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,1,1,1,4,4,4,3,3,3,5,5,2,2,2,2,2,5,5,3,3,3,4,4,4,1,1,1,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,2,2,1,1,1,4,4,4,3,3,5,5,2,2,2,5,5,3,3,4,4,4,1,1,1,2,2,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,1,1,1,4,4,3,3,5,2,2,2,5,3,3,4,4,1,1,1,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,3,3,2,2,2,2,2,2,2,1,1,1,4,4,3,5,5,2,5,5,3,4,4,1,1,1,2,2,2,2,2,2,2,3,3,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,3,3,3,3,2,2,2,2,2,2,2,1,1,4,3,3,5,2,5,3,3,4,1,1,2,2,2,2,2,2,2,3,3,3,3,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,3,1,3,3,3,2,2,2,2,2,2,2,1,4,4,3,5,5,5,3,4,4,1,2,2,2,2,2,2,2,3,3,3,3,3,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,3,3,1,3,3,3,2,2,2,2,2,2,1,1,4,3,3,5,3,3,4,1,1,2,2,2,2,2,2,3,3,3,3,3,3,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,3,3,1,3,3,3,2,2,2,2,2,2,1,4,4,3,5,3,4,4,1,2,2,2,2,2,2,3,3,3,3,3,3,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,3,3,1,3,3,3,2,2,2,2,2,1,1,4,3,5,3,4,1,1,2,2,2,2,2,3,3,3,3,3,3,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,3,3,1,3,3,3,2,2,2,2,2,1,4,3,3,3,4,1,2,2,2,2,2,3,3,3,3,3,3,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,3,3,1,3,3,2,2,2,2,2,1,4,4,3,4,4,1,2,2,2,2,2,3,3,3,3,3,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,2,3,3,1,3,3,2,2,2,2,1,1,4,3,4,1,1,2,2,2,2,3,3,3,3,3,2,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,2,2,3,3,1,3,3,2,2,2,2,1,4,4,4,1,2,2,2,2,3,3,3,3,3,2,2,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3,3,3,2,2,2,2,1,1,4,1,1,2,2,2,2,3,3,3,3,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,4,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,4,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,4,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
};

// Con este metodo se rellenan los colores de la matriz de la cer�mica dependiendo del valor mandado.
// 1-> Negro
// 2-> Gris
// 3-> Rojo
// 4-> Verde
// 5-> Naranja
void secuencia(int arg[], int fila) {
	int i = 0;
	int valor;
	int alfa = 0;
	double x1 = 3.1;
	double x2 = 5.9;
	double y1 = 150.1;
	double y2 = 152.9;
	double cont = 0;

	while (i < 50) {
		valor = arg[i];
		switch (valor) {
		case 1:
			glBegin(GL_POLYGON);
			glColor3f(0.5, 0.5, 0.5);
			glVertex2f(x1 + cont, y1 - fila);
			glVertex2f(x1 + cont, y2 - fila);
			glVertex2f(x1 + cont, y2 - fila);
			glVertex2f(x2 + cont, y2 - fila);
			glVertex2f(x2 + cont, y2 - fila);
			glVertex2f(x2 + cont, y1 - fila);
			glVertex2f(x2 + cont, y1 - fila);
			glVertex2f(x1 + cont, y1 - fila);
			glEnd();
			alfa++;
			cont = cont + 3;
			break;
			
		case 2:
			glBegin(GL_POLYGON);
			glColor3f(0.75, 0.84, 0.79);
			glVertex2f(x1 + cont, y1 - fila);
			glVertex2f(x1 + cont, y2 - fila);
			glVertex2f(x1 + cont, y2 - fila);
			glVertex2f(x2 + cont, y2 - fila);
			glVertex2f(x2 + cont, y2 - fila);
			glVertex2f(x2 + cont, y1 - fila);
			glVertex2f(x2 + cont, y1 - fila);
			glVertex2f(x1 + cont, y1 - fila);
			glEnd();
			alfa++;
			cont = cont + 3;
			break;
			
		case 3:
			glBegin(GL_POLYGON);
			glColor3f(1.5, 0, 0);
			glVertex2f(x1 + cont, y1 - fila);
			glVertex2f(x1 + cont, y2 - fila);
			glVertex2f(x1 + cont, y2 - fila);
			glVertex2f(x2 + cont, y2 - fila);
			glVertex2f(x2 + cont, y2 - fila);
			glVertex2f(x2 + cont, y1 - fila);
			glVertex2f(x2 + cont, y1 - fila);
			glVertex2f(x1 + cont, y1 - fila);
			glEnd();
			alfa++;
			cont = cont + 3;
			break;
			
		case 4:
			glBegin(GL_POLYGON);
			glColor3f(0, 0.5, 0);
			glVertex2f(x1 + cont, y1 - fila);
			glVertex2f(x1 + cont, y2 - fila);
			glVertex2f(x1 + cont, y2 - fila);
			glVertex2f(x2 + cont, y2 - fila);
			glVertex2f(x2 + cont, y2 - fila);
			glVertex2f(x2 + cont, y1 - fila);
			glVertex2f(x2 + cont, y1 - fila);
			glVertex2f(x1 + cont, y1 - fila);
			glEnd();
			alfa++;
			cont = cont + 3;
			break;
			
		case 5:
			glBegin(GL_POLYGON);
			glColor3f(2, 1, 0);
			glVertex2f(x1 + cont, y1 - fila);
			glVertex2f(x1 + cont, y2 - fila);
			glVertex2f(x1 + cont, y2 - fila);
			glVertex2f(x2 + cont, y2 - fila);
			glVertex2f(x2 + cont, y2 - fila);
			glVertex2f(x2 + cont, y1 - fila);
			glVertex2f(x2 + cont, y1 - fila);
			glVertex2f(x1 + cont, y1 - fila);
			glEnd();
			alfa++;
			cont = cont + 3;
			break;
		}
		glTranslatef(0.5f, 0.0f, 0.0f);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		alfa = 0;
		i++;
	}
	glTranslatef(0.5f, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
}

// Este m�todo genera una matriz como base gu�a para la cer�mica
void lineSegment(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	int k = 0;
	int m = 0;
	while (k < 50) {
		int i = 0;
		int j = 0;
		while (i < 50) {
			glVertex2f(3 + m, 3 + j);
			glVertex2f(3 + m, 6 + j);
			glVertex2f(3 + m, 6 + j);
			glVertex2f(3 + m, 6 + j);
			glVertex2f(6 + m, 6 + j);
			glVertex2f(6 + m, 3 + j);
			glVertex2f(6 + m, 3 + j);
			glVertex2f(3 + m, 3 + j);
			j = j + 3;
			i++;
		}
		m = m + 3;
		k++;
	}
	glVertex2f(3, 153);
	glVertex2f(153, 153);
	glEnd();
	
// Se manda llamar el m�todo que rellena la matriz.
	int y = 0;	
	//glPushMatrix();
	for (int i = 0; i < 50; i++)
	{
		secuencia(mat[i], y);
		y = y + 3;
	}
	glPopMatrix();
	glutSwapBuffers();
	//angle += 0.2;
	glFlush();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Cer�mica");
	init();
	glutDisplayFunc(lineSegment);
	glutTimerFunc(0, timer, 0);
	double tmr = 5.0;
	bool flag = true;
	clock_t start = clock();
	double secondPassed;
	while (flag) {
		secondPassed = (clock() - start) / CLOCKS_PER_SEC;
		if (secondPassed >= tmr) {
			flag = false;
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.0, 0.0, 0.0, 0.0);
		}
	}
	glutMainLoop();
	
}