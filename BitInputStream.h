/**
 * Jihoon You
 * jiy043
 * A97097001
 * CSE100
 * PA3
 * */
#ifndef BITINPUTSTREAM_H
#define BITINPUTSTREAM_H
#include <iostream>

using namespace std;

class BitInputStream {
	private:
		//one byte buffer of bits
		char buf;
		//how many bits have been read from buf
		int nbits;
		//the input stream to use
		istream & in;	

	public:
		/** Initialize a BitInputStream that will use
		  * the given istream for input.
		  */
		BitInputStream(istream& is) : in(is), buf(0), nbits(8) {}

		/** Fill the buffer from the input */
		void fill();

		/** Read the next bit from the bit buffer.
		  * Fill the buffer from the input stream first if needed
		  * Return 1 if the bit read is 1;
		  * return 0 if the bit read is 0.
		  */
		int readBit();
		
};

#endif
