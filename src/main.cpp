#include "include.h"

using namespace std;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// clear the color buffer

    glMatrixMode(GL_MODELVIEW);			        // indicate we are specifying camera transformations
    glLoadIdentity();				        // make sure transformation is "zero'd"

    // drawing is done here
    // end drawing

    glFlush();
    glutSwapBuffers();					// swap buffers (we earlier set double buffer)
}

void reshape(int w, int h) {

}

void handleInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:    // ESCAPE KEY
        exit(0);
        break;
    // spacebar closes window
    case ' ':
        exit(0);
        break;
    }
}

int main(int argc, char* argv[]) {
    //This initializes glut
    glutInit(&argc, argv);

    //This tells glut to use a double-buffered window with red, green, and blue channels
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Inverse-Kinematics");

    glutDisplayFunc(display);				// function to run when its time to draw something
    glutReshapeFunc(reshape);				// function to run when the window gets resized

    // set handleInput() function to take keyboard events
    glutKeyboardFunc(handleInput);

	// shading stuff?
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// random light behind your eyes
	GLfloat diffuse0[]={1.0, 1.0, 1.0, 1.0};
	GLfloat ambient0[]={1.0, 1.0, 1.0, 1.0};
	GLfloat specular0[]={1.0, 1.0, 1.0, 1.0};
	GLfloat light0_pos[]={0.0, 0.0, 5.0, 1.0};

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

    glutMainLoop();

    return 0;
}
