#include "point.h"

void printVector(Vector3f v) {
    cout << "[" << v[0] << ", " << v[1] << ", " << v[2] << "]" << endl;
};

/*
String vectorString(Vector3f v) {
    String ret = "[";
    ret += to_string(v[0]);
    ret.erase(ret.length() - 4);
    ret += ", ";
    ret += to_string(v[1]);
    ret.erase(ret.length() - 4);
    ret += ", ";
    ret += to_string(v[2]);
    ret.erase(ret.length() - 4);
    ret += "]";
    return ret;
}
*/