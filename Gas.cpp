#include "Gas.h"
using namespace std;

Gas::Gas(void)
{
}

Gas::Gas(Lattice initial)
{
	state = initial;
}

void Gas::iterate(void)
{
	//Add rules based on Appendix B from Jensen's book
}