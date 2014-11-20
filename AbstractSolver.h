// AbstractSolver.h: Schnittstelle für die Klasse AbstractSolver.
//
//////////////////////////////////////////////////////////////////////

#ifndef ABSTRACTSOLVER_H
#define ABSTRACTSOLVER_H

#include "Fe.h"

#include "Model.h"
#include "Element.h"
#include <ostream> //print matrices

namespace fesolv {
using namespace fe;
using femath::Matrix;

class AbstractSolver  
{
public:
	AbstractSolver(Model* model);
	virtual ~AbstractSolver();

public:
	virtual void Solve()=0;
	
	void PrintData(std::ostream& out);
	void PrintElementStiffnessMatrix(std::ostream& out);
	void PrintSystemStiffnessMatrix(std::ostream& out);
	void PrintSystemDVector(std::ostream& out);
	void PrintSystemDisplacementVector(std::ostream& out);
	void PrintReactionForceVector(std::ostream& out);

protected:
	Model*	_model;
	Matrix<FEdouble>* _systemstiffnessmatrix;
	DoubleVector* _d;
	DoubleVector* _displacement;
	DoubleVector* _reactionforce;
};

} //end namespace
#endif
