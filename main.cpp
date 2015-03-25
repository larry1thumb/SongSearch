/*
 * main.cpp
 *
 */
#include "Wordlist.h"

int main(int argc, char *argv[])
{
	std::string filename;
	Wordlist wordlist;

	if (argc == 2) { // if there is a filename on the command line
		wordlist.read_lyrics(argv[1], true);
	}
	else { // use a pre-defined filename
		filename = "rick_db.txt";
		//filename = "lyrics_fulldb.txt";
	        wordlist.read_lyrics(filename.c_str(),false);
	}
		std::cout << "Enter word: ";
		std::string word;
		while (word != "<BREAK>")
		{
			std:: cin >> word;
        	wordlist.search(word);
        	if (word != "<BREAK>")
        		std::cout << "<END-OF-REPORT>" << std::endl;
        }
        return 0;
        
}