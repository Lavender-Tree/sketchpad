CC = g++
LIBS_L = -lGL -lGLU -lglut
LIBS_W = -lglut32 -lglu32 -lopengl32
env = $(shell uname)
FILE = ./shape/Data.cpp ./shape/Shape.cpp ./shape/Line.cpp ./shape/Rect.cpp ./shape/Circle.cpp File_no_s.cpp main.cpp

sketchpad: 
ifeq ($(env), Linux)
	$(CC) $(FILE) -o sketchpad $(LIBS_L)
else
	$(CC) $(FILE) -o sketchpad.exe $(LIBS_W)
endif

debug:
	make clean
	make sketchpad
	./sketchpad
	
clean:
	rm -rf sketchpad*