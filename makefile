all:
	g++ -o main main.cpp datastructure/*.cpp datastructure/base/*.cpp -lpthread -lm -std=c++0x -pthread

clean:
	rm main
