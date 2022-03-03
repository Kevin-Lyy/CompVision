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
  vector<int> equivList,changedList;
  equivList.push_back(50);
  changedList.push_back(50);
  int top,left,place=0;
    for(int i = 1;i < num_rows;i++){
      for(int j = 1;j < num_columns;j++){
        if(an_image->GetPixel(i,j) == 49){
          top = an_image->GetPixel(i-1,j);
          left = an_image->GetPixel(i,j-1);

          //CHECK TO THE LEFT AND RIGHT IF THEY ARE BACKGROUND 
          if(top == 0 && left == 0){
            an_image->SetPixel(i,j,equivList[place]);
            equivList.push_back(equivList[place]+1);
            place++;
          }
          //IF LEFT AND TOP ARE DIFF VALUES
          else if(top != left){
            //TOP IS BACKGROUND
            if(top == 0 && left != 0){
              an_image->SetPixel(i,j,left);
            }
            // LEFT IS BACKGROUND
            else if(left == 0 && top !=0 ){
              an_image->SetPixel(i,j,top);
            }
            else{
              if(left < top){
                an_image->SetPixel(i,j,left);
                for(int x = 0; x <equivList.size();x++ ){
                  if(top == equivList[x]){
                    equivList[x] = left;
                  }
                }
              }
              else if (left > top){
                an_image->SetPixel(i,j,top);
                for(int x = 0; x <equivList.size();x++ ){
                  if(left == equivList[x]){
                    equivList[x] = top;
                  }
                }
              }
            }
          }
          //TOP AND LEFT ARE THE SAME AND ARE NOT BACKROUND BUT DIFF FOREGROUND
          else if(top == left && top != 0){
            an_image->SetPixel(i,j,top);
          }
        }
      }
    }  

    for(int i = 0; i < equivList.size();i++){
      equivList[i] = equivList[equivList[i]-50]; 
    }

    //SECOND PASS
    for(int i = 1;i < num_rows;i++){
        for(int j = 1;j < num_columns;j++){
          for(int x = 0;x < equivList.size();x++){
            if(an_image->GetPixel(i,j) ==x+50 ){
              an_image->SetPixel(i,j,equivList[x]);
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