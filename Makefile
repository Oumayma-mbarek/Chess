TARGET=echecs

CXX=g++
CXXFLAGS=-Wall -g -Wextra -Werror -std=c++11 -Wshadow -O2 -Wno-analyzer-use-of-uninitialized-value


DOXYGEN=doxygen
DOXYGEN_CONFIG=Doxyfile

SRC=$(wildcard *.cpp)
OBJ=$(subst .cpp,.o,$(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^


%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

doc: $(DOXYGEN_CONFIG)
	$(DOXYGEN) -g $(DOXYGEN_CONFIG)

clean:
	rm -f $(OBJ) $(TARGET)

doc-clean:
	rm -rf html latex

doc-view:
	xdg-open html/index.html