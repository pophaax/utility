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


all: $(FILE)

$(FILE): $(SOURCES) $(HEADERS)
	$(CC) $(SOURCES) $(FLAGS) $(LIBS) -c -o $(FILE)

clean:
	rm -f $(FILE)