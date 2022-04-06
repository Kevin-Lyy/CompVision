// KEVIN LY
#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;
using namespace ComputerVisionProjects;

// goes through the image and if pixel is in a connected region add it's x or y value to the vector
// then divide the x or y with the # of pixels which gives the center column or row
// returns a vector that contains either the center x or center y of each connected region 
// parameter: the image, a vector with the number of objects labeled, a bool that tells the function to return either center column or center row
int getCenterXorY(ComputerVisionProjects::Image *an_image, bool x_or_y){
  int num_of_pixels=0, center_pixel=0;
  const int num_rows = an_image->num_rows();
  const int num_columns = an_image->num_columns();
  for(int i = 1;i < num_rows;i++){
    for(int j = 1;j < num_columns;j++){
        if(an_image->GetPixel(i,j) != 0){
            if(x_or_y){
                center_pixel = center_pixel + j;
            }
            else{
                center_pixel = center_pixel + i;
            }
            num_of_pixels += 1;
      }
    }
  }
  center_pixel = center_pixel/num_of_pixels;
  
  return center_pixel;
}


void findSphere(int threshold, Image *an_image,string out_put){
  if (an_image == nullptr) abort();
  const int num_rows = an_image->num_rows();
  const int num_columns = an_image->num_columns();

  for(int i = 0;i < num_rows;i++){
    for(int j = 0;j < num_columns;j++){
      if(an_image->GetPixel(i,j) < threshold){
        an_image->SetPixel(i,j,0);
      }
      else{
        an_image->SetPixel(i,j,255);
      }
    }
  }
  int center_column = getCenterXorY(an_image,1);
  int center_row = getCenterXorY(an_image,0);
  //an_image->SetPixel(center_row,center_column,100);

  int left_most=center_row,right_most=center_row,bottom_most=center_column,top_most=center_column;
  for(int i = 0;i < num_rows;i++){
    for(int j = 0;j < num_columns;j++){
        if(an_image->GetPixel(i,j) != 0){
            if(i < left_most){
                left_most = i;
            }
            if(i > right_most){
                right_most = i;
            }
            if(j < top_most){
                top_most = j;
            }
            if(j > bottom_most){
                bottom_most = j;
            }
        }
    }
  }
  int radius = (((right_most-left_most)+(bottom_most-top_most))/2)/2;
  ofstream output_file;
  output_file.open(out_put);
  output_file << center_row << " " << center_column << " " << radius;
//   cout << left_most <<" " << right_most << endl;
//   cout << top_most << " " << bottom_most << endl;
//   cout << radius << endl;
//   DrawLine(left_most,center_column,right_most,center_column,100,an_image);
//   DrawLine(center_row,top_most,center_row,bottom_most,100,an_image);


}


int main(int argc, char **argv){
    if (argc!=4) {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 0;
    }
    const string input_file(argv[1]);
    const int threshold_(stoi(argv[2]));
    const string output_file(argv[3]);

    Image an_image;
    if (!ReadImage(input_file, &an_image)) {
        cout <<"Can't open file " << input_file << endl;
        return 0;
    }

    //S1
    findSphere(threshold_,&an_image,output_file);


}