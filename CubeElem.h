#pragma once

#include <vector>
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
	CubeElem(CubeType = Empty);
private: 

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