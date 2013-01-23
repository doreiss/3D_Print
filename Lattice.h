#pragma once
#include <iostream>
#include <vector> 
class Lattice
{
public: 
	Lattice(void);
	Lattice(int, int, int);
	Lattice(char*);
	
	
private: 
	vector < vector < int > > values; 
};
