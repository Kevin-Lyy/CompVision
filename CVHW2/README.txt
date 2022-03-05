Kevin Ly
threshold: 120

i. Which parts of your assignment were completed
    Completed parts p1, p2, p3, p4
    p1:
        p1.cc   
            void grayToBin(int threshold, Image *an_image)
    
    p2:
        p2.cc  
            vector<int> objectCount(Image *an_image)

            void connectedRegions(Image *an_image)
    
    p3:
        functions.h 
        functions.cc 
            vector<int> objectCount(Image *an_image)

            vector<int> getAreaOfObjects(Image *an_image, vector<int> num_of_obj)

            vector<int> getCenterXorY(Image *an_image, vector<int> num_of_obj,bool x_or_y) 
        p3.cc  
            void generateDatabase(Image *an_image, string database)
    
    p4:
        functions.h
        functions.cc  
            vector<int> objectCount(Image *an_image)

            vector<int> getAreaOfObjects(Image *an_image, vector<int> num_of_obj)

            vector<int> getCenterXorY(Image *an_image, vector<int> num_of_obj,bool x_or_y)
        p4.cc
            vector<double> readDatabase(string database)

            void compareToImage(Image *an_image, vector<double> object_model_database)


ii. Any bugs that you have encountered
    in p4 when writing the image recognition, my program could not distinguse a fork from a spoon, I used
    roundedness becuase it was the only attribute that was resistant to different orentations but the fork's and
    spoon's roundedness were too close in value

iii. Complete instructions of how to run your program(s).
    make clean
    make all

    ./p1 many_objects_2.pgm objects_output_1.pgm
	./p2 many_objects_2.pgm objects_output_2.pgm
	./p3 many_objects_2.pgm database.txt objects_output_3.pgm 
	./p4 many_objects_1.pgm database.txt objects_output_4.pgm

iv. The input file (if any) and the output files (if any).
    inpuut:
        many_objects_2.pgm
        many_objects_1.pgm
    output:
        objects_output_1.pgm
        objects_output_2.pgm
        objects_output_3.pgm
        objects_output_4.pgm
        database.txt