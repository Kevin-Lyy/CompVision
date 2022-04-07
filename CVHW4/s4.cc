// KEVIN LY
#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
using namespace ComputerVisionProjects;

vector<double> invertMatrix(string input){
    vector<double> output_matrix(9);
    ifstream matrix; 
    matrix.open(input);
    string line = "";
    vector<double> matrix_vector;
    while(getline(matrix,line)){
        stringstream temp_line(line);
        double parameter;
        while(temp_line >> parameter){
            matrix_vector.push_back(parameter);
        }
    } 

    output_matrix[0] = matrix_vector[4]* matrix_vector[8] - matrix_vector[5]*matrix_vector[7];
    output_matrix[1] = -1*(matrix_vector[3]* matrix_vector[8] - matrix_vector[5]*matrix_vector[6]);
    output_matrix[2] = matrix_vector[3]* matrix_vector[7] - matrix_vector[4]*matrix_vector[6];
    output_matrix[3] = -1*(matrix_vector[1]* matrix_vector[8] - matrix_vector[2]*matrix_vector[7]);
    output_matrix[4] = matrix_vector[0]* matrix_vector[8] - matrix_vector[2]*matrix_vector[6];
    output_matrix[5] = -1*(matrix_vector[0]* matrix_vector[7] - matrix_vector[1]*matrix_vector[6]);
    output_matrix[6] = matrix_vector[1]* matrix_vector[5] - matrix_vector[2]*matrix_vector[4];
    output_matrix[7] = -1*(matrix_vector[0]* matrix_vector[5] - matrix_vector[2]*matrix_vector[3]);
    output_matrix[8] = matrix_vector[0]* matrix_vector[4] - matrix_vector[1]*matrix_vector[3];
    double determinant = matrix_vector[0]*output_matrix[0] - matrix_vector[1]*-1*output_matrix[1] + matrix_vector[2]*output_matrix[2];
    output_matrix[1] = -1*(matrix_vector[1]* matrix_vector[8] - matrix_vector[2]*matrix_vector[7]);
    output_matrix[3] = -1*(matrix_vector[3]* matrix_vector[8] - matrix_vector[5]*matrix_vector[6]);
    output_matrix[2] = matrix_vector[1]* matrix_vector[5] - matrix_vector[2]*matrix_vector[4];
    output_matrix[6] = matrix_vector[3]* matrix_vector[7] - matrix_vector[4]*matrix_vector[6];
    output_matrix[5] = -1*(matrix_vector[0]* matrix_vector[5] - matrix_vector[2]*matrix_vector[3]);
    output_matrix[7] = -1*(matrix_vector[0]* matrix_vector[7] - matrix_vector[1]*matrix_vector[6]);

    for(int i = 0;i < 9;i++){
        output_matrix[i] = output_matrix[i]/determinant;
    }
    return output_matrix;

}

void surfaceAlbedo(vector<double> inverted_matrix,Image *an_image,Image *an_image_2,Image *an_image_3, int threshold){
    vector<double> normal_image_1, normal_image_2, normal_image_3;
    double normal;
    const int num_rows = an_image->num_rows();
    const int num_columns = an_image->num_columns();
    for(int i = 0;i < num_rows;i++){
        for(int j = 0;j < num_columns;j++){
            int pixel1 = an_image->GetPixel(i,j),pixel2 = an_image_2->GetPixel(i,j), pixel3 =  an_image_3->GetPixel(i,j);
            normal = pixel1*inverted_matrix[0] + pixel2*inverted_matrix[1] + pixel3*inverted_matrix[2];
            normal_image_1.push_back(normal);
            normal = pixel1*inverted_matrix[3] + pixel2*inverted_matrix[4] + pixel3*inverted_matrix[5];
            normal_image_2.push_back(normal);
            normal = pixel1*inverted_matrix[6] + pixel2*inverted_matrix[7] + pixel3*inverted_matrix[8];
            normal_image_3.push_back(normal);
       
        }
    }

    vector<double> albedo(normal_image_1.size());
    double max_albedo = 0;
    for(int i = 0;i < normal_image_1.size();i++){
        double temp = pow(normal_image_1[i],2) + pow(normal_image_2[i],2) + pow(normal_image_3[i],2);
        albedo[i] = pow(temp,0.5);
        if (albedo[i] > max_albedo){
            max_albedo = albedo[i];
        }
    }
    max_albedo = max_albedo;
    int counter = 0;
    for(int i = 0;i < num_rows;i++){
        for(int j = 0;j < num_columns;j++){
            if(an_image->GetPixel(i,j) > threshold && an_image_2->GetPixel(i,j) > threshold && an_image_3->GetPixel(i,j) > threshold)
                an_image->SetPixel(i,j,255*albedo[counter]/max_albedo);
            else
                an_image->SetPixel(i,j,0);
            counter++;
            
        }
    }

}



int main(int argc, char **argv){
    if (argc!=7) {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 0;
    }
    const string input_direction(argv[1]);
    const string input_file1(argv[2]);
    const string input_file2(argv[3]);
    const string input_file3(argv[4]);
    const int threshold(stoi(argv[5]));
    const string output_file(argv[6]);
     

    Image an_image_1,an_image_2,an_image_3;

    if (!ReadImage(input_file1, &an_image_1)) {
        cout <<"Can't open file " << input_file1 << endl;
        return 0;
    }
    if (!ReadImage(input_file2, &an_image_2)) {
        cout <<"Can't open file " << input_file2 << endl;
        return 0;
    }
    if (!ReadImage(input_file3, &an_image_3)) {
        cout <<"Can't open file " << input_file3 << endl;
        return 0;
    }

    //S4
    vector<double> invert_matrix = invertMatrix(input_direction);
    surfaceAlbedo(invert_matrix,&an_image_1,&an_image_2,&an_image_3,threshold);

    if (!WriteImage(output_file, an_image_1)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

}