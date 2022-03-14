##########################################
##
## Makefile for Assignment No. 2
## LINUX Compilation
## 
##########################################

# FLAGS
C++FLAG = -g -std=c++11

MATH_LIBS = -lm

EXEC_DIR=.

.cc.o:
	g++ $(C++FLAG) $(INCLUDES) -c $< -o $@

# Including
INCLUDES= -I.

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib 

# H1
ALL_OBJ1 = image.o h1.o 
PROGRAM_1 = h1
$(PROGRAM_1): $(ALL_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ1) $(INCLUDES) $(LIBS_ALL)

# H2
ALL_OBJ2 = image.o h2.o
PROGRAM_2 = h2
$(PROGRAM_2): $(ALL_OBJ2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ2) $(INCLUDES) $(LIBS_ALL)

# H3
ALL_OBJ3 = image.o h3.o
PROGRAM_3 = h3
$(PROGRAM_3): $(ALL_OBJ3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ3) $(INCLUDES) $(LIBS_ALL)

# H4
ALL_OBJ4 = image.o h4.o 
PROGRAM_4 = h4
$(PROGRAM_4): $(ALL_OBJ4)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ4) $(INCLUDES) $(LIBS_ALL)

# Compiling all
all:
	make $(PROGRAM_1)
	make $(PROGRAM_2)
	make $(PROGRAM_3)
	make $(PROGRAM_4)


run:
	./h1 hough_simple_1.pgm output_h1.pgm
	./h2 output_h1.pgm 45 output_h2.pgm	
	./h3 output_h2.pgm output_h3.pgm output_h3_votingarray.pgm
	./h4 hough_simple_1.pgm output_h3_votingarray.txt 50 output_h4.pgm

# Clean files
clean:
	(rm -f *.o; rm -f $(PROGRAM_1); rm -f $(PROGRAM_2); rm -f $(PROGRAM_3); rm -f $(PROGRAM_4);)
