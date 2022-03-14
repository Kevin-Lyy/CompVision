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

void draw_lines(Image *an_image, Image *voting_array, int threshold){

}

int main(int argc, char **argv){
    if (argc!=5) {
        printf("Usage: %s file1 file2\n", argv[0]);
        return 0;
    }
    const string input_file(argv[1]);
    const string voting_array(argv[2]);
    const int threshold(stoi(argv[3]));
    const string output_file(argv[4]);

    Image an_image;
    Image hough_image;
    if (!ReadImage(input_file, &an_image)) {
        cout <<"Can't open file " << input_file << endl;
        return 0;
    }

    if (!ReadImage(voting_array, &hough_image)) {
        cout <<"Can't open file " << voting_array << endl;
        return 0;
    }


    draw_lines(&an_image, &hough_image, threshold);

    if (!WriteImage(output_file, an_image)){
        cout << "Can't write to file " << output_file << endl;
        return 0;
    }

}