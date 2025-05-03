TARGET=chess

CXX=g++
CXXFLAGS=-Wall -g -fanalyzer -Wextra -Werror -std=c++11 -Wshadow -O2 -Wno-analyzer-use-of-uninitialized-value



SRC=$(wildcard *.cpp)
OBJ=$(subst .cpp,.o,$(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^


%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<


clean:
	rm -f $(OBJ) $(TARGET)
