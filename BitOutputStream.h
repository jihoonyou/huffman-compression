/**
 * Jihoon You
 * jiy043
 * A97097001
 * CSE100
 * PA3
 * */
#ifndef BITOUTPUTSTREAM_H
#define BITOUTPUTSTREAM_H
#include <iostream>

using namespace std; 

class BitOutputStream {
	private:
		// bitwise buffer (one byte)
		unsigned char buf; 
		// number of bits that have been written to the bitwise buffer
		int nbits;
		// refernce to the bytewise output stream
		ostream & out;

	public:
		/** Initalize a BitOutputStream that will use
		 * the given osteram for output */
		BitOutputStream(ostream & os) : out(os), buf(0), nbits(0) {}

 		/** Send the buffer to the output, and claer it*/
		void flush();

		/**Write the least signficant bit of the argument to
 			* the bit buffer, and increment the bit buffer index.
 			* But flush the buffer first, if it is full*/
		void writeBit(int i);

	
};

#endif
