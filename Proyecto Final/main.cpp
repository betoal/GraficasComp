#include <string>
#include <ctime>
#include <Windows.h>
#include <iostream>
#include "GL/glut.h"

#define IMAGE_ROWS 64      // La textura de  imagen de las columnas y renglones
#define IMAGE_COLS 64

#define DEGREES_PER_PIXEL  0.6f // Variable para controlar la velocidad de rotación con el mouse


typedef struct {
	bool leftButton;
	bool rightButton;
	int x;
	int y;
} MouseState;

MouseState mouseState = { false, false, 0, 0 };

// Variables Globales
char title[] = "Proyecto Final";  // Título de la ventana
int windowWidth = 640;     // Ancho de la ventana
int windowHeight = 480;     // Alto de la ventana
int windowPosX = 50;      // Esquina superior izquierda x
int windowPosY = 50;      // Esquina superior izquierda y
bool fullScreenMode = true; // Full-screen?

struct rotacion {
	bool rota;    // Animación o movimiento
	float x, y, z;      // Valores actuales de rotacion
	int current_axis; // 0 para x, 1 para y, 2 para z
} cube_state;

							// Textura
GLubyte imageData[IMAGE_ROWS][IMAGE_COLS][3]; // Textura como image data

											  // Animacion
GLfloat xAngle = 0.0f;  // Ángulo rotacional en x-axis
GLfloat yAngle = 0.0f;  // Ángulo rotacional en y-axis

						// Cargar el arreglo imageData con el patron de ajedrez
void loadTextureImageData() {
	int value;
	for (int row = 0; row < IMAGE_ROWS; row++) {
		for (int col = 0; col < IMAGE_COLS; col++) {
			// Cada celda es de 8x8, value es 0 o 255 (negro o blanco)
			value = (((row & 0x8) == 0) ^ ((col & 0x8) == 0)) * 255;
			imageData[row][col][0] = (GLubyte)value;
			imageData[row][col][1] = (GLubyte)value;
			imageData[row][col][2] = (GLubyte)value;
		}
	}
}

// Iniciar OpenGL
void initGL(GLvoid) {

	cube_state.rota = false;
	cube_state.x = cube_state.y = cube_state.z = 0.0f;
	cube_state.current_axis = 0;

	glShadeModel(GL_SMOOTH);               // Habilitar smooth shading del color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // Poner background (clear) color a blanco

										   // Depth-buffer para quitar superficies escondidas
	glClearDepth(1.0f);       // Poner el clear depth value al más lejano
	glEnable(GL_DEPTH_TEST);  // Habilitar depth-buffer para quitar superficies escondidas
	glDepthFunc(GL_LEQUAL);   // Tipo de depth testing para realizar

							  // Textura
	loadTextureImageData();   // Cargar el patrón al image data array
	glTexImage2D(GL_TEXTURE_2D, 0, 3, IMAGE_COLS, IMAGE_ROWS, 0, GL_RGB,
		GL_UNSIGNED_BYTE, imageData);  // Crear textura del image data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glEnable(GL_TEXTURE_2D);  // Habilitar textura 2D 

							  // Corregir distorsión en la proyección en perspectiva
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	GLfloat xmin = -100.0, ymin = -80.0, xmax = 100.0, ymax = 80.0; // Dimensiones del plano ortogonal
	GLfloat dnear = -5.0, dfar = -10.0; // Puntos donde se proyectan los objetos en z
	glMatrixMode(GL_PROJECTION);
	glOrtho(xmin, xmax, ymin, ymax, dnear, dfar); // Creación del plano ortogonal
}

void action(void)
{
	// Animar la rotación
	float increment = 0.0125f;
	switch (cube_state.current_axis)
	{
	case 0:
		cube_state.x += increment;
		break;
	case 1:
		cube_state.y += increment;
		break;
	case 2:
		cube_state.z += increment;
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

// Handler para la ventana
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Borra la pantalla y depth buffers

														// Dibuja el cubo
	glLoadIdentity();   // Resetea la vista
	glTranslatef(0.0f, 0.0f, -5.0f); // Traslada el cubo al origen
	
	// Para rotar con el mouse
	glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(yAngle, 0.0f, 1.0f, 0.0f);

	// Para rotar con el teclado
	glRotatef(cube_state.x, 1, 0, 0);
	glRotatef(cube_state.y, 0, 1, 0);
	glRotatef(cube_state.z, 0, 0, 1);
	//glScalef(10, 10, 10);

	glBegin(GL_QUADS);
	// Cara frontal
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	// Cara trasera
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	// Cara superior
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	// Cara inferior
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	// Cara derecha
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	// Cara izquierda
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
	glutSwapBuffers();
}

// Para el fondo


// Para el re-size de la ventana
void reshape(GLsizei width, GLsizei height) {  
	if (height == 0) height = 1;  // para no dividir entre 0

								  // Pone el viewport (display area) para que ocupe toda la vista
	glViewport(0, 0, width, height);

	// Selecciona el aspect ratio
	glMatrixMode(GL_PROJECTION);  // Selecciona la Projection matrix
	glLoadIdentity();             // Resetea la Projection matrix
	gluPerspective(45.0, (float)width / (float)height, 0.1, 100.0);

	// Resetea el Model-View matrix
	glMatrixMode(GL_MODELVIEW);  // Selecciona la Model-View matrix
	glLoadIdentity();            // Resetea el Model-View matrix
}

// Handler para el teclado
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:  // ESC key: sale del programa
		exit(0); break;
	case 'x': // rota eje x
		cube_state.current_axis = 0;
		break;
	case 'y': // rota eje y
		cube_state.current_axis = 1;
		break;
	case 'z': //rota eje z
		cube_state.current_axis = 2;
		break;
	case 'r': // empieza o detiene rotación
		cube_state.rota ^= 1;
		glutIdleFunc(cube_state.rota ? action : NULL);
		break;
	default: break;
	}
}

// Handler para teclas especiales
void specialKey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:    // F1: full-screen y windowed mode
		fullScreenMode = !fullScreenMode;         // Toggle state
		if (fullScreenMode) {                     // Full-screen mode
			windowPosX = glutGet(GLUT_WINDOW_X); // Save parameters
			windowPosY = glutGet(GLUT_WINDOW_Y);
			windowWidth = glutGet(GLUT_WINDOW_WIDTH);
			windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
			glutFullScreen();                      // Switch into full screen
		}
		else {                                         // Windowed mode
			glutReshapeWindow(windowWidth, windowHeight); // Switch into windowed mode
			glutPositionWindow(windowPosX, windowPosX);   // Postion top-left corner
		}
		break;
	default: break;
	}
}

// Handler para el mouse
void mouse(int button, int state, int x, int y)
{
	// actualiza el estado del botón
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
			mouseState.leftButton = true;
		else
			mouseState.leftButton = false;
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
			mouseState.rightButton = true;
		else
			mouseState.rightButton = false;
	}

	// Actualiza la posición del mouse para que se pueda rastrear
	mouseState.x = x;
	mouseState.y = y;
}

// Handler para el movimiento del mouse
void mouseMove(int x, int y)
{
	// Calcula la distancia del mouse
	int xDelta = mouseState.x - x;
	int yDelta = mouseState.y - y;

	// Pone la posición del mouse
	mouseState.x = x;
	mouseState.y = y;

	// Si se tiene click, cambia la rotación del cubo 
	if (mouseState.leftButton) {
		xAngle -= yDelta * DEGREES_PER_PIXEL;
		yAngle -= xDelta * DEGREES_PER_PIXEL;
	}
	glutPostRedisplay();
}


// main function
int main(int argc, char** argv) {
	glutInit(&argc, argv);      // Inicia GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // Pone modos para 3D
	glutInitWindowSize(windowWidth, windowHeight);  // Ancho y alto inicial de la ventana
	glutInitWindowPosition(windowPosX, windowPosY); // Posición (x,y) inicial de la esquina superior izquierda
	glutCreateWindow(title);     // Crea la ventana con el título dado
	glutDisplayFunc(display);    // Registra el handler para la ventana
	glutReshapeFunc(reshape);    // Registra el handler para el re-size de la ventana
	glutKeyboardFunc(keyboard);  // Registra el handler para el teclado
	glutSpecialFunc(specialKey); // Registra el handler para las teclas especiales
	glutMouseFunc(mouse);        // Registra el handler para el mouse
	glutMotionFunc(mouseMove);   // Registra el handler para el movimiento del mouse
	//glutIdleFunc(action);		 // Registra el handler para la rotación automática
	initGL();          // inicia OpenGl
	glutMainLoop();
	return 0;
}