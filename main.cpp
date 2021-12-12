/*****************************************************************************************************************************************************
*
* Christopher Bakhos
*
* Created: Wednesday, December 8, 2021
*
*****************************************************************************************************************************************************/

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

char makeLowercase( char character ) {
	switch( character ) {
		case 'A':
			character = 'a';
			break;
		case 'B':
			character = 'b';
			break;
		case 'C':
			character = 'c';
			break;
		case 'D':
			character = 'd';
			break;
		case 'E':
			character = 'e';
			break;
		case 'F':
			character = 'f';
			break;
		case 'G':
			character = 'g';
			break;
		case 'H':
			character = 'h';
			break;
		case 'I':
			character = 'i';
			break;
		case 'J':
			character = 'j';
			break;
		case 'K':
			character = 'k';
			break;
		case 'L':
			character = 'l';
			break;
		case 'M':
			character = 'm';
			break;
		case 'N':
			character = 'n';
			break;
		case 'O':
			character = 'o';
			break;
		case 'P':
			character = 'p';
			break;
		case 'Q':
			character = 'q';
			break;
		case 'R':
			character = 'r';
			break;
		case 'S':
			character = 's';
			break;
		case 'T':
			character = 't';
			break;
		case 'U':
			character = 'u';
			break;
		case 'V':
			character = 'v';
			break;
		case 'W':
			character = 'w';
			break;
		case 'X':
			character = 'x';
			break;
		case 'Y':
			character = 'y';
			break;
		case 'Z':
			character = 'z';
			break;
		default:
			break;
	}
	return character;
}

// Template this later?
struct Unigram {
	std::string one;
	
	//bool operator<( const Unigram& rhs ) { return ( one < rhs.one ); }
	friend bool operator<( Unigram const& lhs, Unigram const& rhs ) {
		return ( lhs.one < rhs.one );
	}
};

struct Bigram {
	std::string one;
	std::string two;
	
	friend bool operator<( Bigram const& lhs, Bigram const& rhs ) {
		if( lhs.one < rhs.one ) {
			return true;
		}
		else if( lhs.one == rhs.one ) {
			if( lhs.two < rhs.two ) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
};

struct Trigram {
	std::string one;
	std::string two;
	std::string three;
	
	friend bool operator<( Trigram const& lhs, Trigram const& rhs ) {
		if( lhs.one < rhs.one ) {
			return true;
		}
		else if( lhs.one == rhs.one ) {
			if( lhs.two < rhs.two ) {
				return true;
			}
			else if( lhs.two == rhs.two ) {
				if( lhs.three < rhs.three ) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
};

int main() {
	// parse text file
	// use parsed file to create vocab
	// use vocab to compute ngram probabilities
	// generate? other stuff? You now have a language model.
	
	// File and directory name
	std::string directoryName = "./source/textfiles/";
	std::string fileName = "P1_real_fake_review_train.txt";
	
	// Open and parse the file
	std::string line;
	std::vector<std::string> lines;
	
	std::fstream file;
	std::cout << directoryName + fileName << '\n';
	file.open( directoryName + fileName, std::fstream::in );
	
	for( std::string line; std::getline( file, line ); ) {
		lines.push_back( line );
	}
	
	file.close();
	
	std::vector<std::string> entries;
	for( auto it = std::begin( lines ); it != std::end( lines ); ++it ) {
		std::string entry = "";
		char character;
		for( auto lineIterator = it->begin(); lineIterator != it->end(); ++lineIterator ) {
			character = *lineIterator;
			//std::cout << character << '\n';
			if( character == '|' ) {
				//std::cout << "no" << '\n';
				entries.push_back( entry );
				break;
			}
			else {
				entry += character;
			}
		}
	}
	
	std::vector<std::string> words;
	for( auto it = std::begin( entries ); it != std::end( entries ); ++it ) {
		std::string word = "";
		char character;
		for( auto entryIterator = it->begin(); entryIterator != it->end(); ++entryIterator ) {
			character = *entryIterator;
			character = makeLowercase( character );
			// If a special character is detected
			if( ( character == '!' || character == '.' || character == '"' || character == '\'' || character == '?' || character == '(' || character == ')' || character == ',' || character == ' ' || character == '-' || character == ':' || character == ';' || character == '/' || character == '*' || character == '#' || character == '+' || character == '~' ) ) {
				// And if that special character comes at the direct end of a word
				if( word.compare( "" ) != 0 ) {
					// Push back the word and set the word buffer to empty
					words.push_back( word );
					word = "";
					
					// And set any special tokens
					switch( character ) {
						case ',':
							words.push_back( "," );
							break;
						case ';':
							words.push_back( ";" );
							break;
						case '.':
							words.push_back( "." );
							break;
						case '!':
							words.push_back( "!" );
							break;
						case '?':
							words.push_back( "?" );
							break;
						default:
							break;
					}
				}
				// Otherwise do nothing and just delete the special character. Duplicates are not welcome!
			}
			else {
				word += character;
			}
		}
	}
	
	// Calculate now the ngram counts
	std::map<Unigram, std::pair<unsigned int, std::shared_ptr<Unigram>>> unigramDictionary;
	std::map<Bigram, unsigned int> bigramDictionary;
	std::map<Trigram, unsigned int> trigramDictionary;
	
	for( auto it = std::begin( words ); it != std::end( words ); ++it ) {
		///////////////////////////////////////////////////////////////
		// Create a smart pointer to unigram on the heap
		std::shared_ptr<Unigram> sharedPointer( new Unigram );
		// Set unigram.one to the iterator dereferenced
		sharedPointer->one = *it;
		Unigram unigram = *sharedPointer;
		// Increment the count of the unigram
		unigramDictionary[unigram].first++;
		// Check if there is not yet an entry for unigram. If there is not, the pointer need be updated
		if( !unigramDictionary.count(unigram) )
			unigramDictionary[unigram].second = sharedPointer;
		///////////////////////////////////////////////////////////////
		
		// Calculate bigram occurrences
		Bigram bigram;
		bigram.one = *it;
		bigram.two = *std::next(it);
		bigramDictionary[bigram]++;
		
		// Calculate trigram occurrences
		Trigram trigram;
		trigram.one = *it;
		trigram.two = *std::next(it);
		trigram.three = *std::next(it, 2);
		trigramDictionary[trigram]++;
	}
	
	// Define vector of dictionary iterators so we can access randomly
	// std::vector<std::pair<const Unigram, unsigned int>*> unigramPointers;
	// unsigned int iteratorCounter = 0;
	
	// for( auto it = std::begin( unigramDictionary ); it != std::end( unigramDictionary ); ++it ) {
		// iteratorCounter++;
		// unigramPointers[iteratorCounter] = &(*it);
	// }
	
	//std::cout << unigramPointers[0]->first.one << '\n';
	
	
	
	// std::vector<std::pair<Bigram, unsigned int>> bigramDictionary;
	// std::vector<std::pair<Trigram, unsigned int>> trigramDictionary;
	
	// Create random things for generating a sequence of words
	// std::default_random_engine generator;
	// std::discrete_distribution<int> unigramDistribution;
	// std::discrete_distribution<int> bigramDistribution;
	// std::discrete_distribution<int> trigramDistribution;
	
	for( int i = 0; i < 10; i++ ) {
		
	}
	
	// for( auto it = std::begin( unigramDictionary ); it != std::end( unigramDictionary ); ++it ) {
		// std::cout << it->first.one << " : " << it->second << '\n';
	// }
	
	// for( auto it = std::begin( bigramDictionary ); it != std::end( bigramDictionary ); ++it ) {
		// std::cout << it->first.one << " " << it->first.two << " : " << it->second << '\n';
	// }
	
	// for( auto it = std::begin( trigramDictionary ); it != std::end( trigramDictionary ); ++it ) {
		// std::cout << it->first.one << " " << it->first.two << " " << it->first.three << " : " << it->second << '\n';
	// }
	
	std::cout << "Unigram entries: " << unigramDictionary.size() << ", bigram entries: " << bigramDictionary.size() << ", trigram entries: " << trigramDictionary.size() << '\n';
	
	return 0;
}