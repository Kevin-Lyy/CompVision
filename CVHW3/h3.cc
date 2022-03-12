// KEVIN LY
#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>


using namespace std;
using namespace ComputerVisionProjects;

void hough_transformation(Image *an_image, Image *an_image_2){
    const int num_rows = an_image->num_rows();
    const int num_columns = an_image->num_columns();
    int rho,theta;
    rho = an_image->num_columns();
    theta = an_image->num_rows();

    int size_of_rho = sqrt(pow(num_rows,2)+pow(num_columns,2));
    int size_of_theta = 360;

    an_image_2->AllocateSpaceAndSetSize(size_of_rho,size_of_theta);

    double accumulator[size_of_rho][size_of_theta];
    for(int i = 0;i < size_of_rho;i++){
        for(int j = 0;j < size_of_theta;j++){
            accumulator[i][j] = 0;
        }
    }

    double temp_rho;
    for(int i = 0;i < num_rows;i++){
        for(int j = 0;j < num_columns;j++){
            if(an_image->GetPixel(i,j) != 0){
                for(double t = 0;t < 2*M_PI;t+=M_PI/180){
                    temp_rho = i*cos(t) + j*sin(t);
                    if(temp_rho >= 0 && temp_rho < size_of_rho){
                        accumulator[int(temp_rho)][int(t/(M_PI/180))] += 1;
                        // int temp = an_image_2->GetPixel(int(temp_rho),int(t/(M_PI/180)));
                        // temp++;
                        // an_image_2->SetPixel(int(temp_rho),int(t/(M_PI/180)),temp);
                    }
                }
            }
        }
    }

    for(int i = 0;i < size_of_rho;i++){
        for(int j = 0;j < size_of_theta;j++){
            an_image_2->SetPixel(i,j,accumulator[i][j]);
        }
    }

    double local_maxima[size_of_rho/10][size_of_theta/10];
    for(int i = 0; i < size_of_rho;i+=10){
        for(int j = 0;j < size_of_theta;j+=10){
            for(int k=i;k < i+10;k++){
                for(int l = j;l < j+10;l++){
                    
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
    // const string output_file_2(argv[3]);

    Image an_image;
    Image an_image_2;
    if (!ReadImage(input_file, &an_image)) {
        cout <<"Can't open file " << input_file << endl;
        return 0;
    }


    //H1
    hough_transformation(&an_image, &an_image_2);

    if (!WriteImage(output_file, an_image_2)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

}