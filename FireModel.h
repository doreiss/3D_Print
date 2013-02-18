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
		Lattice* old = new Lattice(state->rowSize(),state->colSize(),LatElem::Empty);
		old->insertSubLattice(*state,0,0); 

		for(int i = 0; i < state->rowSize(); ++i) { 
			for(int j = 0; j < state->colSize(); ++j) {

				LatElem* oldelem = old->getElement(i,j);
				LatElem* elem = state->getElement(i,j);

				LatElem::LatType current_type = oldelem->getValue();
				bool update = false;
				bool ignite = false;

				switch(current_type) {

				case LatElem::Empty:
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
				case LatElem::Full:
					for (int k = 0; k < 8; ++k) {
						LatElem* neighbour = oldelem->getNeighbour(k);
						if (neighbour != NULL) {
							if(neighbour->getValue() == LatElem::Burning) {
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
						int strike_prob = 10;
						strike_prob *= lightning;
						if (strike < strike_prob) {
							elem->setValue(LatElem::Burning);
							elem->setBurnTime(burning_time);
						}
					}
					break;

				case LatElem::Burning:
					int burn_time = oldelem->getBurnTime();
					burn_time--;
					if (burn_time == 0) {
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
		}
	}
	int random(void) {
		int number = rand() % 1000;
		return number;
	}	
private: 
	int growth; 
	int lightning; 
	int burning_spread; 
	int burning_time;
};

