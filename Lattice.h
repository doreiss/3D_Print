#pragma once
#include <iostream>
#include <vector> 
using namespace std; 
class Lattice
{
public: 
	Lattice(void);
	Lattice(int, int, int);
	Lattice(char*);
	void setElement(int, int, int);
	int	getElement(int, int);
	void setSubLattice(int,int,int,int,int);
	void print(void); 
private: 
	vector<vector<int>> values; 
};