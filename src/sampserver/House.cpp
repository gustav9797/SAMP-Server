#include "House.h"

House::House(void)
{
	pickups = new std::map<int, int>();
	interiors = new std::map<int, int>();
	inventory = new Inventory(16, 1, 65536);
	name = "Random house";
}


House::~House(void)
{

}
