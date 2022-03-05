// KEVIN LY
// P2
// This file takes a binary image and segements and labels each connected region into a vector and
// colors them a different color
// it has two arguments the input image and retuns it with each connected region labeled
#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace ComputerVisionProjects;

// This function does a sequential labeling algorithm using the colors of the pixels above and
// to the left to determine its color and does a second pass to set all objects to its true color
// parameters: the image 
void connectedRegions(Image *an_image) {
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


int main(int argc, char **argv){
    if (argc!=3) {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 0;
    }
    const string input_file(argv[1]);
    const string output_file(argv[2]);

    Image an_image;
    if (!ReadImage(input_file, &an_image)) {
        cout <<"Can't open file " << input_file << endl;
        return 0;
    }

    //P2
    connectedRegions(&an_image);

    if (!WriteImage(output_file, an_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

}