#pragma once
#include <iostream>
#include <vector> 
class Lattice
{
public: 
	Lattice(void); 
	~Lattice(void);
private: 
	vector < vector < int > > values; 
};