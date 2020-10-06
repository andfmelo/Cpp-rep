/*
author:		Andre Florentino Melo
Date:		March 28, 2020
Purpose:	The purpose of this program is to encode a book message into numbers.

file:		bce.cpp
author:	Andre Florentino Melo
date:		March 28, 2020
version:	1.0
brief:		Book ciphers work by replacing words in the plaintext of a message with the location of words from the book being used. In this mode, 
			book ciphers are more properly called codes, and we encode them into another file.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

/*
fn:		fileToChar
brief:	Transform a txt file into a vector of chars
param:  accepts a ifstream of a txt file asa a parameter, and returns a vector of type char.
return:	describe return value
*/

vector<char> fileToChar(ifstream & bookfile)
{
	
	char character;
	vector<char>textChar;

	while (bookfile.get(character))
	{
		textChar.push_back(character);
	}

	return textChar;
}

int main(int argc, char*argv[])
{
	//tests if number of inputs of an argument in command line is valid

	if (argc < 4)
	{
		cerr << "Error, to few arguments.";
		return EXIT_FAILURE;
	}
	else if (argc > 4)
	{
		cerr << "Error, to many arguments.";
		return EXIT_FAILURE;
	}

	ifstream bookfile(argv[1], ios::in);

	//if file is not compatible

	if (!bookfile)
	{
		//gives an error and show to the user that the input is invalid
		cerr << "Error reading the file\n";
		return EXIT_FAILURE;
	}

	
	ifstream originalMsg(argv[2], ios::in);

	ofstream encodedMsg(argv[3], ios::out);

	vector<string> bookCode;

	string encode;
	char character;
	int pageCount = 0;
	int lineCount = 0;
	int columnCount = 0;
	
	while (bookfile.get(character))
	{

		//using to_string (int val);
		encode = to_string(pageCount) + "," + to_string(lineCount) + "," + to_string(columnCount);
		bookCode.push_back(encode);

		//we are basically counting the number of words until the word we are looking for and adding it to columnCount.
		columnCount++;

		if (character == '\n')
		{
			//we've found and end of line character '\n', increment line counter
			lineCount++;
			
			//reset columnCount since we did not find the word in the line
			columnCount = 0;

		}
		else if(character == '\f')
		{
			//we've found and end of page character '\p', increment page counter
			pageCount++;

			//reset the line count since we've reached a new page
			lineCount = 0;

			//reset columnCount since we did not find the word within the page
			columnCount = 0;

		}

	}

	//bookCode should be populated by the coding scheme
	//restoring default condition 

	bookfile.clear();
	bookfile.seekg(0, ios::beg);


	
	string encodedCh;
	char msgCh;
	size_t index;

	vector<char>textChar;
	textChar = fileToChar(bookfile);

	
	//while loop to encode the message

	while (originalMsg.get(msgCh))
	{
		auto foundCh = find(textChar.begin(), textChar.end(), msgCh);

		if (!(foundCh == textChar.end()))
		{
			index = distance(textChar.begin(), foundCh);

			encodedCh = bookCode[index];
			encodedMsg << encodedCh << " ";

			textChar.erase(textChar.begin() + index);
			bookCode.erase(bookCode.begin() + index);

		}
		else {
			cerr << "Missing character test.";
			return EXIT_FAILURE;
		}
	}


}