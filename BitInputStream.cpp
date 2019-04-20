/**
 * Jihoon You
 * jiy043
 * A97097001
 * CSE100
 * PA3
 * */
#include "BitInputStream.h"
#include <iostream>
using namespace std;

void BitInputStream::fill()
	{
		buf = in.get();
		nbits = 0;
	}

int BitInputStream::readBit()
{
	//If all bits in the buffer are read, fill the buffer fisrt
	if(nbits == 8)
	{
		fill();
	}

		//get the next unread bit from the bitwise buffer
		int nextBit = buf & (1 <<(7 - nbits));
		nextBit = (nextBit >> (7 - nbits)) & 1;
		//increament the number of bits we have read from the bitwise buffer
		nbits++;

		//return the bit we just read
		return nextBit;


}
