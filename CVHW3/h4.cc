// KEVIN LY
#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
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

vector<int> objectCount(Image *an_image){
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

void draw_lines(Image *an_image, Image *voting_array, Image *stored_votes, int threshold){
    const int num_rows = an_image->num_rows();
    const int num_columns = an_image->num_columns();

    const int hough_rows = voting_array->num_rows();
    const int hough_columns = voting_array->num_columns();

    for(int i = 0;i < hough_rows;i++){
        for(int j = 0;j < hough_columns;j++){
            if(voting_array->GetPixel(i,j) < threshold)
                voting_array->SetPixel(i,j,0);
            else
                voting_array->SetPixel(i,j,255);
        }
    }

    connectedRegions(voting_array);

    vector<int> num_of_objects;
    num_of_objects = objectCount(voting_array);
    vector<int> center_column(num_of_objects.size()),center_row(num_of_objects.size());
    vector<int> centervotearea(num_of_objects.size());

    for(int i = 0;i < hough_rows;i++){
        for(int j = 0;j < hough_columns;j++){
            for(int x = 0;x < num_of_objects.size();x++){
                if(voting_array->GetPixel(i,j) == num_of_objects[x]){
                    center_row[x] += i*stored_votes->GetPixel(i,j);
                    center_column[x] += j*stored_votes->GetPixel(i,j);
                    centervotearea[x] += stored_votes->GetPixel(i,j);
                }
            }
        }
    }

    for(int i = 0;i <num_of_objects.size();i++){
        center_row[i] = center_row[i]/centervotearea[i];
        center_column[i] = center_column[i]/centervotearea[i];
    }

    for(int i = 0;i < hough_rows;i++){
        for(int j = 0;j < hough_columns;j++){
            for(int x = 0;x < num_of_objects.size();x++){
                if(i == center_row[x] && j == center_column[x]){
                    voting_array->SetPixel(i,j,255);
                }
            }
        }
    }
  
    //rho = row * 5
    //theta = col * 5 * (M_PI/180)

    for(int i = 0;i <num_of_objects.size();i++){
      center_row[i] = center_row[i] * 5;
      center_column[i] = center_column[i] * 5 * (M_PI/180);

    }

    
}

int main(int argc, char **argv){
    if (argc!=5) {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 0;
    }
    const string input_file(argv[1]);
    const string voting_array(argv[2]);
    const int threshold(stoi(argv[3]));
    const string output_file(argv[4]);

    Image an_image;
    Image hough_image;
    Image stored_votes;
    if (!ReadImage(input_file, &an_image)) {
        cout <<"Can't open file " << input_file << endl;
        return 0;
    }

    if (!ReadImage(voting_array, &hough_image)) {
        cout <<"Can't open file " << voting_array << endl;
        return 0;
    }

    if (!ReadImage(voting_array, &stored_votes)) {
        cout <<"Can't open file " << voting_array << endl;
        return 0;
    }


    draw_lines(&an_image, &hough_image,&stored_votes, threshold);

    if (!WriteImage(output_file, hough_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

}