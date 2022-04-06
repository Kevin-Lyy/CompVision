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

vector<double> calculate_light_source(Image *an_image, vector<double> sphere_properties){
    vector<double> output;
    int brightestX=0,brightestY=0,brightest_pixel;
    const int num_rows = an_image->num_rows();
    const int num_columns = an_image->num_columns();
    for(int i = 1;i < num_rows;i++){
        for(int j = 1;j < num_columns;j++){
            if(an_image->GetPixel(i,j) > an_image->GetPixel(brightestX,brightestY)){
                brightestX = i;
                brightestY = j;
                brightest_pixel = an_image->GetPixel(i,j);
            }
        }
    }


    double x_component = brightestX - sphere_properties[0];
    double y_component = brightestY - sphere_properties[1];
    double z_input = pow(sphere_properties[2],2) - pow(x_component,2) - pow(y_component,2);

    double z_component = pow( z_input,0.5);

    double direction_input = pow(sphere_properties[2],2) + pow(x_component,2) + pow(y_component,2);
    double directional_magnitude = pow(direction_input ,0.5);

    double scaled_x =  x_component * brightest_pixel/directional_magnitude;
    double scaled_y =  y_component * brightest_pixel/directional_magnitude;
    double scaled_z =  z_component * brightest_pixel/directional_magnitude;
    output.push_back(scaled_x);
    output.push_back(scaled_y);
    output.push_back(scaled_z);
    //cout << scaled_x << " " << scaled_y << " " <<scaled_z << endl;
    return output;
}

void directionsAndIntensities(string input, Image *an_image,Image *an_image_2,Image *an_image_3,string out_put){
    ifstream open_parameters; 
    open_parameters.open(input);
    string line = "";
    vector<double> parameters;
    while(getline(open_parameters,line)){
        stringstream temp_line(line);
        double parameter;
        while(temp_line >> parameter){
            parameters.push_back(parameter);
        }
    } 
    open_parameters.close();
    ofstream output_file;
    output_file.open(out_put);
    vector<double> write_to_file;
    write_to_file = calculate_light_source(an_image,parameters);
    output_file << write_to_file[0] << " " << write_to_file[1] << " " << write_to_file[2] << "\n";
    write_to_file = calculate_light_source(an_image_2,parameters);
    output_file << write_to_file[0] << " " << write_to_file[1] << " " << write_to_file[2] << "\n";
    write_to_file = calculate_light_source(an_image_3,parameters);
    output_file << write_to_file[0] << " " << write_to_file[1] << " " << write_to_file[2];

    output_file.close();

}

int main(int argc, char **argv){
    if (argc!=6) {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 0;
    }
    const string input_param(argv[1]);
    const string input_file1(argv[2]);
    const string input_file2(argv[3]);
    const string input_file3(argv[4]);
    const string output_file(argv[5]);

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

    //S2
    directionsAndIntensities(input_param,&an_image_1,&an_image_2,&an_image_3,output_file);


}