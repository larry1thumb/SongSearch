//
// Songs.h
// Header file for the Songs class
//

#include <iostream>

#ifndef _Songs_H_
#define _Songs_H_

class Songs {
public:
	//insert lyrics into lyrics vector
	void insert_lyrics(std::string l); 
	void insert_info(std::string a, std::string t);
	std::string artist;
	std::string title;
	std::vector<std::string>lyrics;
private:
};

#endif /* _Songs_H_ */