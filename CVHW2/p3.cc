#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;
using namespace ComputerVisionProjects;

void conRegions(Image *an_image) {
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

  vector<int> equiv_list,changed_list;
  equiv_list.push_back(50);
  changed_list.push_back(50);
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
            //TOP IS BACKGROUND
            if(pixel_above == 0 && pixel_left != 0){
              an_image->SetPixel(i,j,pixel_left);
            }
            // LEFT IS BACKGROUND
            else if(pixel_left == 0 && pixel_above !=0 ){
              an_image->SetPixel(i,j,pixel_above);
            }
            else{
              if(pixel_left < pixel_above){
                an_image->SetPixel(i,j,pixel_left);
                for(int x = 0; x <equiv_list.size();x++ ){
                  if(pixel_above == equiv_list[x]){
                    equiv_list[x] = pixel_left;
                  }
                }
              }
              else if (pixel_left > pixel_above){
                an_image->SetPixel(i,j,pixel_above);
                for(int x = 0; x <equiv_list.size();x++ ){
                  if(pixel_left == equiv_list[x]){
                    equiv_list[x] = pixel_above;
                  }
                }
              }
            }
          }
          //TOP AND LEFT ARE THE SAME AND ARE NOT BACKROUND BUT DIFF FOREGROUND
          else if(pixel_above == pixel_left && pixel_above != 0){
            an_image->SetPixel(i,j,pixel_above);
          }
        }
      }
    }  

    for(int i = 0; i < equiv_list.size();i++){
      equiv_list[i] = equiv_list[equiv_list[i]-50]; 
    }

    //SECOND PASS
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


void p3(Image *an_image, string database){
  conRegions(an_image);
  vector<int> num_of_objects;

  const int num_rows = an_image->num_rows();
  const int num_columns = an_image->num_columns();
  bool isin=false;

  for(int i = 1;i < num_rows;i++){
      for(int j = 1;j < num_columns;j++){

        if(an_image->GetPixel(i,j) != 0){
          for(int x = 0;x < num_of_objects.size();x++){
            if( an_image->GetPixel(i,j) == num_of_objects[x]){
              isin = true;
            }
          }
          if(!isin){
            num_of_objects.push_back(an_image->GetPixel(i,j));
          }
          isin = false;
        }
      }
  }

  vector<int> area_of_objects(num_of_objects.size());
    for(int i = 1;i < num_rows;i++){
        for(int j = 1;j < num_columns;j++){
          for(int x = 0;x < num_of_objects.size();x++){
            if(an_image->GetPixel(i,j) == num_of_objects[x]){
              area_of_objects[x] = area_of_objects[x]+1;
            }
          }
        }
  }

  vector<int> center_column(num_of_objects.size()),center_row(num_of_objects.size()),nmm_of_col(num_of_objects.size()),nmm_of_row((num_of_objects.size()));
    for(int i = 1;i < num_rows;i++){
      for(int j = 1;j < num_columns;j++){
        for(int x = 0;x < num_of_objects.size();x++){
          if(an_image->GetPixel(i,j) == num_of_objects[x]){
            center_column[x] = center_column[x] + j;
            nmm_of_col[x] += 1;
            center_row[x] = center_row[x] + i;
            nmm_of_row[x] += 1;
          }
        }
      }
    }

    for(int x = 0;x < num_of_objects.size();x++){
      center_column[x] = center_column[x]/nmm_of_col[x];
      center_row[x] = center_row[x]/nmm_of_row[x];
    }   

    for(int i = 0; i < num_of_objects.size();i++){
      an_image->SetPixel(center_row[i],center_column[i],255);
    }


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

    vector<double> theta1(num_of_objects.size());
    for(int x = 0;x < num_of_objects.size();x++){
      theta1[x] = atan2(b[x],a[x]-c[x])/2.0;
    }

    vector<double> e_min(num_of_objects.size());
    for(int x = 0;x < num_of_objects.size();x++){
      e_min[x] = a[x] * sin(theta1[x]) * sin(theta1[x]) - b[x] * sin(theta1[x]) * cos(theta1[x]) + c[x] * cos(theta1[x]) * cos(theta1[x]);
    }
    
    vector<double> theta2(num_of_objects.size());
    for(int x = 0;x < num_of_objects.size();x++){
      theta2[x] = theta2[x] + M_PI/2.0;
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
    //orentation is pi/2 - theta 
    vector<double> orientation(num_of_objects.size());
    for(int x = 0;x < num_of_objects.size();x++){
      orientation[x] = 90.0 - theta_degrees[x];
    }

    // for(int i = 0; i < num_of_objects.size();i++){
    //   cout << num_of_objects[i] << " ";
    //   cout << center_row[i] << " ";
    //   cout << center_column[i] << " ";
    //   cout << e_min[i] << " ";
    //   cout << area_of_objects[i] << " ";
    //   cout << roundedness[i] << " ";
    //   cout << orientation[i] << " ";
    //   cout << endl;
    // }

    
    vector<double> rho(num_of_objects.size());
    for(int i = 0;i < num_of_objects.size();i++){
      rho[i] = center_column[i]*cos(theta1[i]) - center_row[i]*sin(theta1[i]);
    }

    vector<int> newX(num_of_objects.size()), newY(num_of_objects.size());
    for(int i = 0;i < num_of_objects.size();i++){
      newX[i] = center_row[i] + 30;
      newY[i] = (newX[i] * sin(theta1[i]) + rho[i])/cos(theta1[i]);
     
    }

    for(int i = 0;i < num_of_objects.size();i++){
      DrawLine(center_row[i],center_column[i],newX[i],newY[i],255,an_image);
    }
    ofstream databased;
    databased.open(database);

    for(int i = 0; i < num_of_objects.size();i++){
        databased << i << " ";
        databased << center_row[i] << " ";
        databased << center_column[i] << " ";
        databased << e_min[i] << " ";
        databased << area_of_objects[i] << " ";
        databased << roundedness[i] << " ";
        databased << orientation[i] << " ";
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
    
    p3(&an_image, outdatabase);
    


    if (!WriteImage(output_file, an_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

}