#Makefile
#author: Jan Wrona, xwrona00@stud.fit.vutbr.cz
#projet: SHO Vyrobni linka
#lecture: IMS
#language: C++/SIMLIB


#####################################
# files

TARGET = pizza
SOURCES = main.cpp generator.cpp order.cpp
HEADERS = generator.h order.h
OBJECTS = main.o generator.o order.o 

#####################################
# compiler, linker and options
CC = gcc
CXX = g++

CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra
OFLAG = -o
CFLAG = -c

LINK = g++
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
