#include "Polyhedron.h"

Polyhedron::Polyhedron() {
}

Polyhedron::Polyhedron(CubeArray cArr, double res, double cSize) {
	resolution = res; 
	for(int k = 0; k < cArr.stackSize(); k++) { 
		for(int i = 0; i < cArr.rowSize(); i++) { 
			for(int j = 0; j < cArr.colSize(); j++) {
				CubeElem* current = cArr.getCube(i,j,k);
				if(!(current->isEmpty())) {
					vector<int> emptyNInd;
					for(int nInd = 0; nInd < 6; nInd++) { 
						if(current->isNEmpty(nInd)) { 
							emptyNInd.push_back(nInd); 
						}
					}
					for(unsigned int vecInd = 0; vecInd < emptyNInd.size(); vecInd++) { 
						constructVF(i,j,k,emptyNInd[vecInd],cSize);
					}
				}
			} 
		} 
	}
} 

int Polyhedron::addVertex(Vec3& vertex) { 
	int nextIndex = vertSize(); 
	int index = nextIndex; 
	for(int i = 0; i < vertSize(); i++) { 
		if(!(vertex.withinResolution(vert[i],resolution))){
			index = i; 
			break;
		}
	}
	if(index == nextIndex) {
		vert.push_back(vertex);
	}
	return index; 
}

int Polyhedron::vertSize(void) { 
	return vert.size(); 
}

int Polyhedron::faceSize(void) { 
	return faces.size(); 
}

Vec3* Polyhedron::getVertex(int i) { 
	return &(vert[i]); 
}

Face* Polyhedron::getFace(int i) {
	return &(faces[i]); 
}

void Polyhedron::constructVF(int rowInd, int colInd, int stackInd, int faceInd, double cSize) { 
	double cx = (colInd*cSize);
	double cy = (rowInd*cSize);
	double cz = (stackInd*cSize); 
	vector < Vec3 > verticies; 
	for(int k = 0; k <= 1; k++) { 
		for (int j = 0; j <= 1; j++) { 
			for (int i = 0; i <= 1; i++) { 
				double newx = (cSize*i);
				newx += cx; 
				double newy = (cSize*j); 
				newy += cy; 
				double newz = (cSize*k); 
				newz += cz;  
				Vec3 v(newx,newy,newz);
				verticies.push_back(v); 
			}
		}
	}
	vector< Vec3* > f1, f2; 
	int a, b, c, d; //Pos of the 4 verticies of a square face
	switch(faceInd) { 
	case 0:
		a = addVertex(verticies[7]);
		b = addVertex(verticies[5]);
		c = addVertex(verticies[1]); 
		d = addVertex(verticies[3]);
		break; 
	case 1:
		a = addVertex(verticies[5]);
		b = addVertex(verticies[7]);
		c = addVertex(verticies[6]);
		d = addVertex(verticies[4]); 
		break; 
	case 2:
		a = addVertex(verticies[4]);
		b = addVertex(verticies[6]);
		c = addVertex(verticies[2]);
		d = addVertex(verticies[0]); 
		break;
	case 3:
		a = addVertex(verticies[0]);
		b = addVertex(verticies[2]);
		c = addVertex(verticies[3]);
		d = addVertex(verticies[1]); 
		break; 
	case 4: 
		a = addVertex(verticies[5]);
		b = addVertex(verticies[4]);
		c = addVertex(verticies[0]);
		d = addVertex(verticies[1]); 
		break; 
	case 5:
		a = addVertex(verticies[6]);
		b = addVertex(verticies[7]);
		c = addVertex(verticies[3]);
		d = addVertex(verticies[2]); 
		break; 
	default:
		cout << "not a valid faceInd ..." << endl; 
		break; 
	}
	vector<int> v1, v2; 
	v1.push_back(a); 
	v1.push_back(b); 
	v1.push_back(c); 
	v2.push_back(c); 
	v2.push_back(d); 
	v2.push_back(a); 
	Vec3 norm = normal_vector(faceInd);
	Face newF1(v1,norm); 
	Face newF2(v2,norm); 
	faces.push_back(newF1);
	faces.push_back(newF2);
}

void Polyhedron::print_stl(string filename, string objname) {
	ofstream myfile(filename);
	stl_head(myfile,objname); 
	stl_facet(myfile);
	stl_foot(myfile,objname);
	myfile.close();
} 

void Polyhedron::stl_head(ofstream& outfile, string objname) {
	if(outfile.good()) outfile << " solid " << objname << endl; 
}

void Polyhedron::stl_foot(ofstream& outfile, string objname) { 
	if(outfile.good()) outfile << " endsolid " << objname << endl;
}

void Polyhedron::stl_facet(ofstream& outfile) {
	if(outfile.good()) { 
		for(int i = 0; i < faceSize(); i++) {
			Face currentFace = faces[i];
			outfile << "facet normal "; 
			outfile << scientific << currentFace.getNormal().getX() << " "; 
			outfile << scientific << currentFace.getNormal().getY() << " ";
			outfile << scientific << currentFace.getNormal().getZ() << endl;
			outfile << " outer loop" << endl; 
			for(int j = 0; j < 3; j++) { 
				Vec3* v = getVertex(currentFace.getVerticies()[j]);
				outfile << "  vertex ";
				outfile << scientific << v->getX() << " ";
				outfile << scientific << v->getY() << " ";
				outfile << scientific << v->getZ() << endl;
			}
			outfile << " endloop" << endl;
			outfile << "endfacet" << endl; 
		}
	}
}

void Polyhedron::print_ply(string filename){
	ofstream myFile(filename);
	ply_head(myFile);
	ply_vertex(myFile); 
	ply_faces(myFile);
	myFile.close();
}

void Polyhedron::ply_head(ofstream& outfile) {
	if(outfile.good()) { 
		outfile << "ply" << endl; 
		outfile << "format ascii 1.0" << endl; 
		outfile << "element vertex " << vertSize() << endl;
		outfile << "property float x" << endl;
		outfile << "property float y" << endl;
		outfile << "property float z" << endl;
		outfile << "element face " << faceSize() << endl;
		outfile << "property list uchar int vertex_index" << endl; 
		outfile << "end_header" << endl; 
	}
}

void Polyhedron::ply_vertex(ofstream& outfile) { 
	if(outfile.good()) {
		for(int i = 0; i < vertSize(); i++) { 
			outfile << vert[i].getX() << " "
					<< vert[i].getY() << " " 
					<< vert[i].getZ() << endl; 
		}
	}
}

void Polyhedron::ply_faces(ofstream& outfile) {
	if(outfile.good()) {
		for(int i = 0; i < faceSize(); i++) {
			outfile << faces[i].getOrder() << " "; 
			for(int j = 0; j < faces[i].getOrder(); j++) { 
				outfile << faces[i].getVerticies()[j] << " "; 
			}
			outfile << endl; 
		}
	}
}