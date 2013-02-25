#pragma once
#include "Model.h"
#include <ctime>

class FireModel : public Model 
{
public: 
	//Constructors
	FireModel() : Model() {
		growth = 0; 
		lightning = 0; 
		burning_spread = 0; 
		burning_time = 0;
		srand(time(NULL));
	}
	FireModel(Lattice& l,int G = 60, int LB = 1, int BS = 75, int BT = 3) : Model(l) {
		growth = G; 
		lightning = LB; 
		burning_spread = BS; 
		burning_time = BT;
		srand(time(NULL));
	}

	//Iterate methods for the ForestFire
	void iterate(void) {
		cout << "here1" << endl; 
		//Create a copy of the state for reference
		Lattice* old = new Lattice(state->rowSize(),state->colSize(),LatElem::Empty);
		old->insertSubLattice(*state,0,0); 
		
		//Loop through the lattice
		for(int i = 0; i < state->rowSize(); ++i) { 
			for(int j = 0; j < state->colSize(); ++j) {

				LatElem* oldelem = old->getElement(i,j);
				LatElem* elem = state->getElement(i,j);

				LatElem::LatType current_type = oldelem->getValue();
				bool update = false;
				bool ignite = false;

				switch(current_type) {
				case LatElem::Empty: //If the current cell is empty
					for (int k = 0; k < 8; k++) { //look at neighbouring cells
						LatElem* neighbour = oldelem->getNeighbour(k);
						if(neighbour != NULL) {
							if (neighbour->getValue() == LatElem::Full) {
								update = true; //are any of the neighbouring cells occupied
							}
						}
					}
					if(update) {
						int grow = random();
						int grow_prob = 10;
						grow_prob *= growth;
						if (grow < grow_prob) {
							elem->setValue(LatElem::Full);
						}
					}
					break;
					
				case LatElem::Full: //If the current cell is full
					for (int k = 0; k < 8; ++k) { //Look at all its neighbours
						LatElem* neighbour = oldelem->getNeighbour(k);
						if (neighbour != NULL) {
							if(neighbour->getValue() == LatElem::Burning) { //Are any of its neighbours burning
								int ignite_chance = random();
								int ignite_prob = 10;
								ignite_prob *= burning_spread;
								if (ignite_chance < ignite_prob) {
									ignite = true;
								}
							}
						}
					}
					if(ignite) { 
						elem->setValue(LatElem::Burning);
						elem->setBurnTime(burning_time);
					}
					else {
						int strike = random();
						int strike_prob = 1;
						strike_prob *= lightning;
						if (strike < strike_prob) {
							elem->setValue(LatElem::Burning);
							elem->setBurnTime(burning_time);
						}
					}
					break;

				case LatElem::Burning: //If the current element burning
					int burn_time = oldelem->getBurnTime(); //How long has it been burning
					burn_time--;
					if (burn_time == 0) { //Is it time to stop burning?
						elem->setValue(LatElem::Empty);
					}
					elem->setBurnTime(burn_time);
					break;
				}
			}
		}
		Lattice save = *state; 
		system_states.addLattice(save);
	}
	void iterate(int n) { 
		for(int i = 0; i < n; i++) { 
			iterate();
			cout << i << endl;
		}
	}
	//Generates a random int between 1 - 1000
	int random(void) {
		int number = rand() % 1000;
		return number;
	}	
	//Generates a random int between 1 - max
	int random(int max) {
		int number = rand() % max; 
	}
private: 
	int growth; 
	int lightning; 
	int burning_spread; 
	int burning_time;
};

