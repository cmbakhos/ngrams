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
	
	// Create a few dictionaries (maps) for the ngrams
	std::map<Unigram, unsigned int> unigramDictionary;
	std::map<Bigram, unsigned int> bigramDictionary;
	std::map<Trigram, unsigned int> trigramDictionary;
	
	// Create a few vectors for the ngrams
	std::vector<Unigram> unigramVector;
	std::vector<Bigram> bigramVector;
	std::vector<Trigram> trigramVector;
	
	// Loop through all of the parsed words
	for( auto it = std::begin( words ); it != std::end( words ); ++it ) {
		// Unigrams
		Unigram unigram;
		unigram.one = *it;
		if( !unigramDictionary.count( unigram ) ) {
			//std::cout << "no" << '\n';
		}
		unigramDictionary[unigram]++;
		
		// Bigrams
		Bigram bigram;
		bigram.one = *it;
		bigram.two = *std::next(it);
		if( !bigramDictionary.count( bigram ) ) {
			bigramVector.push_back( bigram );
		}
		bigramDictionary[bigram]++;
		
		// Trigrams
		Trigram trigram;
		trigram.one = *it;
		trigram.two = *std::next(it);
		trigram.three = *std::next(it, 2);
		if( !trigramDictionary.count( trigram ) ) {
			trigramVector.push_back( trigram );
		}
		trigramDictionary[trigram]++;
	}
	
	// Create ngram vectors and ngram frequency vectors for each unigram
	std::vector<unsigned int> unigramFrequencyVector;
	std::vector<unsigned int> bigramFrequencyVector;
	std::vector<unsigned int> trigramFrequencyVector;
	
	for( auto it = std::begin( unigramDictionary ); it != std::end( unigramDictionary ); ++it ) {
		std::pair<const Unigram, unsigned int> unigramEntry = *it;
		unigramVector.push_back( unigramEntry.first );
		unigramFrequencyVector.push_back( unigramEntry.second );
	}
	
	for( auto it = std::begin( bigramDictionary ); it != std::end( bigramDictionary ); ++it ) {
		std::pair<const Bigram, unsigned int> bigramEntry = *it;
		bigramVector.push_back( bigramEntry.first );
		
		// Bigram entry occurences
		unsigned int bigramOccurence = bigramEntry.second;
		
		// Bigram first word
		std::string bigramFirstWord = bigramEntry.first.one;
		
		// Unigram entry based off bigram first word
		Unigram unigramEntry;
		unigramEntry.one = bigramFirstWord;
		
		// Unigram entry occurence based off bigram first word
		unsigned int unigramOccurence = unigramDictionary[unigramEntry];
		
		// Create frequency vector based off unigram entry occurence and bigram first word occurence
		bigramFrequencyVector.push_back( (double) bigramOccurence / (float) unigramOccurence );
	}
	
	for( auto it = std::begin( trigramDictionary ); it != std::end( trigramDictionary ); ++it ) {
		std::pair<const Trigram, unsigned int> trigramEntry = *it;
		trigramVector.push_back( trigramEntry.first );
		trigramFrequencyVector.push_back( trigramEntry.second );
	}
	
	// Create random things for generating a sequence of words
	std::default_random_engine generator;
	
	std::discrete_distribution<int> unigramDistribution( unigramFrequencyVector.begin(), unigramFrequencyVector.end() );
	std::discrete_distribution<int> bigramDistribution( bigramFrequencyVector.begin(), bigramFrequencyVector.end() );
	std::discrete_distribution<int> trigramDistribution( trigramFrequencyVector.begin(), trigramFrequencyVector.end() );
	
	// Unigram generator. Absolutely horrible
	// for( int i = 0; i < 300; i++ ) {
		// std::cout << unigramVector[unigramDistribution( generator )].one << '\n';
	// }
	
	
	
	
	
	// Bigram generator. Start by picking a random unigram.
	std::string previousToken = unigramVector[unigramDistribution( generator )].one;
	std::cout << previousToken << " ";
	
	for( int i = 0; i < 300; i++ ) {
		// From here, we want a list of probabilities of the words that can follow that one.
		std::vector<Bigram> bigramVectorFollowing;
		std::vector<unsigned int> bigramFrequencyVectorFollowing;
		for( auto it = std::begin( bigramDictionary ); it != std::end( bigramDictionary ); it++ ) {
			std::pair<const Bigram, unsigned int> bigramEntry = *it;
			if( bigramEntry.first.one == previousToken ) {
				bigramVectorFollowing.push_back( bigramEntry.first );
				bigramFrequencyVectorFollowing.push_back( bigramEntry.second );
			}
		}
		
		// Distribution for bigrams based on that probability
		std::discrete_distribution<int> bigramDistributionFollowing( bigramFrequencyVectorFollowing.begin(), bigramFrequencyVectorFollowing.end() );
	
		unsigned int bigramIndex = bigramDistributionFollowing( generator );
		previousToken = bigramVectorFollowing[bigramIndex].two;
		std::cout << previousToken << " ";
	}
	
	std::cout << '\n';
	
	
	/*
	// Calculate now the ngram counts
	std::map<Unigram, std::pair<unsigned int, std::shared_ptr<Unigram>>> unigramDictionary;
	std::map<Bigram, std::pair<unsigned int, std::shared_ptr<Bigram>>> bigramDictionary;
	std::map<Trigram, std::pair<unsigned int, std::shared_ptr<Trigram>>> trigramDictionary;
	
	for( auto it = std::begin( words ); it != std::end( words ); ++it ) {
		// Unigrams
		///////////////////////////////////////////////////////////////
		// Create a smart pointer to unigram on the heap
		std::shared_ptr<Unigram> sharedUnigramPointer( new Unigram );
		// Set unigram.one to the iterator dereferenced
		sharedUnigramPointer->one = *it;
		Unigram unigram = *sharedUnigramPointer;
		// Increment the count of the unigram
		unigramDictionary[unigram].first++;
		// Check if there is not yet an entry for unigram. If there is not, the pointer need be updated
		if( !unigramDictionary.count(unigram) ) {
			unigramDictionary[unigram].second = sharedUnigramPointer;
		}
		///////////////////////////////////////////////////////////////
		
		// Bigrams
		///////////////////////////////////////////////////////////////
		// Create a smart pointer to bigram on the heap
		std::shared_ptr<Bigram> sharedBigramPointer( new Bigram );
		// Set bigram.one, bigram.two to the iterator dereferenced
		sharedBigramPointer->one = *it;
		sharedBigramPointer->two = *std::next(it);
		Bigram bigram = *sharedBigramPointer;
		// Increment the count of the bigram
		bigramDictionary[bigram].first++;
		// Check if there is not yet an entry for bigram. If there is not, the pointer need be updated
		if( !bigramDictionary.count(bigram) ) {
			bigramDictionary[bigram].second = sharedBigramPointer;
		}
		///////////////////////////////////////////////////////////////
		
		// Trigrams
		///////////////////////////////////////////////////////////////
		// Create a smart pointer to trigram on the heap
		std::shared_ptr<Trigram> sharedTrigramPointer( new Trigram );
		// Set trigram.one, trigram.two, trigram.three to the iterator dereferenced
		sharedTrigramPointer->one = *it;
		sharedTrigramPointer->two = *std::next(it);
		sharedTrigramPointer->three = *std::next(it, 2);
		Trigram trigram = *sharedTrigramPointer;
		// Increment the count of the trigram
		trigramDictionary[trigram].first++;
		// Check if there is not yet an entry for trigram. If there is not, the pointer need be updated
		if( !trigramDictionary.count(trigram) ) {
			trigramDictionary[trigram].second = sharedTrigramPointer;
		}
		///////////////////////////////////////////////////////////////
	}
	// Now that maps are taken care of, we need to take care of vectors
	// Define vector of dictionary iterators so we can access randomly
	std::vector<std::pair<const Unigram, std::pair<unsigned int, std::shared_ptr<Unigram>>>> unigramPointers;
	unsigned int iteratorCounter {0};
	for( auto it = std::begin( unigramDictionary ); it != std::end( unigramDictionary ); ++it ) {
		iteratorCounter++;
		unigramPointers.push_back( *it );
	}
	
	for( unsigned int i = 0; i < 10; i++ ) {
		std::cout << (unigramPointers[iteratorCounter].second.second)->one << '\n';
	}
	*/
	
	//std::cout << unigramPointers[0]->first.one << '\n';
	
	
	
	// std::vector<std::pair<Bigram, unsigned int>> bigramDictionary;
	// std::vector<std::pair<Trigram, unsigned int>> trigramDictionary;
	
	
	for( int i = 0; i < 10; i++ ) {
		
	}
	
	// for( auto it = std::begin( unigramDictionary ); it != std::end( unigramDictionary ); ++it ) {
		// std::cout << it->first.one << " : " << it->second.first << '\n';
	// }
	
	// for( auto it = std::begin( bigramDictionary ); it != std::end( bigramDictionary ); ++it ) {
		// std::cout << it->first.one << " " << it->first.two << " : " << it->second.first << '\n';
	// }
	
	// for( auto it = std::begin( trigramDictionary ); it != std::end( trigramDictionary ); ++it ) {
		// std::cout << it->first.one << " " << it->first.two << " " << it->first.three << " : " << it->second.first << '\n';
	// }
	
	std::cout << "Unigram entries: " << unigramDictionary.size() << ", bigram entries: " << bigramDictionary.size() << ", trigram entries: " << trigramDictionary.size() << '\n';
	
	return 0;
}