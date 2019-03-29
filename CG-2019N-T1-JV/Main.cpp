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
quadrado topo(0, 6, 0, 5.0, 0.5f, 0.8f, 1, 0);
quadrado garra1(1.5, 4.8, 0, 1, 1, 0.5, 0);
quadrado garra2(-1.5, 4.8, 0, 1, 1, 0.5, 0.5);

GLfloat angley = 0;
GLfloat anglex = 0;
GLfloat positionX = 0;

void renderCoordinateAxis(){
	glBegin(GL_LINES);
		// X axis - green color
		glColor3f(0, 1, 0);
		glVertex2f(-50.0, 0.0);
		glVertex2f(50.0, 0.0);
	glEnd();

	glBegin(GL_LINES);
		// Y axis - blue color
		glColor3f(0, 0, 1);
		glVertex2f(0.0, -50.0);
		glVertex2f(0.0, 50.0);
	glEnd();

	glBegin(GL_LINES);
		// Y axis - blue color
		glColor3f(0, 0, 1);
		glVertex3f(0.0, 0.0, -50.0);
		glVertex3f(0.0, 0.0, -50.0);
	glEnd();
}

void display() {
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0, -10.0, -40.0f); // "ALTERA" VIS홒 DA "CAMERA"
	renderCoordinateAxis();
	
	glPushMatrix();
		// ROTA합ES GLOBAIS
		glRotatef(angley, 0, 1, 0);
		glRotatef(anglex, 1, 0, 0);
		glTranslatef(positionX, 0, 0);


		// PLOT => PRET0
		glColor3f(base.R, base.G, base.B);
		glTranslatef(base.x, base.y, base.z);
		glutWireCube(base.lado);

		// ROTA플O => VERMELHO
		glRotatef(central1.angle, 0, 0, 1);
		// PLOT => VERMELHO
		glColor3f(central1.R, central1.G, central1.B);
		glTranslatef(central1.x, central1.y, central1.z);
		glutWireCube(central1.lado);

		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		glPushMatrix();
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glTranslatef(0, 0, -2.5);
			gluCylinder(quadratic, 3, 3, 0.5, 32, 32);
		glPopMatrix();

		// ROTA플O => VERDE
		glRotatef(central2.angle, 0, 0, 1);
		// PLOT => VERDE
		glColor3f(central2.R, central2.G, central2.B);
		glTranslatef(central2.x, central2.y, central2.z);
		glutWireCube(central2.lado);

		glPushMatrix();
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glTranslatef(0, 0, -2.5);
			gluCylinder(quadratic, 3, 3, 0.5, 32, 32);
		glPopMatrix();

		// ROTA플O => AZUL
		glRotatef(topo.angle, 0, 0, 1);
		// PLOT => AZUL
		glColor3f(topo.R, topo.G, topo.B);
		glTranslatef(topo.x, topo.y, topo.z);
		glScalef(1, 1.75, 1);
		glutWireCube(topo.lado);

		glPushMatrix();
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glTranslatef(0, 0, -2.5);
			gluCylinder(quadratic, 3, 3, 0.5, 32, 32);
		glPopMatrix();

		// GARRAS

		glPushMatrix();
			glColor3f(garra1.R, garra1.G, garra1.B);
			glTranslatef(garra1.x, garra1.y, garra1.z);
			glRotatef(garra1.angle, 0, 0, 1);
			glScalef(1, 5, 1);
			glutWireCube(garra1.lado);
		glPopMatrix();

		glPushMatrix();
			glColor3f(garra2.R, garra2.G, garra2.B);
			glTranslatef(garra2.x, garra2.y, garra2.z);
			glRotatef(garra2.angle, 0, 0, 1);
			glScalef(1, 5, 1);
			glutWireCube(garra2.lado);
		glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

void update(int x) {
	glutPostRedisplay();
	glutTimerFunc(UPDATE_INTERVAL_MS, update, 0);
}

void keyboard(int key, int x, int y) {
	if (key == GLUT_KEY_RIGHT) { // GIRA PARA DIREITA
		angley += 5;
	}
	if (key == GLUT_KEY_LEFT) { // GIRA PARA ESQUERDA
		angley -= 5;
	}

	// EXTRA DO EXTRA
	if (key == GLUT_KEY_UP) { // GIRA NO X
		anglex += 5;
	}
	if (key == GLUT_KEY_DOWN) { // GIRA NO X
		anglex -= 5;
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


	// MOVIMENTO DAS GARRAS
	if ((key == 'R' || key == 'r') && garra1.angle >= -5) { // ABRE
		garra1.angle -= 1;
		garra2.angle += 1;
	}
	if ((key == 'F' || key == 'f') && garra1.angle <= 20) { // FECHA
		garra1.angle += 1;
		garra2.angle -= 1;
	}
}

void initView() {
	glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 200.0);

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