
all: headerfiler cppfiler	
	g++  nRad*.o -o nRad
	echo "g++  nRad*.o -o nRad"

cppfiler:g++ -c nRad*.cpp 
echo "g++ -c nRad*.cpp "
headerfiler:g++ -c nRad*.h
echo "g++ -c nRad*.h"
