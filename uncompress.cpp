/**
 * Jihoon You
 * jiy043
 * A97097001
 * CSE100
 * PA3
 * */
#include "HCTree.h"
#include "BitInputStream.h"
#include <vector>
#include <fstream>
#include <ostream>


using namespace std;


int main(int argc, const char * argv[]){

	//check arguments
	if(argc != 3)
	{
		cout << "Incorrect number of arguments" << endl;
		return -1;
	}

	//declarations
	string infile, outfile;
	vector<int> freqs (256, 0);
	int c = 0;
	ifstream in;
	ofstream out;
	HCTree tree;
	int remainder = 0;
	char leaveCount = 0;
	BitInputStream inn(in);
	int filesize =0;


	infile = argv[1];
	outfile = argv[2];
	
	//open the input file
	in.open(infile, ios::binary);
	
	if(in.peek() == EOF)
	{
		cout << "input file is empty"<< endl;
		return 0;
	}



	/*	for(int i = 0; i < 256; i++)
	{
		in.read((char*)&c, sizeof(int) );
		//in >> c;
		if(!in.eof() && c != 0)
		{
			freqs[i] = c;
			remainder += c;
		}
	}
	in.get();*/

	//get filesize from the header file
	in.read((char*)&filesize, sizeof(int) );
	//get laeveCount from the header file
	in.read((char*)&leaveCount, sizeof(char) );

	//open the output file for writing
	out.open(outfile);

	//building tree from the header file
	tree.setRoot(tree.decodeHeader(inn, leaveCount));

	

	//Using the Huffman coding tree, decode the bits from the input file into the appropriate sequence of bytes, writing them to the output file.
	for(int i = 0; i < filesize; i++)
	{

		byte sym = tree.decode(inn);
		out.write((char*)&sym ,1 );
	}

	//close the input and output files
	in.close();
	out.close();
}
