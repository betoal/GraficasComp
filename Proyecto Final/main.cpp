#include <string>
#include <ctime>
#include <Windows.h>
#include <iostream>
#include "GL/glut.h"

// La textura de  imagen de las columnas y renglones para cubo
#define IMAGE_ROWS 64
#define IMAGE_COLS 64

// La textura de  imagen de las columnas y renglones para fondo
#define IMAGE_ROWS_F 512
#define IMAGE_COLS_F 512

#define DEGREES_PER_PIXEL  1.0f // Variable para controlar la velocidad de rotación con el mouse


typedef struct {
	bool leftButton;
	bool rightButton;
	int x;
	int y;
} MouseState;

struct rotacion {
	bool rota;    // Animación o movimiento
	float x, y, z;      // Valores actuales de rotacion
	int current_axis; // 0 para x, 1 para y, 2 para z
} cube_rotate;

//struct traslacion {
//	bool mueve;    // Animación o movimiento
//	float x, y, z;      // Valores actuales de traslacion
//	int current_axis; // 0 para x, 1 para y, 2 para z
//} cube_traslate;

MouseState mouseState = { false, false, 0, 0 };

// Variables Globales
char title[] = "Proyecto Final";  // Título de la ventana
int windowWidth = 640;     // Ancho de la ventana
int windowHeight = 480;     // Alto de la ventana
int windowPosX = 50;      // Esquina superior izquierda x
int windowPosY = 50;      // Esquina superior izquierda y
bool fullScreenMode = true; // Full-screen?

static GLuint textures[2];

// Textura
GLubyte imageData[IMAGE_ROWS][IMAGE_COLS][3]; // Textura como image data para cubo
GLubyte imageDataF[IMAGE_ROWS_F][IMAGE_COLS_F][3]; // Textura como image data para fondo

// Animacion
GLfloat xAngle = 0.0f;  // Ángulo rotacional en x-axis
GLfloat yAngle = 0.0f;  // Ángulo rotacional en y-axis

// Dimensiones del plano ortogonal
GLfloat xmin = -20.0f, ymin = -20.0f;
GLfloat xmax =  20.0f, ymax =  20.0f;
GLfloat dnear = -5.0f, dfar = -20.0f; // Puntos donde se proyectan los objetos en z

// Cargar el arreglo imageData con el patron de ajedrez para cubo
void loadTextureImageData() {
	int value;
	for (int row = 0; row < IMAGE_ROWS; row++) {
		for (int col = 0; col < IMAGE_COLS; col++) {
			// Cada celda es de IMAGE_ROWSxIMAGE_COLS, value es 0 o 255 (negro o blanco)
			value = (((row & 0x8) == 0) ^ ((col & 0x8) == 0)) * 255;
			imageData[row][col][0] = (GLubyte)value;
			imageData[row][col][1] = (GLubyte)value;
			imageData[row][col][2] = (GLubyte)value;
		}
	}
}

// Cargar el arreglo imageData con el patron de ajedrez para fondo
void loadTextureImageB() {
	int value;
	for (int row = 0; row < IMAGE_ROWS_F; row++) {
		for (int col = 0; col < IMAGE_COLS_F; col++) {
			// Cada celda es de IMAGE_ROWS_FxIMAGE_COLS_F, value es 0 o 255 (negro o blanco)
			value = (((row & 0x8) == 0) ^ ((col & 0x8) == 0)) * 255;
			imageDataF[row][col][0] = (GLubyte)value;
			imageDataF[row][col][1] = (GLubyte)value;
			imageDataF[row][col][2] = (GLubyte)value;
		}
	}
}

// Iniciar OpenGL y crear texturas
void initGL(GLvoid) {

	// Objeto para rotar con teclado
	cube_rotate.rota = false;
	cube_rotate.x = cube_rotate.y = cube_rotate.z = 0.0f;
	cube_rotate.current_axis = 0;

	//// Objeto para trasladar con teclado
	//cube_traslate.mueve = false;
	//cube_traslate.x = cube_traslate.y = cube_traslate.z = 0.0f;
	//cube_traslate.current_axis = 0;

	glShadeModel(GL_SMOOTH);               // Habilitar smooth shading del color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // Poner background (clear) color a blanco

										   // Depth-buffer para quitar superficies escondidas
	glClearDepth(1.0f);       // Poner el clear depth value al más lejano
	glEnable(GL_DEPTH_TEST);  // Habilitar depth-buffer para quitar superficies escondidas
	glDepthFunc(GL_LEQUAL);   // Tipo de depth testing para realizar

	// Textura del cubo
	loadTextureImageData();   // Cargar el patrón al image data array
	glGenTextures(2, textures); // Carga la textura al arreglo textures[1]
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, IMAGE_COLS, IMAGE_ROWS, 0, GL_RGB,
		GL_UNSIGNED_BYTE, imageData);  // Crear textura del image data

	// Textura del fondo
	loadTextureImageB();   // Cargar el patrón al image data array
	glBindTexture(GL_TEXTURE_2D, textures[2]); //Carga la textura al arreglo textures[2]
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, IMAGE_COLS_F, IMAGE_ROWS_F, 0, GL_RGB,
		GL_UNSIGNED_BYTE, imageDataF);  // Crear textura del image data

	glEnable(GL_TEXTURE_2D);  // Habilitar textura 2D 

							  // Corregir distorsión en la proyección en perspectiva
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glMatrixMode(GL_PROJECTION);
	glOrtho(xmin, xmax, ymin, ymax, dnear, dfar); // Creación del plano ortogonal

}

// Rotar el cubo
void actionR(void)
{
	// Animar la rotación
	float increment = 0.015f;
	switch (cube_rotate.current_axis)
	{
	case 0:
		cube_rotate.x += increment;
		break;
	case 1:
		cube_rotate.y += increment;
		break;
	case 2:
		cube_rotate.z += increment;
		break;
	case 3:
		cube_rotate.x += increment;
		cube_rotate.y += increment;
		cube_rotate.z += increment;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

// Trasladar el cubo
//void actionT(void)
//{
//	float increment = 0.015f;
//	// trasladar
//	switch (cube_traslate.current_axis)
//	{
//	case 0:
//		cube_traslate.x += increment;
//		break;
//	case 1:
//		cube_traslate.x -= increment;
//		break;
//	case 2:
//		cube_traslate.y += increment;
//		break;
//	case 3:
//		cube_traslate.y -= increment;
//		break;
//	case 4:
//		cube_traslate.z += increment;
//		break;
//	case 5:
//		cube_traslate.z -= increment;
//		break;
//	default:
//		break;
//	}
//}

// Handler para el cubo, fondo y ventana
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Borra la pantalla y depth buffers

	glLoadIdentity();   // Resetea la vista
	glTranslatef(0.0f, 0.0f, dnear); // Traslada el cubo al origen

	// Crear fondo

	// Poner textura al fondo
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(xmin, ymin, dfar);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(xmax, ymin, dfar);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(xmax, ymax, dfar);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(xmin, ymax, dfar);
	glEnd();
	
	// Para rotar con el mouse
	glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(yAngle, 0.0f, 1.0f, 0.0f);

	// Para rotar con el teclado
	glRotatef(cube_rotate.x, 1, 0, 0);
	glRotatef(cube_rotate.y, 0, 1, 0);
	glRotatef(cube_rotate.z, 0, 0, 1);

	//// Para trasladar con el teclado
	//glTranslatef(cube_traslate.x, 0, 0);
	//glTranslatef(0, cube_traslate.y, 0);
	//glTranslatef(0, 0, cube_traslate.z);

	//glScalef(5.0f, 5.0f, 5.0f);

	// Crear cubo

	//Poner textura al cubo
	glBindTexture(GL_TEXTURE_2D, textures[1]);
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
		cube_rotate.current_axis = 0;
		break;
	case 'y': // rota eje y
		cube_rotate.current_axis = 1;
		break;
	case 'z': //rota eje z
		cube_rotate.current_axis = 2;
		break;
	case 'r': // empieza o detiene rotación
		cube_rotate.rota ^= 1;
		glutIdleFunc(cube_rotate.rota ? actionR : NULL);
		break;
	case 32: // rota todos los ejes
		cube_rotate.current_axis = 3;
		break;
	//case 'a': // mueve a la izquierda
	//	cube_traslate.current_axis = 0;
	//	break;
	//case 'd': // mueve a la derecha
	//	cube_traslate.current_axis = 1;
	//	break;
	//case 'w': // mueve arriba
	//	cube_traslate.current_axis = 2;
	//	break;
	//case 's': // mueve abajo
	//	cube_traslate.current_axis = 3;
	//	break;
	//case 'q': // mueve cerca
	//	cube_traslate.current_axis = 4;
	//	break;
	//case 'e': // mueve lejos
	//	cube_traslate.current_axis = 5;
	//	break;
	//case 't': // empieza o detiene rotación
	//	cube_traslate.mueve ^= 1;
	//	glutIdleFunc(cube_traslate.mueve ? actionT : NULL);
	//	break;
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
	glutInit(&argc, argv);										// Inicia GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	// Pone modos para 3D
	glutInitWindowSize(windowWidth, windowHeight);				// Ancho y alto inicial de la ventana
	glutInitWindowPosition(windowPosX, windowPosY);				// Posición (x,y) inicial de la esquina superior izquierda
	glutCreateWindow(title);									// Crea la ventana con el título dado
	glutDisplayFunc(display);									// Registra el handler para la ventana
	glutReshapeFunc(reshape);									// Registra el handler para el re-size de la ventana
	glutKeyboardFunc(keyboard);									// Registra el handler para el teclado
	glutSpecialFunc(specialKey);								// Registra el handler para las teclas especiales
	glutMouseFunc(mouse);										// Registra el handler para el mouse
	glutMotionFunc(mouseMove);									// Registra el handler para el movimiento del mouse
	initGL();													// inicia OpenGl
	glutMainLoop();
	return 0;
}