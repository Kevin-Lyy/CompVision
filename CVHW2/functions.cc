#include "functions.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;
using namespace ComputerVisionProjects;

void connectedRegions(ComputerVisionProjects::Image *an_image) {
  if (an_image == nullptr) abort();
  const int num_rows = an_image->num_rows();
  const int num_columns = an_image->num_columns();

  for(int i = 0;i < num_rows;i++){
    for(int j = 0;j < num_columns;j++){
      if(an_image->GetPixel(i,j) < 120){
        an_image->SetPixel(i,j,0);
      }
      else{
        an_image->SetPixel(i,j,49);
      }
    }
  }

  // create two lists:the equivelency list and the changed list
  // equivelency list keeps track of every new pixel and keeps track of its color
  // then when there is an encounter with a darker pixel, it tracks the true pixel color
  vector<int> equiv_list;
  equiv_list.push_back(50);

  int pixel_above,pixel_left,new_pixel=0;

  for(int i = 1;i < num_rows;i++){
    for(int j = 1;j < num_columns;j++){
      if(an_image->GetPixel(i,j) == 49){
        pixel_above = an_image->GetPixel(i-1,j);
        pixel_left = an_image->GetPixel(i,j-1);

        //CHECK TO THE LEFT AND RIGHT IF THEY ARE BACKGROUND 
        if(pixel_above == 0 && pixel_left == 0){
          an_image->SetPixel(i,j,equiv_list[new_pixel]);
          equiv_list.push_back(equiv_list[new_pixel]+1);
          new_pixel++;
        }

        //IF LEFT AND TOP ARE DIFF VALUES
        else if(pixel_above != pixel_left){
          if(pixel_above == 0 && pixel_left != 0){
            an_image->SetPixel(i,j,pixel_left);
          }
          else if(pixel_left == 0 && pixel_above !=0 ){
            an_image->SetPixel(i,j,pixel_above);
          }
          else{
            // if left pixel color is darker than the top then set it to the darker one
            // then it finds the color on the list and sets it to the darker color
            if(pixel_left < pixel_above){
              an_image->SetPixel(i,j,pixel_left);
              for(int x = 0; x <equiv_list.size();x++){
                if(pixel_above == equiv_list[x]){
                  equiv_list[x] = pixel_left;
                }
              }
            }
            else if (pixel_left > pixel_above){
              an_image->SetPixel(i,j,pixel_above);
              for(int x = 0; x <equiv_list.size();x++){
                if(pixel_left == equiv_list[x]){
                  equiv_list[x] = pixel_above;
                }
              }
            }
          }
        }
        //TOP AND LEFT ARE THE SAME AND ARE NOT BACKROUND
        else if(pixel_above == pixel_left && pixel_above != 0){
          an_image->SetPixel(i,j,pixel_above);
        }
      }
    }
  }  

  // goes through the eqivalency list and sets all pixels to its lowest truest value
  for(int i = 0; i < equiv_list.size();i++){
    equiv_list[i] = equiv_list[equiv_list[i]-50]; 
  }

  // SECOND PASS
  // goes through the image and sets any pixels to the true value
  // this true value is one of the connected region's color 
  for(int i = 1;i < num_rows;i++){
    for(int j = 1;j < num_columns;j++){
      for(int x = 0;x < equiv_list.size();x++){
        if(an_image->GetPixel(i,j) ==x+50 ){
          an_image->SetPixel(i,j,equiv_list[x]);
        }
      }
    }
  }
}

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

vector<int> getCenterXorY(ComputerVisionProjects::Image *an_image, vector<int> num_of_obj,bool x_or_y){
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