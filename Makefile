all: 
	g++ arenagame.cpp -lm -o arenagame tinystr.cpp tinyxml.cpp  tinyxmlerror.cpp tinyxmlparser.cpp -lGLU -lGL -lglut

clean:
	rm -rf arenagame



