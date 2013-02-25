#pragma once
#include "Model.h"

class DynGasModel : public Model {
	//constructors
	DynGasModel() : Model() {}
	DynGasModel(Lattice& l) : Model(l) {}

	//iterate method for the dynamic gas model
	void iterate(void) {
	}
} ;