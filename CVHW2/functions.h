#ifndef FUNCTIONS
#define FUNCTIONS

#include "image.h"
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;


void connectedRegions(ComputerVisionProjects::Image *an_image);

vector<int> objectCount(ComputerVisionProjects::Image *an_image);

vector<int> getAreaOfObjects(ComputerVisionProjects::Image *an_image, vector<int> num_of_obj);

vector<int> getCenterXorY(ComputerVisionProjects::Image *an_image, vector<int> num_of_obj,bool x_or_y);

#endif 