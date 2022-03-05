// Kevin Ly
// This is the header file for functions.cc which contains all the relevant functions for p3 and p4
#ifndef FUNCTIONS
#define FUNCTIONS

#include "image.h"
#include <cstdlib>
#include <vector>

using namespace std;


vector<int> objectCount(ComputerVisionProjects::Image *an_image);

vector<int> getAreaOfObjects(ComputerVisionProjects::Image *an_image, vector<int> num_of_obj);

vector<int> getCenterXorY(ComputerVisionProjects::Image *an_image, vector<int> num_of_obj,bool x_or_y);

#endif 