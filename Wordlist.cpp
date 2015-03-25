//
// Wordlist.cpp
//

#include <iostream>
#include <sstream>
#include <fstream>
#include "Wordlist.h"
#include "Hashtable.h"
#include "Songs.h"
using namespace std;

// ~Wordlist
//   purpose: destructor
//	 arguments: none
//	 returns: nothing
//	 does: Cleans memory
Wordlist::~Wordlist()
{
}

// read_lyics 
//   purpose: read in song data from a disk file
//   arguments: the name of the file, bool to ask for progress status
//   returns: nothing
//   does: calls a function each time a word is found
void Wordlist::read_lyrics(const char * filename, bool show_progress)
{
        ifstream in(filename);			// creates an input stream
        int song_count = 0;			// for progress indicator
	string artist, title, word;

	// -- While more data to read...
	while ( ! in.eof() ) 
	{
		// -- First line is the artist
		getline(in, artist);
		if (in.fail()) break;

		// -- Second line is the title
		getline(in, title);
		if (in.fail()) break;

		if ( show_progress )
		{
			song_count++;
			if (song_count % 10000 == 0) {
				cout << "At "       << song_count << 
					" Artist: " << artist     << 
					" Title:"   << title << endl;
			}
		}

		Songs s;
		s.insert_info(artist, title);
		// -- Then read all words until we hit the 
		// -- special <BREAK> token
		while ( in >> word && word != "<BREAK>" ){
			// -- Found a word
			s.insert_lyrics(word);
		}
		allSongs.push_back(s);

		// -- Important: skip the newline left behind
		in.ignore();
	}
	int Songs_length = allSongs.size();
	for (int i = 0; i < Songs_length; ++i)
	{
		insert_hash(i);
		if(i % 10000 == 0)
			cout << i+1 << " inserted" << endl;
	}
}

// alpha_only
//   purpose: converts a string to lowercase and alphabetic characters
//            only. E.g., "Bang!" becomes "bang"
//   arguments: a string
//   returns: the alpha-only string
//   does: converts the string
string Wordlist::alpha_only(string s)
{
        ostringstream ss;
        for (size_t i=0;i<s.length();i++) {
                if (isalnum(s[i])){
                        ss << (char)(tolower(s[i]));
                }
        }
        return ss.str();
}


//
// search
//   purpose: Finds top 10 songs that contain the searched word the most.
//   arguments: a string
//   returns: nothing
//   does: Prints out the top 10 song, with song title, artist, and context.
void Wordlist::search(string s)
{
	string word = alpha_only(s);
	vector<SongInfo> *search = hash.find(word);
	if (search == NULL)
	{ //if word not found, return
		return;
	}
	else 
	{ //word is found
		for (int i = 0; i < 10; i++)
		{ //iterate through the top 10 spots in SongInfo vector
			if ((*search)[i].song != NULL)
			{ //if the vector spot is filled
				string title = (*search)[i].song->title;
				string artist = (*search)[i].song->artist;
				vector<string>lyrics = (*search)[i].song->lyrics;
				int lyrics_size = lyrics.size();
				for (int j = 0; j < lyrics_size; j++)
				{ //search through lyrics for word match
					if (s == alpha_only(lyrics[j]))
					{	//found match
						cout << "Title: " << title << endl;
						cout << "Artist: " << artist << endl;
						cout << "Context: ";
						for (int k = j-5; k < j+6; k++)
						{ //creating/printing out context
							if (k >= 0 && k < lyrics_size)
								cout << lyrics[k] << " ";
						}
						cout << endl;
					}
				}
			}
		}
	}
}

// insert_hash 
//   purpose: inserts all the words in a song into the hash table.
//   arguments: integer
//   returns: nothing
//   does: Using the index of a song, puts each individual lyric into 
//		   the hashtable.
void Wordlist::insert_hash(int song_number)
{
	SongInfo s_i; 
	bool vector_full = false; //if the vector has all 11 spaces filled
	int lyrics_length = allSongs[song_number].lyrics.size();
	
	for (int j = 0; j < lyrics_length; ++j)
	{ //iterate through every word in song
		string word = alpha_only(allSongs[song_number].lyrics[j]);
		vector<SongInfo> *search = hash.find(word);
		s_i.song = &(allSongs[song_number]);
		s_i.wordCount = 1;
		if(search == NULL)
		{ //word is not in hashtable, create new vector
				vector<SongInfo> *info = new vector<SongInfo>(11);
				info->push_back(SongInfo());
				(*info)[0] = s_i;
				hash.insert(word, info);
		}
		else
		{  //word is in hashtable, determine whether it is a different song
			bool Song_in_vector = false; //if the Song is in the vector already

			//index to search through SongInfo vector for existing Song
			int index = 0; 
			
			//iterator to search for next open spot in vector for a new Song
			int next_spot;
			while (index < 11 && (*search)[index].song != NULL) 
			{
				if (s_i.song->artist == (*search)[index].song->artist &&
					s_i.song->title == (*search)[index].song->title)
				{
					//index in vector already contains current Song
					//increment wordCount
					(*search)[index].wordCount++;
					Song_in_vector = true;
					break;
				}
				index++;
			}
			if (Song_in_vector == false)
			//if the current song is not in the vector
			{
				for (int i = 0; i < 11; i++)
				{
					if ((*search)[i].song == NULL)
					{ //found next open spot in vector
						next_spot = i;
						search->push_back(SongInfo());
						(*search)[next_spot] = s_i;
						break;
					}
				}
			}
			sort(search);
			if ((*search)[10].song != NULL)
			{	//if the vector is full, sort the vector
				vector_full = true;
			}
		}
	}

	for (int i = 0; i < lyrics_length; ++i)
	{ //go through all lyrics of current song
		if (vector_full == true)
		{ //if vector is full, remove the last member
			string word = alpha_only(allSongs[song_number].lyrics[i]);
			hash.vector_remove_end(word);
		}
	}
}

// sort
//   purpose: sorts the vector by wordCount, highest to lowest
//   arguments: a pointer to a SongInfo vector
//   returns: nothing
//   does: Selection sort on vector.
void Wordlist::sort(std::vector<SongInfo> *song_list)
{
	for (int i = 0; i < 11; i++)
	{
		if ((*song_list)[i].song == NULL)
			return;
		int index = i;
		int largest = (*song_list)[i].wordCount;
		for (int j = i+1; j < 11; j++)
		{
			if ((*song_list)[j].song == NULL)
				break;
			if (largest < (*song_list)[j].wordCount)
			{
				largest = (*song_list)[j].wordCount;
				index = j;
			}
		}
		SongInfo swap = (*song_list)[index];
		(*song_list)[index] = (*song_list)[i];
		(*song_list)[i] = swap;
	}
}