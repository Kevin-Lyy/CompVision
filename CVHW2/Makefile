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

# P1
ALL_OBJ1 = image.o p1.o 
PROGRAM_1 = p1
$(PROGRAM_1): $(ALL_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ1) $(INCLUDES) $(LIBS_ALL)

# P2
ALL_OBJ2 = image.o p2.o
PROGRAM_2 = p2
$(PROGRAM_2): $(ALL_OBJ2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ2) $(INCLUDES) $(LIBS_ALL)

# P3
ALL_OBJ3 = image.o p3.o functions.cc
PROGRAM_3 = p3
$(PROGRAM_3): $(ALL_OBJ3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ3) $(INCLUDES) $(LIBS_ALL)

# P4
ALL_OBJ4 = image.o p4.o functions.cc
PROGRAM_4 = p4
$(PROGRAM_4): $(ALL_OBJ4)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ4) $(INCLUDES) $(LIBS_ALL)

# Compiling all
all:
	make $(PROGRAM_1)
	make $(PROGRAM_2)
	make $(PROGRAM_3)
	make $(PROGRAM_4)

run:
	./p1 many_objects_2.pgm 120 objects_output_1.pgm
	./p2 many_objects_2.pgm objects_output_2.pgm
	./p2 many_objects_1.pgm objects_output_2_2.pgm
	./p3 objects_output_2.pgm database.txt objects_output_3.pgm 
	./p4 objects_output_2_2.pgm database.txt objects_output_4.pgm
# Clean files
clean:
	(rm -f *.o; rm -f $(PROGRAM_1); rm -f $(PROGRAM_2); rm -f $(PROGRAM_3); rm -f $(PROGRAM_4);)
