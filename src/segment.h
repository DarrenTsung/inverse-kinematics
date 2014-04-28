#ifndef SEGMENT_H
#define SEGMENT_H

#include "include.h"

typedef enum {
    BALLJOINT
} JointType;

class Segment {
    private:
        // magnitude of the segment
        float mag;
        // transformation matrix (rotation) of the segment
        Transform<float,3,Affine> T;

        // the type of joint the origin of the segment is
        // connected to
        JointType joint;

    public:
        // constructors
        Segment();
        Segment(float magnitude, JointType jt);

        // draw takes in the startpoint and returns the endpoint
        Point3f draw(Point3f start_point);
};

#endif // SEGMENT_H
