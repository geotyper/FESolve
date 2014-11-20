// LinearSolver.cpp: Implementierung der Klasse LinearSolver.
//
//////////////////////////////////////////////////////////////////////
#include "Matrix.h"

#include "Fe.h"

#include "LinearSolver.h"
#include <vector>

namespace fesolv {
using namespace fe;


LinearSolver::LinearSolver(Model* model):AbstractSolver(model)
{

}

LinearSolver::~LinearSolver()
{

}

void LinearSolver::Solve()
{
	ComputeStiffnessMatrix();
	SimplifyStiffnessMatrix();

	DoubleVector* temp = new DoubleVector;
	(*temp)=(*_d);

	Matrix<FEdouble>* tempMat = new Matrix<FEdouble>(0);
	*tempMat = *_systemstiffnessmatrix;

	Matrix<FEdouble>::CholeskySolveLGS(_systemstiffnessmatrix,_d);
	
	*_systemstiffnessmatrix = *tempMat;
	(*_displacement)=(*_d);
	(*_d)=(*temp);

	delete tempMat;
	delete temp;

	ComputeSystemReactionVector();
}

void LinearSolver::ComputeSystemReactionVector()
{

	Matrix<FEdouble>* tempStiffness = new Matrix<FEdouble>;
	nodes* node = _model->GetNodes();
	FEint dimension = node->size();
	dimension += dimension;
	tempStiffness->SetDimension(dimension,dimension);

	Matrix<FEdouble>* elementMatrix = new Matrix<FEdouble>(0);
	IntVector* insertVector = new IntVector(0);
	elements* elem = _model->GetElements();
	const_element_iterator elemIter = elem->begin();
	for ( ; elemIter != elem->end(); elemIter++ )
	{
		(*elemIter)->GetStiffnessMatrix(elementMatrix);
		(*elemIter)->GetStiffnessNumberVector(insertVector);
		tempStiffness->Insert(elementMatrix,insertVector);
	}
	delete insertVector;
	delete elementMatrix;

	DoubleVector* uglob = new DoubleVector(0.0,dimension);

	const_node_iterator nodeIter = node->begin(); 
	FEint i = 0;
	FEint j = 0;
	for ( ; nodeIter != node->end(); nodeIter++ )
	{
		if((*nodeIter)->GetXConstrain() != 1){
			(*uglob)[i]=(*_displacement)[j];
			j++;
		}
		i++;
		if((*nodeIter)->GetYConstrain() != 1){
			(*uglob)[i]=(*_displacement)[j];
			j++;
		}
		i++;
	}

	(*_reactionforce) = (*tempStiffness)*(*uglob);

	delete uglob;
	delete tempStiffness;
}

void LinearSolver::SimplifyStiffnessMatrix()
{
	std::vector<FEint>* cutV = new std::vector<FEint>(0);
	nodes* node = _model->GetNodes();
	const_node_iterator nodeIter = node->begin(); 
	FEint i = 0;
	for ( ; nodeIter != node->end(); nodeIter++ )
	{
		if((*nodeIter)->GetXConstrain() == 1)
			cutV->push_back(i);
		i++;
		if((*nodeIter)->GetYConstrain() == 1)
			cutV->push_back(i);
		i++;
	}
	IntVector* cut = new IntVector(cutV->size());
	for (FEint j = 0; j < static_cast<FEint>(cutV->size()); j++ )
	{
		(*cut)[j] = (*cutV)[j];
	}
	
	DoubleVector* new_d = new DoubleVector((_d->size())-(cutV->size()));
	
	FEint m = 0;
	FEint h = 0;
	for (FEint k = 0; k < static_cast<FEint>(_d->size()); k++ )
	{
		if(k != (*cut)[m]){
			(*new_d)[h] = (*_d)[k];
			h++;
		} else {
			m++;
		}
		
	}

	(*_d) = (*new_d);
	
	_systemstiffnessmatrix->Cut(cut);
	
	delete new_d;
	delete cutV;
	delete cut;
}

void LinearSolver::ComputeStiffnessMatrix()
{
	
	nodes* node = _model->GetNodes();

	FEint dimension = node->size();
	dimension += dimension;
	_d->resize(dimension,0.0);
	const_node_iterator nodeIter = node->begin(); 
	FEint i = 0;
	for ( ; nodeIter != node->end(); nodeIter++ )
	{
		(*_d)[i] = (*nodeIter)->GetXForce();
		i++;
		(*_d)[i] = (*nodeIter)->GetYForce();
		i++;
	}
	_systemstiffnessmatrix->SetDimension(dimension,dimension);


	Matrix<FEdouble>* elementMatrix = new Matrix<FEdouble>(0);
	IntVector* insertVector = new IntVector(0);
	elements* elem = _model->GetElements();
	const_element_iterator elemIter = elem->begin();
	for ( ; elemIter != elem->end(); elemIter++ )
	{
		(*elemIter)->GetStiffnessMatrix(elementMatrix);
		(*elemIter)->GetStiffnessNumberVector(insertVector);
		_systemstiffnessmatrix->Insert(elementMatrix,insertVector);
	}
	delete insertVector;
	delete elementMatrix;

	

}

} //end namespace