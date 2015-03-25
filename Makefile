#
# Makefile for SongSearch, Assignment 6
#
CXX = clang++
FLAGS = -Wall -g3 -g

songsearch: Songs.cpp Songs.h Wordlist.cpp Wordlist.h \
			Hashtable.cpp Hashtable.h hashfunc.cpp hashfunc.h main.cpp
	${CXX} ${FLAGS} -o songsearch Wordlist.cpp Songs.cpp Hashtable.cpp \
					   hashfunc.cpp main.cpp
	
clean:
	rm -f songsearch

provide_design:
	provide comp15 hw6_design songsearch_design.txt

provide:
	provide comp15 hw6 Songs.cpp Songs.h Wordlist.cpp Wordlist.h \
			Hashtable.cpp Hashtable.h hashfunc.cpp hashfunc.h main.cpp \
			Makefile ReadMe.md

