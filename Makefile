SRC=src/core/base.cpp src/core/main.cpp
INC=inc/core/base.hpp
srv: $(SRC) $(INC)
	g++ -o srv $(SRC) -I./inc -ldl $(XT)
clean: srv
	rm srv
