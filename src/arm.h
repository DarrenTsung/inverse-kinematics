#ifndef ARM_H
#define ARM_H

#include "include.h"
#include "segment.h"

class Arm {
    private:
        vector<Segment*> segments;
        Point3f base;

        Matrix<float,1,3> compute_jacovian_segment(int seg_num, Point3f goal_point, Vector3f angle);

        // computes end_effector up to certain number of segments
        Point3f calculate_end_effector(int segment_num = -1);

        // get the total magnitude of all the segments in the arm
        float get_max_length();
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

        // solve the arm for some point
        void solve(Point3f goal_point, int life_count);

        // draw the arm
        void draw();
};

#endif
