obj = tmp/FPmain.o tmp/FPUI.o tmp/FPplane.o tmp/serialize.o
flags = -Wall -g
GLflags = -lGL -lglut -lGLU

bin/main: $(obj)
	g++ $(obj) -o $@ $(flags) $(GLflags)

tmp/FPmain.o: FPmain.cpp FPplane.hpp
	g++ -c $< -o $@ $(flags) $(GLflags)

tmp/FPUI.o: FPUI.cpp FPUI.hpp
	g++ -c $< -o $@ $(flags) $(GLflags)

tmp/FPplane.o: FPplane.cpp FPplane.hpp
	g++ -c $< -o $@ $(flags)

tmp/serialize.o: serialize.cpp serialize.hpp
	g++ -c $< -o $@ $(flags)
