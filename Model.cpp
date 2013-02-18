#include "Model.h"

//Constructors 
Model::Model(void){
} 

Model::Model(Lattice& initial){
	state = &initial;
	Lattice save = *state; 
	Flow fsave(save,true);
	system_states = fsave;
} 

//Methods
//Return a pointer to a lattice of the current model state
Lattice* Model::getLattice(void) {
	return state; 
}
//Print current model state to cout
void Model::print(void){ 
	state->print(); 
}
//Print current model state to file
void Model::filePrint(bool ishuman){
	state->filePrint(ishuman,false);
}
//Print all model states to file/entire flow object - merge to filePrint (overload)
void Model::filePrintAll(void){
	Lattice toprint;
	for (int i = 0; i < system_states.numStates(); ++i) {
		toprint = system_states.getLattice(i); //get a specific element
		if (i == 0) { //print this specific element
			toprint.filePrint(false,true);
		}
		else {
			toprint.filePrint(false,false); 
		}
	} //may be possible to redo this with pointers. only useful if we need to manage memory more
}
//Returns the number of time steps taken
int Model::timeSize(void){
	return system_states.numStates(); 
} 
//return the current gas state at a time t as a lattice
Lattice Model::getLatT(int t){
	return system_states.getLattice(t); 
}