
# require: liboost_date_time libboost_system libboost_filesystem libzip

CXX=g++
#CXXFLAGS=-Wall -g
CXXFLAGS=-Wall
LDFLAGS=-lboost_system -lboost_filesystem -lboost_date_time -lzip
SOURCES=main.cpp ods_reader.cpp content_reader.cpp algorithms.cpp
HEADERS=common_types.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main



all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $< 

.PHONY : clean
clean:
	rm -f $(EXECUTABLE)
	rm -f $(OBJECTS)
