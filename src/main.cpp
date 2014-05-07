#include "include.h"
#include "arm.h"

#define PI 3.14159265359

using namespace std;

Arm mainArm;

float angle = 0.0;
GLdouble eyeX=0.0;
GLdouble eyeY=-10;
GLdouble eyeZ=4.0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// clear the color buffer

    angle += 360./30.;

    Point3f goal(cos(angle*PI/180.0f), sin(angle*PI/180.0f), 1);
    goal.normalize();
    goal *= 6;
    //goal += Vector3f(-1,0,0);
    mainArm.solve(goal, 100);

    // set camera parameters
	GLdouble centerX=eyeX;
	GLdouble centerY=eyeY+1;
	GLdouble centerZ=eyeZ;
	GLdouble upX=0.;
	GLdouble upY=0.;
	GLdouble upZ=1.;

    glMatrixMode(GL_MODELVIEW);			        // indicate we are specifying camera transformations
    glLoadIdentity();

    gluLookAt(eyeX,eyeY,eyeZ,
                centerX,centerY,centerZ,
                upX,upY,upZ);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(60, 1, 1, 100);

    // drawing is done here
    mainArm.draw();

    float c = 0.2;
    Point3f a0 = goal + Vector3f(-c, 0, c);
    Point3f a1 = goal + Vector3f(0, 0, -c);
    Point3f a2 = goal + Vector3f(c, 0, c);
    Vector3f n2(0, -1, 0);
    glBegin(GL_TRIANGLES);
        glNormal3f(n2[0], n2[1], n2[2]);
        glVertex3f(a0[0], a0[1], a0[2]);
        glVertex3f(a1[0], a1[1], a1[2]);
        glVertex3f(a2[0], a2[1], a2[2]);
    glEnd();
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
    case '-':
        display();
        break;
    }
}

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
} ArrowKeyState;

ArrowKeyState arrow_state;

void handleSpecialKeypress(int key, int x, int y) {
    int mod = glutGetModifiers();
    switch (key) {
        case GLUT_KEY_LEFT:
            arrow_state = LEFT;
            // handle left key
            if (mod == GLUT_ACTIVE_SHIFT) {
                // translate it
                eyeX -= 0.1;
            } else {
                // rotate it around the normal
                //mainBez.transform(ROTATION, mainBez.get_normal(), 8);
            }
            break;

        case GLUT_KEY_RIGHT:
            arrow_state = RIGHT;
            // handle right key
            if (mod == GLUT_ACTIVE_SHIFT) {
                // translate it
                eyeX += 0.1;
            } else {
                // rotate it around the normal
            }
            break;

        case GLUT_KEY_UP:
            arrow_state = UP;
            // handle up key
            if (mod == GLUT_ACTIVE_SHIFT) {
                // translate it
                eyeZ += 0.1;
            } else {
                // rotate it around the right vector
                eyeY += 0.1;
            }
            break;

        case GLUT_KEY_DOWN:
            arrow_state = DOWN;
            // handle down key
            if (mod == GLUT_ACTIVE_SHIFT) {
                // translate it
                eyeZ -= 0.1;
            } else {
                // rotate it around the right vector
                eyeY -= 0.1;
            }
            break;
    }
    display();
}

void handleSpecialKeyReleased(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
            arrow_state = NONE;
            break;
    }
}

int main(int argc, char* argv[]) {
    vector<Segment*> segs;
    Segment *new_seg = new Segment(2, BALLJOINT);
    segs.push_back(new_seg);
    new_seg = new Segment(3, BALLJOINT);
    segs.push_back(new_seg);
    new_seg = new Segment(1, BALLJOINT);
    segs.push_back(new_seg);

    mainArm.set_segments(segs);

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
    glutSpecialFunc(handleSpecialKeypress);
    glutSpecialUpFunc(handleSpecialKeyReleased);

	// shading stuff?
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// random light behind your eyes
	GLfloat diffuse0[]={1.5, 1.5, 1.5, 1.0};
	GLfloat ambient0[]={1.0, 1.0, 1.0, 1.0};
	GLfloat specular0[]={1.0, 1.0, 1.0, 1.0};
	GLfloat light0_pos[]={-5.0, 0.0, 3.0, 1.0};

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);


    glutMainLoop();

    return 0;
}
