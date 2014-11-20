// LinearSolver.h: Schnittstelle f�r die Klasse LinearSolver.
//
//////////////////////////////////////////////////////////////////////

#ifndef LINEARSOLVER_H
#define LINEARSOLVER_H


#include "AbstractSolver.h"

namespace fesolv {

class LinearSolver : public AbstractSolver  
{
public:
	LinearSolver(Model* model);
	~LinearSolver();

	void Solve();

private:
	void ComputeStiffnessMatrix();
	void SimplifyStiffnessMatrix();
	void ComputeSystemReactionVector();
};

} //end namespace

#endif 
