/**
 * Jihoon You
 * jiy043
 * A97097001
 * CSE100
 * PA3
 * */
#include "HCNode.h"
/* Compare this HCNode and other for priority ordering.
 * Smaller count means higher priority
 * Use node symble for deterministic tiebreaking*/
bool HCNode::operator<(const HCNode& other)
{
	if(count != other.count)
	{
		return count > other.count;
	}
	/*if count is equal break tie by symbol*/
	return symbol > other.symbol;
}
