Kevin Ly
threshold: 120

i. Which parts of your assignment were completed
    Completed parts p1, p2, p3, p4

    p1:
        p1.cc   
            void grayToBin(int threshold, Image *an_image)
    
    p2:
        p2.cc  
            void conRegions(Image *an_image)
    
    p3:
        p3.cc   
            void conRegions(Image *an_image)

            vector<int> objectCount(Image *an_image)

            vector<int> getAreaOfObjects(Image *an_image, vector<int> num_of_obj)

            vector<int> getCenterXorY(Image *an_image, vector<int> num_of_obj,bool x_or_y)

            void generateDatabase(Image *an_image, string database)
    
    p4:
        p4.cc
            vector<double> readDatabase(string database)

            void conRegions(Image *an_image)

            vector<int> objectCount(Image *an_image)

            vector<int> getAreaOfObjects(Image *an_image, vector<int> num_of_obj)

            vector<int> getCenterXorY(Image *an_image, vector<int> num_of_obj,bool x_or_y)

            void compareToImage(Image *an_image, vector<double> object_model_database)


ii. Any bugs that you have encountered
    N/A

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