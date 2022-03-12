// KEVIN LY
#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>


using namespace std;
using namespace ComputerVisionProjects;

void locateEdges(Image *an_image){
  const int num_rows = an_image->num_rows();
  const int num_columns = an_image->num_columns();

  double edge_array[num_rows][num_columns];


  for(int i = 1;i < num_rows-1;i++){
    for(int j = 1;j < num_columns-1;j++){
      double derivative_of_x, derivative_of_y,epsilon,delta_sqr,mask;

      derivative_of_x = -1* an_image->GetPixel(i-1,j-1)+ an_image->GetPixel(i+1,j-1) + -2*an_image->GetPixel(i-1,j) 
      + 2*an_image->GetPixel(i+1,j) + -1*an_image->GetPixel(i-1,j+1) + an_image->GetPixel(i+1,j+1);
      
      derivative_of_y = an_image->GetPixel(i-1,j-1)+ 2*an_image->GetPixel(i,j-1) + an_image->GetPixel(i+1,j-1) 
      + -1*an_image->GetPixel(i-1,j+1) + -2*an_image->GetPixel(i,j+1) + -1*an_image->GetPixel(i+1,j+1);

      derivative_of_x = pow(derivative_of_x,2);
      derivative_of_y = pow(derivative_of_y,2);

      delta_sqr = sqrt(derivative_of_x+derivative_of_y);
      edge_array[i][j] = delta_sqr;
    }
  }

  for(int i = 0;i < num_rows;i++){
    for(int j = 0;j < num_columns;j++){
      an_image->SetPixel(i,j,edge_array[i][j]);
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

    //H1
    locateEdges(&an_image);

    if (!WriteImage(output_file, an_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

}
