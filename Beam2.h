// Beam2.h: Schnittstelle für die Klasse Beam2.
//
//////////////////////////////////////////////////////////////////////

#ifndef BEAM2_H
#define BEAM2_H

#include "Fe.h"
#include "Element.h"

namespace fesolv {

using namespace fe;

class Beam2 : public Element  
{
public:
	Beam2(Model* model, FEint number, FEint node1, FEint node2, FEdouble area, FEint mat);
	~Beam2();

	void GetStiffnessMatrix(Matrix<FEdouble>* S);
	void GetStiffnessNumberVector(IntVector* vec);

private:
	FEint		_node1,_node2;
	FEint		_mat;
	FEdouble	_area;
};

} //end namespace
#endif 


