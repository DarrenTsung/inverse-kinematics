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
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    // to go back to normal mode
    //glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glShadeModel(GL_SMOOTH);
    //glShadeModel(GL_FLAT);

    int seg_size = segments.size();
    Point3f start_point = base;

    for(int i=0; i<seg_size; i++) {
        start_point = segments[i]->draw(start_point);
    }
}
