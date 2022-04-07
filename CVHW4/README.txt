Kevin Ly

i. Which parts of your assignment were completed
    Completed parts s1, s2, s3, s4
    s1:
        threshold: 100
        s1.cc
            int getCenterXorY(ComputerVisionProjects::Image *an_image, bool x_or_y)   
            
            void findSphere(int threshold, Image *an_image,string out_put)
    
    s2:
        s2.cc  
            vector<double> calculate_light_source(Image *an_image, vector<double> sphere_properties) 
            
            void directionsAndIntensities(string input, Image *an_image,Image *an_image_2,Image *an_image_3,string out_put)
    
    s3:
        threshold: 100
        step: 10
        s3.cc  
            vector<double> invertMatrix(string input)

            void calculateSurfaceNormals(vector<double> inverted_matrix,Image *an_image,Image *an_image_2,Image *an_image_3,int step, int threshold)
    
    s4:
        threshold: 100  
        h4.cc
            vector<double> invertMatrix(string input)

            void surfaceAlbedo(vector<double> inverted_matrix,Image *an_image,Image *an_image_2,Image *an_image_3, int threshold)

ii. Any bugs that you have encountered


iii. Complete instructions of how to run your program(s).
    make clean
    make all

    ./s1 sphere0.pgm 100 radiusAndCenter.txt
	./s2 radiusAndCenter.txt sphere1.pgm sphere2.pgm sphere3.pgm outputDirections.txt
	./s3 outputDirections.txt object1.pgm object2.pgm object3.pgm 10 100 objectout.pgm
	./s4 outputDirections.txt object1.pgm object2.pgm object3.pgm 100 outaldeo.pgm


iv. The input file (if any) and the output files (if any).
    input:
        sphere1.pgm
        sphere2.pgm
        sphere3.pgm
        object1.pgm
        object2.pgm
        object3.pgm
        radiusAndCenter.txt
        outputDirections.txt
    output:
        radiusAndCenter.txt
        outputDirections.txt
        objectOut.pgm
        outAldeo.pgm