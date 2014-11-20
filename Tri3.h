// Tri3.h: Schnittstelle für die Klasse Tri3.
//
//////////////////////////////////////////////////////////////////////

#ifndef TRI3_H
#define TRI3_H

#include "Fe.h"
#include "Element.h"

namespace fesolv {
using namespace fe;

class Tri3 : virtual public Element  
{
public:
	Tri3(Model* model, FEint number, FEint node1, FEint node2, FEint node3, FEdouble thickness, FEint mat);
	~Tri3();
	
	void GetStiffnessMatrix(Matrix<FEdouble>* S);
	void GetStiffnessNumberVector(IntVector* vec);

private:
	FEdouble	_thickness;
	FEint		_node1,_node2,_node3;
	FEint		_mat;

};

} //end namespace
#endif 