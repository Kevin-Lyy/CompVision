// KEVIN LY
// H2 
// This file converts a gray level image to a binary one using a given threshold value 
// it has three arguments: the input image, the threshold and it returns a binary image 
#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

// This function goes through the image pixel by pixel and if the pixel is less than the threshold
// set the color black otherwise set it white 
// parameters: threshold, the image 
void grayToBin(int threshold, Image *an_image){
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

    //H2
    grayToBin(threshold_,&an_image);

    if (!WriteImage(output_file, an_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }
}