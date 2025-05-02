TARGET= chess

CC = g++
CFLAGS= -Wall -g -b -fanalyzer -Werror -std=c++11

SRC = $(wildcard *.cpp)
OBJ=$(SRC: .cpp =.o)

$(TARGET): $(OBJ)
	$(CC)  $(OBJ) -o $(TARGET)

%.o: %.cpp 
	$(CC) $(CFLAGS) -c $^ 


clean:
	rm -f $(OBJS) $(TARGET)
