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
    //ad - bc
    //0 1 2
    //3 4 5
    //6 7 8
    // 1 <-> 3
    // 2 <-> 6
    // 5 <-> 7

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
        cout <<output_matrix[i] << " ";
        if(i==2 || i == 5){
            cout << "\n";
        }
    }
    return output_matrix;

}

void calculateSurfaceNormals(vector<double> inverted_matrix,Image *an_image,Image *an_image_2,Image *an_image_3,int step, int threshold){
    const int num_rows = an_image->num_rows();
    const int num_columns = an_image->num_columns();
    for(int i = 0;i < num_rows;i+=step){
        for(int j = 0;j < num_columns;j+=step){
            
        }
    }


}


int main(int argc, char **argv){
    if (argc!=8) {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 0;
    }
    const string input_direction(argv[1]);
    const string input_file1(argv[2]);
    const string input_file2(argv[3]);
    const string input_file3(argv[4]);
    const int step(stoi(argv[5]));
    const int threshold(stoi(argv[6]));
    const string output_file(argv[7]);
     

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

    //S3
    vector<double> invert_matrix = invertMatrix(input_direction);
    calculateSurfaceNormals(invert_matrix,&an_image_1,&an_image_2,&an_image_3,step,threshold);

    if (!WriteImage(output_file, an_image_1)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

}