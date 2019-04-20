/**
 * Jihoon You
 * jiy043
 * A97097001
 * CSE100
 * PA3
 * */
#include "HCTree.h"
#include "HCNode.h"
#include "BitOutputStream.h"
#include "BitInputStream.h"
#include <fstream>
#include <queue>
#include <iostream> 
#include <stack>
using namespace std;

HCTree::~HCTree(){
	deleteAll(root);
}

void HCTree::setRoot(HCNode* one){
	root = one;
}

HCNode* HCTree::getRoot(){
	return root;
}



void HCTree::build(const vector<int>& freqs){
	priority_queue<HCNode*,std::vector<HCNode*>,HCNodePtrComp> pq;

	for(int i = 0; i < freqs.size(); i++)
	{
		if(freqs[i] > 0)
		{
			//leaves[i] points to the leaf node containg byte i
			leaves[i] = new HCNode(freqs[i],i);
			pq.push(leaves[i]);
		}

	}
	//in case no freqs
	if(pq.empty())
	{
		cout << "No charecters in the original file" <<endl;
		return;
	}

	while(pq.size() > 1)
	{
		HCNode* child0 = pq.top();
		pq.pop();
		
		HCNode* child1 = pq.top();
		pq.pop();


		HCNode* parent = new HCNode(child0->count + child1->count, child0->symbol);
		parent->c0 = child0;
		parent->c1 = child1;


		child0->p = parent;
		child1->p = parent;

		pq.push(parent);
	}
	//root points to the root of the trie
	root = pq.top();	
}
//decoding header to build a tree
HCNode* HCTree::decodeHeader(BitInputStream& in, int leaveC){
	if(!leaveC)
	{
		return nullptr;
	}
	HCNode* newRoot = new HCNode(0,0);

	if(in.readBit() == 0)
	{
		newRoot->c0 = decodeHeader(in, leaveC);
		newRoot->c1 = decodeHeader(in, leaveC);
	}
	else
	{	
		for(int i = 7; i>=0; i--)
		{
			newRoot->symbol |= in.readBit() << i;
		}
		leaveC--;
	}
	return newRoot;
}


void HCTree::newHeader(HCNode* n, BitOutputStream& out) const{

	//write 0 not leave nodes 
	if(n->c0 || n->c1)
	{
		out.writeBit(0);
		newHeader(n->c0,out);
		newHeader(n->c1,out);
	}
	//write 1 leave nodes
	else
	{
		out.writeBit(1);
		for(int i = 0; i < 8; i++)
		{
			out.writeBit(1 & n->symbol >> (7 - i));
		} 	
	}
}





void HCTree::encode(byte symbol, BitOutputStream& out) const{
	HCNode* curr;
	stack<int> myStack;
	curr = leaves[symbol];
	
	if(curr == root)
	{
		myStack.push(0);
	}

	while(curr->p)
	{
		if(curr->p->c0 == curr)
		{
			myStack.push(0);
			curr = curr->p;
		}
		else if(curr->p->c1 == curr)
		{
			myStack.push(1);
			curr = curr->p;
		}
	}
	//write into out
	while(!myStack.empty())
	{
		out.writeBit(myStack.top());
		myStack.pop();
	}
	return;	
}
void HCTree::encode(byte symbol, ofstream& out) const{
	stack<int> myStack;	
	HCNode* curr;


	curr = leaves[symbol];


	//special case there is only one node, push 0
	if(curr == root)
	{
		myStack.push(0);		
	}

	while(curr->p)
	{
		if(curr->p->c0 == curr)
		{
			myStack.push(0);
			curr = curr->p;
		}
		else if(curr->p->c1 == curr)
		{
			myStack.push(1);
			curr = curr->p;
		}
	}
	//write into out
	while(!myStack.empty())
	{
		out << myStack.top();
		myStack.pop();
	}
	return;	

}

int HCTree::decode(BitInputStream& in) const{
	HCNode* curr = root;

	while(curr->c0 || curr->c1)
	{
		int c = in.readBit();
		if(c == 0)
		{
			curr = curr->c0;
		}
		else if(c == 1)
		{
			curr = curr->c1;
		}
	} 		

	return curr->symbol;


}

int HCTree::decode(ifstream& in) const{
	HCNode* curr = root;
		
	while(curr->c0 || curr->c1)
	{
		int c = in.get();
		if(c == '0')
		{
			curr = curr->c0;
		}
		else if(c == '1')
		{
			curr = curr->c1;
		}
	} 		
	
	return curr->symbol;
}

void HCTree::deleteAll(HCNode* n)
{
	if(n){
		//to leftmost child
		if(n->c0){
			deleteAll(n->c0);
		}
		//to rightmost child
		if(n->c1){
			deleteAll(n->c1);
		}
		delete n;
	}

}
