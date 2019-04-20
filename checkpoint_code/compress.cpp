#include "HCTree.h"
#include <vector>
#include <fstream>
#include <ostream>
using namespace std;


int main(int argc, const char * argv[]){

	//check arguments
	if(argc != 3)
	{
		cout << "Incorrect number of arguments" <<endl;
		return -1;
	}

	//declarations
	string infile, outfile;
	vector<int> freqs (256, 0);
	unsigned char c; 
	HCTree tree;
	ifstream in;
	ofstream out;
	int check;

	infile = argv[1];
	outfile = argv[2];


	//open input file
	in.open(infile, ios::binary);

	//Invalid text file
	if(!in)
	{
		cout << "input infile is invalid" << endl;
		return 0;
	}
	//empty text file
	if(in.peek() == EOF)
	{
		cout << "input infile is empty" <<endl;
		return 0;

	}
	

	//Read bytes from the file. Count the number of occurrences of each byte value
	while(!in.eof())
	{
		c = (unsigned char)in.get();
		if(!in.eof())
		{
			freqs[(int)c]++;	
		}
	}



	//reseting the flag
	in.clear();                 
	in.seekg(0, ios::beg); 
	
	//close the file
	in.close();



	//Use the byte counts to construct a Huffman coding tree. Each unique byte with a non-zero count will be a leaf node in the Huffman tree.
	tree.build(freqs);	

	//open the output file for writing
	out.open(outfile);

	//Write enough file header to the output file
	for(int i = 0; i < freqs.size(); i++)
	{
		out << freqs[i] << endl;
	}



	//open the input file for reading, again
	in.open(infile, ios::binary);

	////Using the HCTree, translate each byte from the input file into its code.
	while(!in.eof())
	{
		c = (unsigned char)in.get();
		if(!in.eof())
		{
			tree.encode(c, out);
		}
	}
	//close in and out
	in.close();
	out.close();

}
