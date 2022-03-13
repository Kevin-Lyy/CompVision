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
                        // int temp = hough_image->GetPixel(int(temp_rho),int(t/(M_PI/180)));
                        // temp++;
                        // hough_image->SetPixel(int(temp_rho),int(t/(M_PI/180)),temp);
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

    int rho_bucket = size_of_rho/10, theta_bucket = size_of_theta/10;
    int x_coord_bucket[rho_bucket][theta_bucket],y_coord_bucket[rho_bucket][theta_bucket];
    for(int i = 0; i < size_of_rho;i+=10){
        for(int j = 0;j < size_of_theta;j+=10){
            for(int k=i;k < i+10;k++){
                int maxima = 0;
                for(int l=j;l < j+10;l++){
                    if (hough_image->GetPixel(k,l) > maxima){
                        maxima = hough_image->GetPixel(k,l);
                        x_coord_bucket[i/10][j/10] = k;
                        y_coord_bucket[i/10][j/10] = l;
                    }
                }
            }
        }
    }
    vector<int> local_maxima;
    for(int i = 0; i < rho_bucket;i++){
        for(int j = 0;j < theta_bucket;j++){
            int x_bucket = x_coord_bucket[i][j], y_bucket = y_coord_bucket[i][j];
            if(x_coord_bucket[i][j] != 0 && y_coord_bucket[i][j] != 0){
                int left_pixel = hough_image->GetPixel(x_bucket,y_coord_bucket[i][j-1]); 
                int right_pixel = hough_image->GetPixel(x_bucket,y_coord_bucket[i][j+1]);
                int this_pixel = hough_image->GetPixel(x_bucket,y_bucket);

                if(j == 0){
                    if( this_pixel > right_pixel ){
                        local_maxima.push_back(x_bucket);
                        local_maxima.push_back(y_bucket);
                    }

                }
                else if(j == theta_bucket-1){
                    if(this_pixel > left_pixel ){
                        local_maxima.push_back(x_bucket);
                        local_maxima.push_back(y_bucket);
                    }

                }
                else{
                    if(this_pixel > right_pixel && this_pixel > left_pixel){
                        local_maxima.push_back(x_bucket);
                        local_maxima.push_back(y_bucket);
                    }
                }
            }
            // cout << "(" << x_coord_bucket[i][j] << "," << y_coord_bucket[i][j] << ") ";
        }
    }

    for(int i = 0;i < local_maxima.size();i+=2){
        cout << local_maxima[i] << ","<<local_maxima[i+1] <<" ";
    }




    ofstream open_voting_array;
    open_voting_array.open(voting_array);

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


    //H1
    hough_transformation(&an_image, &hough_image_, output_voting_array);

    if (!WriteImage(output_file, hough_image_)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

}