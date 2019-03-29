#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 800;

const unsigned int FRAMES_PER_SECOND = 30;
const unsigned int UPDATE_INTERVAL_MS = 1000 / FRAMES_PER_SECOND;

float anglex = 0;
float angley = 0;


void renderCoordinateAxis()
{
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 0.0);

	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 0.0);
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);

	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 0.0);

	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 0.0);
	glEnd();

}

class quadrado {
public:
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat z = 0.0;
	GLfloat lado = 5.0;
};

quadrado q;

void display(){
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	renderCoordinateAxis();
	glTranslatef(0, 0, -10.0f);

	glColor3f(1, 0, 0);
	glTranslatef(q.x, q.y, q.z);
	glRotatef(anglex, 1, 0, 0);
	glRotatef(angley, 0, 1, 0);
	glutWireCube(q.lado);

	glutSwapBuffers();
}

void update(int x){
	glutPostRedisplay();
	glutTimerFunc(UPDATE_INTERVAL_MS, update, 0);
}

void keyboard(int key, int x, int y){
	if (key == GLUT_KEY_UP) { // UP
		anglex -= 5;
	}
	if (key == GLUT_KEY_DOWN) { // DOWN
		anglex += 5;
	}
	if (key == GLUT_KEY_RIGHT) { // RIGHT
		angley += 5;
	}
	if (key == GLUT_KEY_LEFT) { // LEFT
		angley -= 5;
	}
}

void keyboardAWSD(unsigned char key, int x, int y) {
	if (key == 87 || key == 'w') { // W
		q.y += 0.1;
	}
	if (key == 83 || key == 's') { // S
		q.y -= 0.1;
	}
	if (key == 68 || key == 'd') { // D
		q.x += 0.1;
	}
	if (key == 65 || key == 'a') { // A
		q.x -= 0.1;
	}
	if (key == 81 || key == 'q') { // Q
		q.z -= 0.1;
	}
	if (key == 69 || key == 'e') { // E
		q.z += 0.1;
	}
}

void initView(){
	glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGHT);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 200.0);

	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
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