//
// Hashtable.cpp
//

#include <iostream>
#include <vector>
#include <string>
#include "Hashtable.h"
#include "hashfunc.h"
using namespace std;

// Hashtable
//   purpose: constructor
//   arguments: none
//   returns: nothing
//   does: Constructs a Hashtable with defined properties
Hashtable::Hashtable()
{
	table_capacity = INIT_CAPACITY;
	table_count = 0;
	table = new HashedItems[table_capacity];
	for (int i = 0; i < table_capacity; i++)
	{
		table[i].alpha_only_word = "";
		table[i].songinfo = NULL;
	} 
}

// ~Hashtable
//   purpose: destructor
//   arguments: none
//   returns: nothing
//   does: clears memory
Hashtable::~Hashtable()
{
	clear_vectors();
	delete [] table;
}

// insert
//   purpose: inserts a word and pointer into hashtable
//   arguments: string and pointer to SongInfo vector
//   returns: nothing
//   does: Hashes word and inserts into the hashtable
//         linear probe in case of collision
void Hashtable::insert(string word, vector<SongInfo> *info)
{
	float LF = load_factor();
	if (LF > MAX_LOAD_FACTOR)
	{
		expand();
	}
	unsigned int hash_value = hash_string(word);
	int table_position;
	bool done_inserting = false;
	int attempt = 0;
	while (!done_inserting)
	{ //linear probe to find a open spot in hashtable
		table_position = (hash_value + attempt)%table_capacity;
		if (table[table_position].alpha_only_word != "") 
		{ 
			attempt++;
		} 
		else 
		{
			table[table_position].songinfo = info;
			table[table_position].alpha_only_word = word;
			table_count++;
			done_inserting = true;
		}
	}
}

// find
//   purpose: finds a word in hashtable
//   arguments: string
//   returns: the pointer to the SongInfo vector with contained word
//   does: Searches through hashtable to get the poitner to the
//         vector that contains the word.
vector<SongInfo> *Hashtable::find(string word)
{
	unsigned int hash_value = hash_string(word);
	int table_position;
	int attempt = 0;
	bool done_searching = false;
	bool found_word = false;
	while(!done_searching)
	{
		table_position = (hash_value + attempt)%table_capacity;
		if (table[table_position].alpha_only_word == "")
		{
			done_searching = true;
		}
		else if (table[table_position].alpha_only_word != word)
		{
			attempt++;
		}
		else
		{
			done_searching = true;
			found_word = true;
		}
	}
	if (found_word == true)
	{
		return table[table_position].songinfo;
	}
	else
		return NULL;
}

// load_factor
//   purpose: determines the current load factor of hashtable
//   arguments: none
//   returns: float number
//   does: calculates the load factor using table_count and capacity
float Hashtable::load_factor()
{
	return table_count/table_capacity;
}

// expand
//   purpose: expands hashtable
//   arguments: none
//   returns: nothing
//   does: when load factor is too high, doubles the hashtable capacity
//         Then rehashes all values into the new hashtable.
void Hashtable::expand()
{
	HashedItems *new_table = new HashedItems[table_capacity*2];
	for (int i = 0; i < table_capacity*2; i++)
	{
		new_table[i].alpha_only_word = "";
		new_table[i].songinfo = NULL;
	}
	HashedItems *temp = new_table;
	new_table = table;
	table = temp;
	table_capacity = table_capacity*2;
	table_count = 0;
	for (int i = 0; i < table_capacity/2; i++) 
	{
		if (new_table[i].alpha_only_word != "")
		{
			string word = new_table[i].alpha_only_word;
			vector<SongInfo> *info = new_table[i].songinfo;
			insert(word, info);
		}
	}
	delete [] new_table;
}

//vector_remove_end
//   purpose: removes the information from the end of a vector
//            in a hashtable
//   arguments: string
//   returns: nothing
//   does: Sets the pointer to the Song vector to NULL, allowing
//		   new data to be inserted into that spot.
void Hashtable::vector_remove_end(string word)
{
	vector<SongInfo> *sort = find(word);
	if(sort != NULL)
	{
		if ((*sort)[10].song != NULL)
		{
			(*sort)[10].song = NULL;
		}
	}
}

void Hashtable::clear_vectors()
{
	for (int i = 0; i<table_capacity; i++)
	{
		if (table[i].songinfo != NULL)
		{
			delete table[i].songinfo;
			table[i].songinfo = NULL;
		}
	}
}
