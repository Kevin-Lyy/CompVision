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

void hough_transformation(Image *an_image, Image *hough_image,string voting_array){
    const int num_rows = an_image->num_rows();
    const int num_columns = an_image->num_columns();
    int rho,theta;
    rho = an_image->num_columns();
    theta = an_image->num_rows();

    int size_of_rho = sqrt(pow(num_rows,2)+pow(num_columns,2));
    int size_of_theta = 360;

    hough_image->AllocateSpaceAndSetSize(size_of_rho,size_of_theta);

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

    double small_accumulator[size_of_rho/10][size_of_theta/10];
    ofstream open_voting_array;
    open_voting_array.open(voting_array);
    
    for(int i = 0;i < size_of_rho;i+=10){
        for(int j = 0;j < size_of_theta;j+=10){
            string output = "";
            int avg=0;
            for(int k = i;k < i+10;k++){   
                for(int l = j;l < j+10;l++){
                    avg += hough_image->GetPixel(i,j);
                }
            }
            avg = avg/100;
            small_accumulator[i/10][j/10] = avg;
        }
    }
    for(int i = 0; i < size_of_rho/10;i++){
        for(int j = 0; j < size_of_theta/10;j++){
            open_voting_array << i << " " << j << endl;
            open_voting_array << small_accumulator[i][j] << endl;
        }
    }
    /*
    for(int i = 0;i < size_of_rho;i+=20){
        for(int j = 0;j < size_of_theta;j+=40){
            string output = "";
            output = output + "Bucket: " + to_string(i/20) + " " + to_string(j/40) + "\n";
            //open_voting_array << "Bucket: " << i/20 << " " << j/40 << endl;
            for(int k = i;k < i+20;k++){
                int maxima = 0;
                for(int l = j;l < j+40;l++){
                    if (hough_image->GetPixel(k,l) > maxima){
                        maxima = hough_image->GetPixel(k,l);
                    }
                    output = output + to_string(k) + " " + to_string(l) + "\n";
                    output = output + to_string(hough_image->GetPixel(k,l)) + "\n";
                    output = output + to_string(k) + " " + to_string(l) + "\n";
                }
                if(maxima > 0){
                    output = output + to_string(maxima) + "\n";
                    open_voting_array << output;
                }
            }
        }
    }
    */
    open_voting_array.close();

    
}

int main(int argc, char **argv){
    if (argc!=4) {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 0;
    }
    const string input_file(argv[1]);
    const string output_file(argv[2]);
    const string output_voting_array(argv[3]);

    Image an_image;
    Image hough_image_;
    if (!ReadImage(input_file, &an_image)) {
        cout <<"Can't open file " << input_file << endl;
        return 0;
    }

    hough_transformation(&an_image, &hough_image_, output_voting_array);

    if (!WriteImage(output_file, hough_image_)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

}