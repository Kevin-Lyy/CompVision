// KEVIN LY
// P3
// This file takes the labeled image as an input and computes attribues into a database
// it then draws a line to demonstrate the orentation of the object
#include "functions.h"
#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;
using namespace ComputerVisionProjects;

// This function calculates the attributes into vectors and fills a database with:
// object label, center row, center column, minimum moment of inertia, area, roundedness and orentation
// parameters: the image, an empty database it will fill 
void generateDatabase(Image *an_image, string database){
  const int num_rows = an_image->num_rows();
  const int num_columns = an_image->num_columns();
  //connectedRegions(an_image);


  vector<int> num_of_objects;
  num_of_objects = objectCount(an_image);

  vector<int> area_of_objects = getAreaOfObjects(an_image, num_of_objects);

  vector<int> center_column(num_of_objects.size()),center_row(num_of_objects.size());
  center_column = getCenterXorY(an_image, num_of_objects,1);
  center_row = getCenterXorY(an_image, num_of_objects,0);

  // calculates the a b and c of the objects based on an equation given by the proffessor
  vector<int> a(num_of_objects.size()), b(num_of_objects.size()), c(num_of_objects.size()) ;
  for(int i = 1;i < num_rows;i++){
    for(int j = 1;j < num_columns;j++){
      for(int x = 0;x < num_of_objects.size();x++){
        if(an_image->GetPixel(i,j) == num_of_objects[x]){
          a[x] = a[x] + pow((i-center_row[x]),2);
          b[x] = b[x] + (i-center_row[x])*(j-center_column[x]);
          c[x] = c[x] + pow((j-center_column[x]),2);
        }
      }
    }
  }
  for(int i = 0;i < b.size();i++){
    b[i] = 2*b[i];
  }


  // theta we will use for the object
  vector<double> theta1(num_of_objects.size());
  for(int x = 0;x < num_of_objects.size();x++){
    theta1[x] = atan2(b[x],a[x]-c[x])/2.0;
  }

  // this is the miniumn moment of inertia labeled as emin
  vector<double> e_min(num_of_objects.size());
  for(int x = 0;x < num_of_objects.size();x++){
    e_min[x] = a[x] * sin(theta1[x]) * sin(theta1[x]) - b[x] * sin(theta1[x]) * cos(theta1[x]) + c[x] * cos(theta1[x]) * cos(theta1[x]);
  }
  
  vector<double> theta2(num_of_objects.size());
  for(int x = 0;x < num_of_objects.size();x++){
    theta2[x] = theta1[x] + M_PI/2.0;
  }

  vector<double> e_max(num_of_objects.size());
  for(int x = 0;x < num_of_objects.size();x++){
    e_max[x] = a[x] * sin(theta2[x]) * sin(theta2[x]) - b[x] * sin(theta2[x]) * cos(theta2[x]) + c[x] * cos(theta2[x]) * cos(theta2[x]);
  }

  vector<double> roundedness(num_of_objects.size());
  for(int x = 0;x < num_of_objects.size();x++){
    roundedness[x] = e_min[x]/e_max[x];
  }

  vector<double> theta_degrees(num_of_objects.size());
  for(int x = 0;x < num_of_objects.size();x++){
    theta_degrees[x] = 180.0 * theta1[x]/M_PI;
  }
  
  vector<double> rho(num_of_objects.size());
  for(int i = 0;i < num_of_objects.size();i++){
    rho[i] = center_column[i]*cos(theta1[i]) - center_row[i]*sin(theta1[i]);
  }
  
  // finds a new X and new Y that make up coordinates to draw a line to
  // that demonstrate the orentation of the object
  vector<int> newX(num_of_objects.size()), newY(num_of_objects.size());
  for(int i = 0;i < num_of_objects.size();i++){
    newX[i] = center_row[i] + 20;
    newY[i] = (newX[i] * sin(theta1[i]) + rho[i])/cos(theta1[i]);
  }

  for(int i = 0;i < num_of_objects.size();i++){
    DrawLine(center_row[i],center_column[i],newX[i],newY[i],255,an_image);
  }
  

  // writes all the information into a database
  ofstream databased;
  databased.open(database);
  for(int i = 0; i < num_of_objects.size();i++){
    databased << num_of_objects[i] << " ";
    databased << center_row[i] << " ";
    databased << center_column[i] << " ";
    databased << e_min[i] << " ";
    databased << area_of_objects[i] << " ";
    databased << roundedness[i] << " ";
    databased << theta_degrees[i] << " ";
    databased << "\n";
  }
  databased.close();
}

int main(int argc, char **argv){
  if (argc!=4) {
    printf("Usage: %s file1 file2\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);
  const string outdatabase(argv[2]);
  const string output_file(argv[3]);

  Image an_image;
  if (!ReadImage(input_file, &an_image)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }

  //P3
  generateDatabase(&an_image, outdatabase);
  
  if (!WriteImage(output_file, an_image)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }

}