#include "arm.h"

Arm::Arm() {
    base = Point3f(0,0,0);
}

Arm::Arm(vector<Segment*>segs, Point3f pos) {
    base = Point3f(0,0,0);
    set_segments(segs);
    set_base(pos);
}

void Arm::set_base(Point3f pos) {
    base = pos;
}

Point3f Arm::get_base() {
    return base;
}

void Arm::set_segments(vector<Segment*> segs) {
    segments = segs;
}

void Arm::draw() {
    // wireframe mode
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    // to go back to normal mode
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glShadeModel(GL_SMOOTH);
    //glShadeModel(GL_FLAT);

    Point3f a0, a1, a2, a3;
    Vector3f n0, n1, n2, n3;
    // draw base
    float length = 10;

    a0 = Point3f(-length, -length, 0);
    a1 = Point3f(length, -length, 0);
    a2 = Point3f(length, length, 0);
    a3 = Point3f(-length, length, 0);

    n0 = Vector3f(0, 0, 1);
    n1 = Vector3f(0, 0, 1);
    n2 = Vector3f(0, 0, 1);
    n3 = Vector3f(0, 0, 1);

    glBegin(GL_QUADS);
        glNormal3f(n0[0], n0[1], n0[2]);
        glVertex3f(a0[0], a0[1], a0[2]);

        glNormal3f(n1[0], n1[1], n1[2]);
        glVertex3f(a1[0], a1[1], a1[2]);

        glNormal3f(n2[0], n2[1], n2[2]);
        glVertex3f(a2[0], a2[1], a2[2]);

        glNormal3f(n3[0], n3[1], n3[2]);
        glVertex3f(a3[0], a3[1], a3[2]);
    glEnd();

    int seg_size = segments.size();
    Point3f start_point = base;

    for(int i=0; i<seg_size; i++) {
        start_point = segments[i]->draw(start_point);
    }
}
