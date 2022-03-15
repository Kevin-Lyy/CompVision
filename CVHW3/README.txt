Kevin Ly

i. Which parts of your assignment were completed
    Completed parts h1, h2, h3, h4
    h1:
        h1.cc   
            void locateEdges(Image *an_image)
    
    h2:
        threshold: 100
        h2.cc  
            void grayToBin(int threshold, Image *an_image) 
            
    
    h3:
        h3.cc  
            void hough_transformation(Image *an_image, Image *hough_image)
    
    h4:
        threshold: 
        hough_complex_1.pgm: 130
        hough_simple_1.pgm: 190
        hough_simple_2.pgm: 180     
        h4.cc
            void connectedRegions(Image *an_image)

            vector<int> objectCount(Image *an_image)

            void drawDetectedLines(Image *an_image, Image *voting_array, Image *stored_votes, int threshold)

ii. Any bugs that you have encountered


iii. Complete instructions of how to run your program(s).
    make clean
    make all

    FOR SIMPLE HOUGH IMAGE 1
    ./h1 hough_simple_1.pgm output_h1.pgm
	./h2 output_h1.pgm 100 output_h2.pgm	
	./h3 output_h2.pgm output_h3.pgm output_h3_votingarray.pgm
	./h4 hough_simple_1.pgm output_h3_votingarray.pgm 130 output_h4.pgm

    FOR SIMPLE HOUGH IMAGE 2
    ./h1 hough_simple_2.pgm output_h1.pgm
	./h2 output_h1.pgm 100 output_h2.pgm	
	./h3 output_h2.pgm output_h3.pgm output_h3_votingarray.pgm
	./h4 hough_simple_2.pgm output_h3_votingarray.pgm 190 output_h4.pgm

    FOR COMPLEX HOUGH IMAGE 1
    ./h1 hough_complex_1.pgm output_h1.pgm
	./h2 output_h1.pgm 100 output_h2.pgm	
	./h3 output_h2.pgm output_h3.pgm output_h3_votingarray.pgm
	./h4 hough_complex_1.pgm output_h3_votingarray.pgm 180 output_h4.pgm

iv. The input file (if any) and the output files (if any).
    input:
        hough_simple_1.pgm
        hough_simple_2.pgm
        hough_complex_1.pgm
    output:
        output_h1.pgm
        output_h2.pgm
        output_h3.pgm
        output_h3_votingarray.pgm
        output_h4.pgm
