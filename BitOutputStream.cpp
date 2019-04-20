/**
 * Jihoon You
 * jiy043
 * A97097001
 * CSE100
 * PA3
 * */
#include "BitOutputStream.h"
#include <iostream>

using namespace std;

void BitOutputStream::flush()
	{
		out.put(buf);
		out.flush();
		buf = nbits = 0;
	}

void BitOutputStream::writeBit(int i)
	{
		//flush the bitwise buffer if it is full
		if(nbits == 8) 
		{
			flush();
		}

	//clearing bits except the lesat significant bit
	int temp = i << 7;
	//moving back the lesat signiicant bit to it's original place 
	buf =  buf | (temp >> (nbits));	
	//increament the number of bits in out bitwise buffer
	nbits++;
	}


