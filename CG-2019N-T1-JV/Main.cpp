#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 800;

const unsigned int FRAMES_PER_SECOND = 30;
const unsigned int UPDATE_INTERVAL_MS = 1000 / FRAMES_PER_SECOND;

class quadrado {
public:
	GLfloat x, y, z, lado, R = 0, G = 0, B = 0, angle = 0;

	quadrado(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat lado1, GLfloat R1, GLfloat G1, GLfloat B1, GLfloat angle1) {
		x = x1;
		y = y1;
		z = z1;
		lado = lado1;
		R = R1;
		G = G1;
		B = B1;
		angle = angle1;
	}
	quadrado(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat lado1, GLfloat R1, GLfloat G1, GLfloat B1) {
		x = x1;
		y = y1;
		z = z1;
		lado = lado1;
		R = R1;
		G = G1;
		B = B1;
	}
};

quadrado base(0, 0, 0, 5.0, 0, 0, 0);
quadrado central1(0, 5, 0, 5.0, 1, 0, 0, 0);
quadrado central2(0, 5, 0, 5.0, 0, 1, 0, 0);
quadrado topo(0, 5, 0, 5.0, 0.5f, 0.8f, 1, 0);

GLfloat angley = 0;
GLfloat positionX = 0;

void renderCoordinateAxis()
{
	// X axis - green color
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
		// Left side, negative X
		glVertex2f(-50.0, 0.0);
		glVertex2f(0.0, 0.0);

		// Right side, positive X
		glVertex2f(0.0, 0.0);
		glVertex2f(50.0, 0.0);
	glEnd();

	// Y axis - blue color
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		// Top side, positive Y
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 50.0);

		// Bottom side, negative Y
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, -50.0);
	glEnd();
}

void display() {
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	renderCoordinateAxis();

	glTranslatef(0, -5.0, -30.0f);
	
	glPushMatrix();
		glTranslatef(positionX, 0, 0);
		// PLOT => PRET0
		glColor3f(base.R, base.G, base.B);
		glTranslatef(base.x, base.y, base.z);
		glRotatef(angley, 0, 1, 0);
		glutWireCube(base.lado);

		// ROTA플O => VERMELHO
		glRotatef(central1.angle, 0, 0, 1);
		// PLOT => VERMELHO
		glColor3f(central1.R, central1.G, central1.B);
		glTranslatef(central1.x, central1.y, central1.z);
		glutWireCube(central1.lado);

		// ROTA플O => VERDE
		glRotatef(central2.angle, 0, 0, 1);
		// PLOT => VERDE
		glColor3f(central2.R, central2.G, central2.B);
		glTranslatef(central2.x, central2.y, central2.z);
		glutWireCube(central2.lado);

		// ROTA플O => AZUL
		glRotatef(topo.angle, 0, 0, 1);
		//PLOT => AZUL
		glColor3f(topo.R, topo.G, topo.B);
		glTranslatef(topo.x, topo.y, topo.z);
		glScalef(1, 1.25, 1);
		glutWireCube(topo.lado);

	glPopMatrix();

	glutSwapBuffers();
}

void update(int x) {
	glutPostRedisplay();
	glutTimerFunc(UPDATE_INTERVAL_MS, update, 0);
}

void keyboard(int key, int x, int y) {
	if (key == GLUT_KEY_RIGHT) { // RIGHT
		angley += 5;
	}
	if (key == GLUT_KEY_LEFT) { // LEFT
		angley -= 5;
	}
}

void keyboardAWSD(unsigned char key, int x, int y) {
	// ROTA플O DO VERMELHO
	if ((key == 'Q' || key == 'q') && central1.angle >= -30) { // VAI PRA ESQUERDA
		central1.angle -= 5;
	}
	if ((key == 'A' || key == 'a' ) && central1.angle <= 30) { // VAI PRA DIREITA
		central1.angle += 5;
	}

	// ROTA플O DO VERDE
	if ((key == 'W' || key == 'w') && central2.angle >= -30) { // VAI PRA ESQUERDA
		central2.angle -= 5;
	}
	if ((key == 'S' || key == 's') && central2.angle <= 30) { // VAI PRA DIREITA
		central2.angle += 5;
	}

	// ROTA플O DO AZUL
	if ((key == 'E' || key == 'e') && topo.angle >= -30) { // VAI PRA ESQUERDA
		topo.angle -= 5;
	}
	if ((key == 'D' || key == 'd') && topo.angle <= 30) { // VAI PRA DIREITA
		topo.angle += 5;
	}

	// MOVIMENTO EM X
	if (key == 'Z' || key == 'z') { // VAI PRA ESQUERDA
		positionX -= 1;
	}
	if (key == 'X' || key == 'x') { // VAI PRA DIREITA
		positionX += 1;
	}
}

void initView() {
	glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 50.0);

	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Transformation - Simple");
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);
	glutKeyboardFunc(keyboardAWSD);

	initView();

	glutTimerFunc(UPDATE_INTERVAL_MS, update, 0);

	glutMainLoop();
	return 0;
}