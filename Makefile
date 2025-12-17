CFLAGS=-D__LINUX__ -Wall -O2 -I../../
LIBS=-lbb_spi_lcd -lAnimatedGIF -lgpiod 

all: hat_gif

hat_gif: main.o
	$(CXX) main.o $(LIBS) -o hat_gif 

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

clean:
	rm -rf *.o hat_gif 
