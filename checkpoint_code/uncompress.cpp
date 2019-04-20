#include "HCTree.h"
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

	infile = argv[1];
	outfile = argv[2];



	//open the input file
	in.open(infile, ios::binary);

	//Read the file header at the beginning of the input file
	for(int i = 0; i < 256; i++)
	{
		in >> c;
		if(!in.eof() && c != 0)
		{
			freqs[i] = c;
			remainder += c;
		}
	}

	//Reconstruct the Huffman coding tree
	tree.build(freqs);

	//open the output file for writing
	out.open(outfile);

	//Using the Huffman coding tree, decode the bits from the input file into the appropriate sequence of bytes, writing them to the output file.
	for(int i = 0; i < remainder; i++)
	{
		out << (unsigned char)tree.decode(in);
	}		
	
	//close the input and output files
	in.close();
	out.close();
}
