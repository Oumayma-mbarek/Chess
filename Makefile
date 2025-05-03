TARGET= chess

CXX = g++
CXXFLAGS= -Wall -g -b -fanalyzer -Wextra -Werror -std=c++11


SRC = $(wildcard *.cpp)
OBJ=$(SRC:.cpp =.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^


%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^


clean:
	rm -f $(OBJ) $(TARGET)
