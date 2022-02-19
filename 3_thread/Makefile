SOURCE_FILE := main.cpp 
CPP_FLAG := -fno-elide-constructors
			-std=c++11

a.out : main.o
	g++ $(SOURCE_FILE) $(CPP_FLAG)

.PHONE: clean
clean:
	rm main.o a.out