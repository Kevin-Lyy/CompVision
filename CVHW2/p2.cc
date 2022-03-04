//KEVIN LY
#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

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
    conRegions(&an_image);



    if (!WriteImage(output_file, an_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

}