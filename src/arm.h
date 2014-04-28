#ifndef ARM_H
#define ARM_H

#include "include.h"
#include "segment.h"

class Arm {
    private:
        vector<Segment*> segments;
        Point3f base;

    public:
        // constructors
        Arm();
        Arm(vector<Segment*> segs, Point3f pos);

        // set the position of base
        void set_base(Point3f pos);
        // get the position of the base
        Point3f get_base();

        // set the segments
        void set_segments(vector<Segment*> segs);

        // draw the arm
        void draw();
};

#endif
