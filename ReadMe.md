# ReadMe for COMP 15 HW6
## Song Search 

This file searches through a database of songs that contain a searched word.  The program prints out the artist, title, and context of the song.

main.cpp
Main file that runs the program

Wordlist.cpp
Holds the hashtable and vector of songs.
Reads in lyrics and stores them in the hashtable and vector.

Hashtable.cpp
Handles inserting and searching the Hashtable

Songs.cpp
Defines the Song class and inserts data and lyrics.

Compile using the Makefile

Outline of Data Structures:
Vector of all songs containing artist, title, and lyrics 
Hashtable made up of a word and a pointer to a SongInfo vector.
SongInfo vector with the wordcount and a pointer that indexes into song vector.

SongInfo vector is capped at a size of 11, 
Everytime the vector is full, vector is sorted using a selection sort, then the last value is removed. 
Each SongInfo vector also points to the Song vector for a quick memory-efficient way to find the information of the song.
All of this is contained within the hashtable for constant time lookup. 
