// Kevin Ly
// This file holds all the functions used both in p3 and p4 
#include "functions.h"
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>

using namespace std;
using namespace ComputerVisionProjects;


// This function loops through an image that has its connected regions labels and returns a vector with them
// parameter: the image 
vector<int> objectCount(ComputerVisionProjects::Image *an_image){
  vector<int> num_of_objects;
  const int num_rows = an_image->num_rows();
  const int num_columns = an_image->num_columns();
  bool is_in=false;

  for(int i = 1;i < num_rows;i++){
    for(int j = 1;j < num_columns;j++){
      if(an_image->GetPixel(i,j) != 0){
        for(int x = 0;x < num_of_objects.size();x++){
          if( an_image->GetPixel(i,j) == num_of_objects[x]){
            is_in = true;
          }
        }
        if(!is_in){
          num_of_objects.push_back(an_image->GetPixel(i,j));
        }
        is_in = false;
      }
    }
  }
  return num_of_objects;
}

// Goes through the image and if the pixel is in a connected region then add it to the sum
// returns a vectors with the areas of the connected region 
// parameter: the image, a vector with the number of objects labeled  
vector<int> getAreaOfObjects(ComputerVisionProjects::Image *an_image, vector<int> num_of_obj){
  const int num_rows = an_image->num_rows();
  const int num_columns = an_image->num_columns();
  vector<int> area_of_objects(num_of_obj.size());
  for(int i = 1;i < num_rows;i++){
    for(int j = 1;j < num_columns;j++){
      for(int x = 0;x < num_of_obj.size();x++){
        if(an_image->GetPixel(i,j) == num_of_obj[x]){
          area_of_objects[x] = area_of_objects[x]+1;
        }
      }
    }
  }
  return area_of_objects;
}

// goes through the image and if pixel is in a connected region add it's x or y value to the vector
// then divide the x or y with the # of pixels which gives the center column or row
// returns a vector that contains either the center x or center y of each connected region 
// parameter: the image, a vector with the number of objects labeled, a bool that tells the function to return either center column or center row
vector<int> getCenterXorY(ComputerVisionProjects::Image *an_image, vector<int> num_of_obj, bool x_or_y){
  vector<int> num_of_pixels(num_of_obj.size()), center_pixels(num_of_obj.size());
  const int num_rows = an_image->num_rows();
  const int num_columns = an_image->num_columns();
  for(int i = 1;i < num_rows;i++){
    for(int j = 1;j < num_columns;j++){
      for(int x = 0;x < num_of_obj.size();x++){
        if(an_image->GetPixel(i,j) == num_of_obj[x]){
          if(x_or_y){
            center_pixels[x] = center_pixels[x] + j;
          }
          else{
            center_pixels[x] = center_pixels[x] + i;
          }
          num_of_pixels[x] += 1;
        }
      }
    }
  }
  for(int x = 0;x < num_of_obj.size();x++){
    center_pixels[x] = center_pixels[x]/num_of_pixels[x];
  }   
  return center_pixels;
}

