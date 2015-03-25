#include <iostream>
#include <vector>
#include <string>
#include "Songs.h"

#ifndef _Hashtable_H_
#define _Hashtable_H_

#define MAX_LOAD_FACTOR 0.7
#define INIT_CAPACITY 5

struct SongInfo
{
	Songs *song;
	int wordCount;
};

struct HashedItems
{
	std::vector<SongInfo> *songinfo;
	std::string alpha_only_word;
};

class Hashtable {
public:
	Hashtable();
	~Hashtable();
	void insert(std::string word, std::vector<SongInfo> *info);
	std::vector<SongInfo> *find(std::string word);
	float load_factor();
	void vector_remove_end(std::string word);
	void clear_vectors();
private:
	HashedItems *table;
	void expand();
	int table_capacity;
	float table_count;
};

#endif /* _Hashtable_H_ */