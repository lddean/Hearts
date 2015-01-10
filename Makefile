CXX = g++                                     # compiler
CXXFLAGS = -g -Wall -MMD                      # compiler flags
MAKEFILE NAME = ${firstword ${MAKEFILE LIST}} # makefile name

OBJECTS1 = p3driver.o Card.o CardPile.o Deck.o Trick.o Player.o SmartPlayer.o RandomPlayer.o HumanPlayer.o
EXEC1 = Hearts                        # executable name

OBJECTS = ${OBJECTS1} ${OBJECTS2}
EXECS = ${EXEC1} ${EXEC2}
DEPENDS = ${OBJECTS:.o=.d}                    # substitute ".o" with ".d"

.PHONY : all clean

all : ${EXECS}

${EXEC1} : ${OBJECTS1}                        # link step
	${CXX} ${CXXFLAGS} $^ -o $@           # make sure there is a tab at the start of this line

${EXEC2} : ${OBJECTS2}                        # link step
	${CXX} ${CXXFLAGS} $^ -o $@           # line starts with a tab

${OBJECTS} : ${MAKEFILE NAME}                 # OPTIONAL : changes to this file => recompile

-include ${DEPENDS}                           # include *.d files containing program dependences

clean :                                       # remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXECS}