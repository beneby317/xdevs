
MY_INCLUDE_PATH = $(HOME)/workspace/xdevs/include
MY_BUILD_PATH = $(HOME)/workspace/xdevs/bin
MY_TARGET = xdevs.exec

INC_PATH = \
    -I${MY_INCLUDE_PATH} \

LIB_PATH = \

LIBS = \
    -lm \
    -lstdc++ \
    -lpthread \

CC = g++
CFLAGS = -Wall -g -O0 ${INC_PATH}
OFILES = $(CFILES:.cpp=.o)

CFILES = \
main.cpp \
xobject.cpp \
xmanager.cpp
$(END)

.cpp.o:
	$(CC) $(CFLAGS) -c $*.cpp 
	
$(MY_BUILD_PATH)/$(MY_TARGET): $(OFILES) 
	$(CC) -o $@ $(CFLAGS) $(OFILES) $(LIBS) $(LIB_PATH)

clean:
	rm -f *.o

