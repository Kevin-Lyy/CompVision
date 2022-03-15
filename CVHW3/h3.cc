// KEVIN LY
// H3
// This file creates a hough image out of the edges of an image by going through the edges running a formula
// setting those new points into an image and returning it along with a voting array which demonstrates the 
// votes of a line on the image
#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;
using namespace ComputerVisionProjects;

// This is the function that creates the hough image out of an image with edges, given the x and y it determines the
// rho and theta of the hough image using rho = xcos(theta) + ysin(theta) 
void hough_transformation(Image *an_image, Image *hough_image){
    const int num_rows = an_image->num_rows();
    const int num_columns = an_image->num_columns();

    // creating an empty hough image
    int size_of_rho = sqrt(pow(num_rows,2)+pow(num_columns,2));
    int size_of_theta = 360;
    hough_image->AllocateSpaceAndSetSize(size_of_rho,size_of_theta);

    // accumlator array that will be iterated and create the hough image
    double accumulator[size_of_rho][size_of_theta];
    for(int i = 0;i < size_of_rho;i++){
        for(int j = 0;j < size_of_theta;j++){
            accumulator[i][j] = 0;
        }
    }

    // goes through given image with edges and determines the points on the hough array by calculating
    // rho with 0 <= theta < pi/180
    double temp_rho;
    for(int i = 0;i < num_rows;i++){
        for(int j = 0;j < num_columns;j++){
            if(an_image->GetPixel(i,j) != 0){
                for(double t = 0;t < 2*M_PI;t+=M_PI/180){
                    temp_rho = i*cos(t) + j*sin(t);
                    if(temp_rho >= 0 && temp_rho < size_of_rho){
                        accumulator[int(temp_rho)][int(t/(M_PI/180))] += 1;
                    }
                }
            }
        }
    }

    for(int i = 0;i < size_of_rho;i++){
        for(int j = 0;j < size_of_theta;j++){
            hough_image->SetPixel(i,j,accumulator[i][j]);
        }
    }

}

int main(int argc, char **argv){
    if (argc!=4) {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 0;
    }
    const string input_file(argv[1]);
    const string output_file(argv[2]);
    const string output_hough_array(argv[3]);

    Image an_image;
    Image hough_image_;

    if (!ReadImage(input_file, &an_image)) {
        cout <<"Can't open file " << input_file << endl;
        return 0;
    }

    //H3
    hough_transformation(&an_image, &hough_image_);

    if (!WriteImage(output_file, hough_image_)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

    if (!WriteImage(output_hough_array, hough_image_)){
        cout << "Can't write to file " << output_hough_array << endl;
        return 0;
    }
}