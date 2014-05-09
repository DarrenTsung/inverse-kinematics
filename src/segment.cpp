#include "segment.h"

#define PI 3.14159265359

Segment::Segment() {
    T = T.Identity();
}

Segment::Segment(float magnitude, JointType jt) {
    T = T.Identity();
    mag = magnitude;
    joint = jt;
}

Point3f Segment::get_end_point() {
    Point3f a;

    // start with vector going into the Z direction
    a = Point3f(0, 0, mag);
    // transform into the rotation of the segment
    a = T * a;

    return a;
}

Point3f Segment::draw(Point3f start_point) {
    Point3f a0, a1, a2;
    Vector3f n0, n1, n2;

    // number of segments to divide the draw polygon into
    int seg_count = 5;

    // calculate the end point of the segment
    // start with vector going into the Z direction
    a2 = Point3f(0, 0, mag);
    // transform into the rotation of the segment
    a2 = T * a2;

    // normal for the end point is just in the same direction of the end_point
    n2 = a2.normalized();

    // translate the end point to the start point
    a2 += start_point;

    float scale = 0.5f;
    for (int i=0; i<seg_count; i++) {
        // a0 and a1 are points on the unit circle divided by seg_count
        // a0 is i+1 so the points go in counter-clockwise order
        a0 = Point3f(scale*cos(i*(2*PI/seg_count)), scale*sin(i*(2*PI/seg_count)), 0);
        a1 = Point3f(scale*cos((i+1)*(2*PI/seg_count)), scale*sin((i+1)*(2*PI/seg_count)), 0);

        // scale appropriately

        // transform a0 and a1 into the rotation of the segment
        a0 = T * a0;
        a1 = T * a1;

        // a2 is the end point of the segment
        // ^^calculated outside for loop

        // normals are just the points normalized
        n0 = a0.normalized();
        n1 = a1.normalized();

        // translate the points to the start point
        a0 += start_point;
        a1 += start_point;

        glBegin(GL_TRIANGLES);
            // counter-clockwise
            glNormal3f(n0[0], n0[1], n0[2]);
            glVertex3f(a0[0], a0[1], a0[2]);

            glNormal3f(n1[0], n1[1], n1[2]);
            glVertex3f(a1[0], a1[1], a1[2]);

            glNormal3f(n2[0], n2[1], n2[2]);
            glVertex3f(a2[0], a2[1], a2[2]);
            /*
            n0 = (a2 - a1).cross(a0 - a1);
            n0 = n0.normalized();
            glNormal3f(n0[0], n0[1], n0[2]);
            glVertex3f(a0[0], a0[1], a0[2]);
            glVertex3f(a1[0], a1[1], a1[2]);
            glVertex3f(a2[0], a2[1], a2[2]);
            */
        glEnd();
    }

    return a2;
}

Vector3f Segment::get_right() {
    return T*Vector3f(1,0,0);
}

Vector3f Segment::get_up() {
    return T*Vector3f(0,1,0);
}

Vector3f Segment::get_z() {
    return T*Vector3f(0,0,1);
}

AngleAxisf Segment::get_T() {
    return T;
}

float Segment::get_mag() {
    return mag;
}

void Segment::save_last_transformation() {
    last_T = T;
}

void Segment::load_last_transformation() {
    T = last_T;
}

void Segment::save_transformation() {
    saved_T = T;
}

void Segment::load_transformation() {
    T = saved_T;
}

void Segment::apply_angle_change(float rad_change, Vector3f angle) {
    T = AngleAxisf(rad_change, angle) * T;
}

void Segment::transform(AngleAxisf t) {
    T = t * T;
}

void Segment::reset() {
    T = T.Identity();
}

void Segment::randomize() {
    // randomize
    T = AngleAxisf(PI/2, Vector3f::Random()) * T;
}
