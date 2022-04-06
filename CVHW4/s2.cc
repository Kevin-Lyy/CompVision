// KEVIN LY
#include "image.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;
using namespace ComputerVisionProjects;

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
    //findSphere(threshold_,&an_image,output_file);



}