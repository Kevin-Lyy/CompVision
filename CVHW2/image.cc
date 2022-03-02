// Class for representing a 2D gray-scale image,
// with support for reading/writing pgm images.
// To be used in Computer Vision class.

#include "image.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

namespace ComputerVisionProjects {

Image::Image(const Image &an_image){
  AllocateSpaceAndSetSize(an_image.num_rows(), an_image.num_columns());
  SetNumberGrayLevels(an_image.num_gray_levels());

  for (size_t i = 0; i < num_rows(); ++i)
    for (size_t j = 0; j < num_columns(); ++j){
      SetPixel(i,j, an_image.GetPixel(i,j));
    }
}

Image::~Image(){
  DeallocateSpace();
}

void Image::AllocateSpaceAndSetSize(size_t num_rows, size_t num_columns) {
  if (pixels_ != nullptr) DeallocateSpace();
  pixels_ = new int*[num_rows];
  for (size_t i = 0; i < num_rows; ++i)
    pixels_[i] = new int[num_columns];

  num_rows_ = num_rows;
  num_columns_ = num_columns;
}

void Image::DeallocateSpace() {
  for (size_t i = 0; i < num_rows_; i++)
    delete pixels_[i];
  delete pixels_;
  pixels_ = nullptr;
  num_rows_ = 0;
  num_columns_ = 0;
}

void grayToBin(int threshold, Image *an_image) {
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
          a[x] = a[x] + pow((i-centerColumn[x]),2);
          b[x] = b[x] + (i-centerColumn[x])*(j-centerRow[x]);
          c[x] = c[x] + pow((j-centerRow[x]),2);
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
    e_min[x] = a[x] * sin(theta1[x]) * sin(theta1[x]) - b[x]*sin(theta1[x])*cos(theta1[x]) + c[x]*cos(theta1[x])*cos(theta1[x]);
  }
  
  vector<double> theta2(numObjects.size());
  for(int x = 0;x < numObjects.size();x++){
    theta2[x] = theta2[x] + M_PI/2.0;
  }

  vector<double> e_max(numObjects.size());
  for(int x = 0;x < numObjects.size();x++){
    e_max[x] = a[x] * sin(theta2[x]) * sin(theta2[x]) - b[x]*sin(theta2[x])*cos(theta2[x]) + c[x]*cos(theta2[x])*cos(theta2[x]);
  }

  vector<double> roundedness(numObjects.size());
  for(int x = 0;x < numObjects.size();x++){
    roundedness[x] = e_min[x]/e_max[x];
  }

  vector<double> theta_degrees(numObjects.size());
  for(int x = 0;x < numObjects.size();x++){
    theta_degrees[x] = 180.0* theta1[x]/M_PI;
  }

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
  for(int i = 1;i < num_rows;i++){
    for(int j = 1;j < num_columns;j++){
      for(int x = 0;x < numObjects.size();x++){
        if(an_image->GetPixel(i,j) == numObjects[x]){
          if( ((i-centerColumn[x]) * sin(theta1[x]) - (j-centerRow[x]) * cos(theta1[x])) == 0){
            an_image->SetPixel(i,j,255);
          }
        }
      }
    }
  }
//orentation is pi/2 - theta 
}

bool ReadImage(const string &filename, Image *an_image) {  
  if (an_image == nullptr) abort();
  FILE *input = fopen(filename.c_str(),"rb");
  if (input == 0) {
    cout << "ReadImage: Cannot open file" << endl;
    return false;
  }
  
  // Check for the right "magic number".
  char line[1024];
  if (fread(line, 1, 3, input) != 3 || strncmp(line,"P5\n",3)) {
    fclose(input);
    cout << "ReadImage: Expected .pgm file" << endl;
    return false;
  }
  
  // Skip comments.
  do
    fgets(line, sizeof line, input);
  while(*line == '#');
  
  // Read the width and height.
  int num_columns,num_rows;
  sscanf(line,"%d %d\n", &num_columns, &num_rows);
  an_image->AllocateSpaceAndSetSize(num_rows, num_columns);
  

  // Read # of gray levels.
  fgets(line, sizeof line, input);
  int levels;
  sscanf(line,"%d\n", &levels);
  an_image->SetNumberGrayLevels(levels);

  // read pixel row by row.
  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0;j < num_columns; ++j) {
      const int byte=fgetc(input);
      if (byte == EOF) {
        fclose(input);
        cout << "ReadImage: short file" << endl;
        return false;
      }
      an_image->SetPixel(i, j, byte);
    }
  }
  
  fclose(input);
  return true; 
}


bool WriteImage(const string &filename, const Image &an_image) {  
  FILE *output = fopen(filename.c_str(), "w");
  if (output == 0) {
    cout << "WriteImage: cannot open file" << endl;
    return false;
  }
  const int num_rows = an_image.num_rows();
  const int num_columns = an_image.num_columns();
  const int colors = an_image.num_gray_levels();

  // Write the header.
  fprintf(output, "P5\n"); // Magic number.
  fprintf(output, "#\n");  // Empty comment.
  fprintf(output, "%d %d\n%03d\n", num_columns, num_rows, colors);

  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < num_columns; ++j) {
      const int byte = an_image.GetPixel(i , j);
      if (fputc(byte,output) == EOF) {
	    fclose(output);
            cout << "WriteImage: could not write" << endl;
	    return false;
      }
    }
  }

  fclose(output);
  return true; 
}

// Implements the Bresenham's incremental midpoint algorithm;
// (adapted from J.D.Foley, A. van Dam, S.K.Feiner, J.F.Hughes
// "Computer Graphics. Principles and practice", 
// 2nd ed., 1990, section 3.2.2);  
void DrawLine(int x0, int y0, int x1, int y1, int color,
	      Image *an_image) {  
  if (an_image == nullptr) abort();

#ifdef SWAP
#undef SWAP
#endif
#define SWAP(a,b) {a^=b; b^=a; a^=b;}

  const int DIR_X = 0;
  const int DIR_Y = 1;
  
  // Increments: East, North-East, South, South-East, North.
  int incrE,
    incrNE,
    incrS,
    incrSE,
    incrN;     
  int d;         /* the D */
  int x,y;       /* running coordinates */
  int mpCase;    /* midpoint algorithm's case */
  int done;      /* set to 1 when done */
  
  int xmin = x0;
  int xmax = x1;
  int ymin = y0;
  int ymax = y1;
  
  int dx = xmax - xmin;
  int dy = ymax - ymin;
  int dir;

  if (dx * dx > dy * dy) {  // Horizontal scan.
    dir=DIR_X;
    if (xmax < xmin) {
      SWAP(xmin, xmax);
      SWAP(ymin , ymax);
    } 
    dx = xmax - xmin;
    dy = ymax - ymin;

    if (dy >= 0) {
      mpCase = 1;
      d = 2 * dy - dx;      
    } else {
      mpCase = 2;
      d = 2 * dy + dx;      
    }

    incrNE = 2 * (dy - dx);
    incrE = 2 * dy;
    incrSE = 2 * (dy + dx);
  } else {// vertical scan.
    dir = DIR_Y;
    if (ymax < ymin) {
      SWAP(xmin, xmax);
      SWAP(ymin, ymax);
    }
    dx = xmax - xmin;
    dy = ymax-ymin;    

    if (dx >=0 ) {
      mpCase = 1;
      d = 2 * dx - dy;      
    } else {
      mpCase = 2;
      d = 2 * dx + dy;      
    }

    incrNE = 2 * (dx - dy);
    incrE = 2 * dx;
    incrSE = 2 * (dx + dy);
  }
  
  /// Start the scan.
  x = xmin;
  y = ymin;
  done = 0;

  while (!done) {
    an_image->SetPixel(x,y,color);
  
    // Move to the next point.
    switch(dir) {
    case DIR_X: 
      if (x < xmax) {
	      switch(mpCase) {
	      case 1:
		if (d <= 0) {
		  d += incrE;  
		  x++;
		} else {
		  d += incrNE; 
		  x++; 
		  y++;
		}
		break;
  
            case 2:
              if (d <= 0) {
                d += incrSE; 
		x++; 
		y--;
              } else {
                d += incrE;  
		x++;
              }
	      break;
	      } 
      } else {
	done=1;
      }     
      break;

    case DIR_Y: 
        if (y < ymax) {
          switch(mpCase) {
	  case 1:
	    if (d <= 0) {
	      d += incrE;  
	      y++;
	    } else {
	      d += incrNE; 
	      y++; 
	      x++;
	    }
            break;
  
	  case 2:
	    if (d <= 0) {
                d += incrSE; 
		y++; 
		x--;
              } else {
                d += incrE;  
		y++;
	    }
            break;
	  } // mpCase
        } // y < ymin 
        else {
	  done=1;
	}
	break;    
    }
  }
}

}  // namespace ComputerVisionProjects







