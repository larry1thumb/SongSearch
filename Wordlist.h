//
// Wordlist.h
// Header File for Wordlist class
//

#include <iostream>
#include <vector>
#include "Songs.h"
#include "Hashtable.h"

#ifndef _Wordlist_H_
#define _Wordlist_H_

class Wordlist {
public:
	~Wordlist();
	void read_lyrics(const char * filename, bool show_progress);
	std::string alpha_only(std::string s);
	void insert_hash(int i);
	void sort(std::vector<SongInfo> *song_list);
	void search(std::string s);
private:
	Hashtable hash;
	std::vector<Songs> allSongs;
};

#endif /* _Wordlist_H_ */