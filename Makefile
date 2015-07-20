#######################################################
#
#    Aland Sailing Robot
#    ===========================================
#    utility
#    -------------------------------------------
#
#######################################################

CC = g++
FLAGS = -Wall -pedantic -Werror -std=c++14 
LIBS = -I$(SAILINGROBOTS_HOME)

SOURCES = Utility.cpp
HEADERS = Utility.h
FILE = Utility.o

SOURCES_TIMER = Timer.cpp
FILE_TIMER = Timer.o

OBJ = $(FILE) $(FILE_TIMER)

all: $(OBJ)

$(FILE): $(SOURCES) $(HEADERS)
	$(CC) $(SOURCES) $(FLAGS) $(LIBS) -c -o $(FILE)

$(FILE_TIMER): $(SOURCES_TIMER) Timer.h
	$(CC) $(SOURCES_TIMER) $(FLAGS) $(LIBS) -c -o $(FILE_TIMER)

clean:
	rm -f $(OBJ)