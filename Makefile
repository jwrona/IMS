#Makefile
#author: Jan Wrona, xwrona00@stud.fit.vutbr.cz
#projet: SHO Vyrobni linka
#lecture: IMS
#language: C++/SIMLIB


#####################################
# files

TARGET = pizza
SOURCES = main.cpp generator.cpp order.cpp batch.cpp timeout.cpp
HEADERS = main.h   generator.h   order.h   batch.h   timeout.h
OBJECTS = main.o   generator.o   order.o   batch.o   timeout.o

#####################################
# compiler, linker and options
CC = gcc
CXX = g++

CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra
OFLAG = -o
CFLAG = -c

LINK = $(CXX)
LIBS = -lsimlib

#####################################
# suffix rules

.SUFFIXES: .cpp .o
.cpp.o:
	$(CXX) $(CXXFLAGS) $(CFLAG) $(OFLAG) "$@" "$<"


#####################################
#build rules

all: $(OBJECTS)
	$(LINK) $(LIBS) $(OFLAG) $(TARGET) $(OBJECTS)

ndebug: CXXFLAGS += -DNDEBUG
ndebug: ndebug_print

ndebug_print: CXXFLAGS += -DNDEBUG_PRINT
ndebug_print: all

run:
	./$(TARGET)

#####################################
#other rules

touch:
	touch $(SOURCES) $(HEADERS)

compress:
	tar -cf $(TARGET).tar $(SOURCES) $(HEADERS) Makefile
	gzip $(TARGET).tar

clean:
	rm -f $(OBJECTS) *~

distclean: clean
	rm -f $(TARGET)
