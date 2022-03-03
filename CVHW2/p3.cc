#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

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

void p3(Image *an_image){
  conRegions(an_image);
  vector<int> numObjects;

  const int num_rows = an_image->num_rows();
  const int num_columns = an_image->num_columns();
  bool isin=false;

  for(int i = 1;i < num_rows;i++){
      for(int j = 1;j < num_columns;j++){

        if(an_image->GetPixel(i,j) != 0){
          for(int x = 0;x < numObjects.size();x++){
            if( an_image->GetPixel(i,j) == numObjects[x]){
              isin = true;
            }
          }
          if(!isin){
            numObjects.push_back(an_image->GetPixel(i,j));
          }
          isin = false;
        }
      }
  }

  vector<int> areaOfObjects(numObjects.size());
    for(int i = 1;i < num_rows;i++){
        for(int j = 1;j < num_columns;j++){
          for(int x = 0;x < numObjects.size();x++){
            if(an_image->GetPixel(i,j) == numObjects[x]){
              areaOfObjects[x] = areaOfObjects[x]+1;
            }
          }
        }
  }

  vector<int> centerColumn(numObjects.size()),centerRow(numObjects.size()),numCol(numObjects.size()),numRow((numObjects.size()));
    for(int i = 1;i < num_rows;i++){
      for(int j = 1;j < num_columns;j++){
        for(int x = 0;x < numObjects.size();x++){
          if(an_image->GetPixel(i,j) == numObjects[x]){
            centerColumn[x] = centerColumn[x] + j;
            numCol[x] += 1;
            centerRow[x] = centerRow[x] + i;
            numRow[x] += 1;
          }
        }
      }
    }

    for(int x = 0;x < numObjects.size();x++){
      centerColumn[x] = centerColumn[x]/numCol[x];
      centerRow[x] = centerRow[x]/numRow[x];
    }   

    for(int i = 0; i < numObjects.size();i++){
      //cout << "center of item: " << numObjects[i] << " is (" << centerColumn[i] << "," << centerRow[i]<<")" << endl ;
      an_image->SetPixel(centerRow[i],centerColumn[i],255);
    }


    vector<int> a(numObjects.size()), b(numObjects.size()), c(numObjects.size()) ;
    for(int i = 1;i < num_rows;i++){
      for(int j = 1;j < num_columns;j++){
        for(int x = 0;x < numObjects.size();x++){
          if(an_image->GetPixel(i,j) == numObjects[x]){
            a[x] = a[x] + pow((i-centerRow[x]),2);
            b[x] = b[x] + (i-centerRow[x])*(j-centerColumn[x]);
            c[x] = c[x] + pow((j-centerColumn[x]),2);
          }
        }
      }
    }
    for(int i = 0;i < b.size();i++){
      b[i] = 2*b[i];
    }

    vector<double> theta1(numObjects.size());
    for(int x = 0;x < numObjects.size();x++){
      theta1[x] = atan2(b[x],a[x]-c[x])/2.0;
    }

    vector<double> e_min(numObjects.size());
    for(int x = 0;x < numObjects.size();x++){
      e_min[x] = a[x] * sin(theta1[x]) * sin(theta1[x]) - b[x] * sin(theta1[x]) * cos(theta1[x]) + c[x] * cos(theta1[x]) * cos(theta1[x]);
    }
    
    vector<double> theta2(numObjects.size());
    for(int x = 0;x < numObjects.size();x++){
      theta2[x] = theta2[x] + M_PI/2.0;
    }

    vector<double> e_max(numObjects.size());
    for(int x = 0;x < numObjects.size();x++){
      e_max[x] = a[x] * sin(theta2[x]) * sin(theta2[x]) - b[x] * sin(theta2[x]) * cos(theta2[x]) + c[x] * cos(theta2[x]) * cos(theta2[x]);
    }

    vector<double> roundedness(numObjects.size());
    for(int x = 0;x < numObjects.size();x++){
      roundedness[x] = e_min[x]/e_max[x];
    }

    vector<double> theta_degrees(numObjects.size());
    for(int x = 0;x < numObjects.size();x++){
      theta_degrees[x] = 180.0 * theta1[x]/M_PI;
    }
    //orentation is pi/2 - theta 
    vector<double> orientation(numObjects.size());
    for(int x = 0;x < numObjects.size();x++){
      orientation[x] = 90.0 - theta_degrees[x];
    }

    for(int i = 0; i < numObjects.size();i++){
      cout << numObjects[i] << " ";
      cout << centerRow[i] << " ";
      cout << centerColumn[i] << " ";
      cout << e_min[i] << " ";
      cout << areaOfObjects[i] << " ";
      cout << roundedness[i] << " ";
      cout << orientation[i] << " ";
      cout << endl;
    }

    //equation of the line 
    //xsin(0) - ycos(0) + p  = 0 
    //use center x y to find p 
    
    vector<double> rho(numObjects.size());
    for(int i = 0;i < numObjects.size();i++){
      rho[i] = centerColumn[i]*cos(theta1[i]) - centerRow[i]*sin(theta1[i]);
      cout << rho[i] << endl;
    }

    vector<int> newX(numObjects.size()), newY(numObjects.size());
    for(int i = 0;i < numObjects.size();i++){
      newX[i] = centerRow[i] + 30;
      newY[i] = (newX[i] * sin(theta1[i]) + rho[i])/cos(theta1[i]);
     
      // cout << newX[i] << endl;
      // cout << newY[i] << endl;
    }

    for(int i = 0;i < numObjects.size();i++){
      DrawLine(centerRow[i],centerColumn[i],newX[i],newY[i],255,an_image);
    }
    //(int x0, int y0, int x1, int y1, int color,Image *an_image)

    for(int i = 0;i < numObjects.size();i++){
      cout << theta1[i] << endl;
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

    //P3
    p3(&an_image);


    if (!WriteImage(output_file, an_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

}