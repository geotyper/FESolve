
#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <valarray>

#include "Fe.h"

#include "Model.h"
#include "Matrix.h"

namespace fesolv {

using namespace fe;

using femath::Matrix;
using femath::IntVector;
using femath::DoubleVector;

class Element  
{
public:
	Element(Model* model, FEint number);
	virtual ~Element();
	
	FEint GetNumber() const { return _number;}
	FEint GetNumberOfNodes() const { return _numberofnodes;}
	FEint GetDimension() const { return _dimension;}
	
	//virual Part
	virtual void GetStiffnessMatrix(Matrix<FEdouble>* mat)=0;
	virtual void GetStiffnessNumberVector(IntVector* vec)=0;
	
protected:
	void NumberToInsertPosition(IntVector* vec);

	FEint _numberofnodes;
	FEint _number;
	FEint _dimension;
	Model* _model;
};


std::ostream& operator<<(std::ostream& fout, Element* element);
std::ostream& operator<<(std::ostream& fout, DoubleVector* vec);
std::ostream& operator<<(std::ostream& fout, Matrix<FEdouble>* mat);
std::ostream& operator<<(std::ostream& fout, Matrix<FEdouble> mat);

}//end namespace

#endif 