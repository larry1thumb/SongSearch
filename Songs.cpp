//
// Songs.cpp
// Code that defines a Song class which contains
// Song title, Artist and the lyrics
//

#include <iostream>
#include <vector>
#include "Songs.h"
using namespace std;

//insert_lyrics
// 	 purpose: stores all the songs lyrics into a vector
//	 arguments: none
// 	 returns: nothing
// 	 does: Inserts full lyrics into the lyrics vector 
void Songs::insert_lyrics(string l)
{
	lyrics.push_back(l);
}

//insert_info
//   purpose: stores the artist and song title information
//   arguments: two strings
//   returns: nothing
//   does: Inserts artist and title into the Songs
void Songs::insert_info(string a, string t)
{
	artist = a;
	title = t;
}
