/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <fstream>
#include "console.h"
#include "vector.h"
#include "map.h"
#include "filelib.h"
#include "random.h"
#include "simpio.h"
using namespace std;

void read(Map<string,Vector<char>>& map, int& order);
string findMostFrequent(Map<string,Vector<char>>& map);
string write(Map<string,Vector<char>>& map, string mostSeed, int order);


int main() {
    // [TODO: fill with your code]

	// initialize a map which represents markov model and initialize the order
	Map<string,Vector<char>> map;
	int order;
	
	read(map, order);
	 
	// find what seed was the most frequently used
	string mostSeed = findMostFrequent(map);
	
	// now comes the writing
	string outText = write(map, mostSeed, order);
	cout << outText << endl;
    return 0;
}
// this method recieves method, order and updates the map with seed-letter info
void read(Map<string,Vector<char>>& map, int& order){
	// Opening the file and get seed order
	ifstream input;
	string filename = promptUserForFile(input, "Enter input file name: ");
	// get the Markov order
	order = getInteger("Enter the Market order [1 - 10]: ");
	while(!(order > 0 && order <= 10)){
		cout << "The value is out of the range." << endl;
		order = getInteger("Enter the Market order [1 - 10]: ");
	}
	
	string seed;
	// itterate through the input char-by-char and get seeds and following chars(peeks)
	while (input.good()) {
		// get the seed
		for(int i = 0; i < order; i++) {
			char ch = input.get();
			seed = seed + ch;
		}
		
		// check what letter comes after the seed
		char peek = (char)input.peek();

		// update the map: update the letters vector and put it in the map
		// letters vector stores all the letters that come after given seed
		Vector<char> lettersVector;
		if (map.containsKey(seed)) {
			lettersVector = map.get(seed);
		} 
		lettersVector.add(peek);
		map.put(seed, lettersVector);
		
		for(int i = 0; i < order - 1; i++) {
			input.unget();
		}

		seed = ""; // clear the seed string for next loop
	}
	input.close();
	//cout << map.toString() << endl; // we got the full Markov model (map) 
}
// itterate through map and return most frequent seed, a key which will be followed by longest char vector
string findMostFrequent(Map<string,Vector<char>>& map){
	// find what seed was the most frequently used
	int maxSize = 0;
	string mostSeed;
	foreach (string seed in map) { // iterate through map and get the keys
		if (map[seed].size() >= maxSize){
			maxSize = map[seed].size();
			mostSeed = seed;
		}
	}
	return mostSeed;
}
// random writer using Markov model
string write(Map<string,Vector<char>>& map, string mostSeed, int order){
	string outText = mostSeed; // start with the most frequent seed
	int seedPointer = 0;

	while(outText.length() < 2000){
		Vector<char> seedLetters = map[outText.substr(seedPointer, order)];
		// if given the seed, there is no letter, that can be written after that seed, just stop writing
		if (seedLetters.size() == 0){
			break;
		}
		char nextLetter = seedLetters[randomInteger(0, seedLetters.size()-1)];
		outText = outText + nextLetter; // instead of 'd ' we should get random char from markov model
		seedPointer++;
	}
	return outText;
}