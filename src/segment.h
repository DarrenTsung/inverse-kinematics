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
        AngleAxisf T, saved_T, last_T;

        // save the angle when computing the changes
        Vector3f saved_angle;

        // the type of joint the origin of the segment is
        // connected to
        JointType joint;

    public:
        // constructors
        Segment();
        Segment(float magnitude, JointType jt);

        // returns end point in object space
        Point3f get_end_point();

        // draw takes in the startpoint and returns the endpoint
        Point3f draw(Point3f start_point);

        Vector3f get_right();
        Vector3f get_up();
        Vector3f get_z();

        AngleAxisf get_T();
        float get_mag();

        void save_transformation();
        void load_transformation();

        void save_last_transformation();
        void load_last_transformation();

        void apply_angle_change(float rad_change, Vector3f angle);

        // clear transformations
        void reset();
        // randomize transformation
        void randomize();

        // apply transformation
        void transform(AngleAxisf t);
};

#endif // SEGMENT_H
