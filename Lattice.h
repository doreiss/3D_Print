#pragma once
#include <iostream>
#include <vector> 
class Lattice
{
public: 
	Lattice(void);
	Lattice(int, int, int);
	Lattice(char*);
	void setElement(int, int, int);
	void setSubLattice(int,int,int,int,int);
	
	
private: 
	vector<vector<int>> values; 
};
