#ifndef INCLUDE_H
#define INCLUDE_H

#include <vector>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#endif

#ifdef _WIN32
//#define EIGEN_DONT_ALIGN_STATICALLY

#define EIGEN_DONT_VECTORIZE
#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
#endif

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

typedef string String;
#include "point.h"

#endif // INCLUDE_H
