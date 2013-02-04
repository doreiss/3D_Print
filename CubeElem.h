#pragma once

#include <iostream> 

class CubeElem 
{ 
public:
	/* 
	This enumerated type defines the property of whether the CubeElem
	exists or not.  This will allow for additional types in the future.  
	*/
	enum CubeType {
		Empty, 
		Full
	};

	//Constructors: 
	
	//Default Constructor
	CubeElem(CubeType init = Empty);
	
	
	//Methods:

	//Get the CubeType
	CubeType getType(void); 
	//Set the CubeType
	void setType(CubeType); 
	//Assigns a given face neighbour to this cube
	void setFaceNeighbour(int,CubeElem&);
	//True if a given neighbour is empty
	bool isNEmpty(int); 
	//True if a given neighobur is null 
	bool isNNull(int); 
	//Returns true if CubeType is Empty otherwise false
	bool isEmpty(void);
	//Sets all face neighbours of this cube to null
	void setNullFaceNeighbours(void); 

private: 

	// Empty or Full
	CubeType type;
	// Pointers to neighbouring CubeElem as defined below 
	CubeElem* face_neighbours[6];

};

/*

Face Definitions 
			
				 Top # 1
					|
					|
					v
				  ________
				 /|		 /|
				/_______/ |
 Left # 2 --->  | |	____| |  <--- Right # 0
				| / 	| /
				|_______|/
		    
					^
					|
					|
			   Bottom # 3

AND Front # 4,  Back # 5 
					
*/