.SUFFIXES: .cpp .o
CXX = g++
CXXFLAGS = -g  -Wall
EXECUTE = main
OBJECTS = player.o deck.o main.o

${EXECUTE}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -o ${EXECUTE} ${OBJECTS}

.cpp .o:
	${CXX} ${CXXFLAGS} -c $<

player.o: player.cpp player.h
deck.o : deck.cpp deck.h
main.o: main.cpp player.h deck.h

clean:
	rm -f ${EXECUTE} ${OBJECTS}

# COMMENTS:
# $< the dependencies that changed
# $@ the target
# $^ all the dependencies
# 	
# Makefiles are usually built like: 
# target: deependencies
#  /t command
#  /t another command
#
#  target -> name of file or an action
#  dependencies -> are files needed to create the target
#  command line must start with tab can get away with this if you escaped with \ endline
