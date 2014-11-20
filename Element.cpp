// Element.cpp: Implementierung der Klasse Element.
//
//////////////////////////////////////////////////////////////////////

#include "Element.h"
#include <cmath> //sqrt
#include <cstddef> //size_t
#include <iomanip>

namespace fesolv {

Element::Element(Model* model, FEint number)
{
	_model = model;
	_number = number;
}

Element::~Element()
{

}

void Element::NumberToInsertPosition(IntVector* vec)
{
	nodes* node = _model->GetNodes();
	FEint pos;
	FEint nodeidx = 0;
	const_node_iterator iter;
	
	for(FEint i = 0; i < static_cast<FEint>(vec->size()); i++){
		
		pos = 0;
		iter = node->begin();

		for ( ; iter != node->end(); iter++ )
		{
			if((*iter)->GetNumber() == (*vec)[i]){
				if(nodeidx == (*vec)[i]){
					pos++;
					//3D not supported yet
					/*if(i > 1 && (*vec)[i-2] == (*vec)[i])
						pos++;*/
				}
				nodeidx = (*vec)[i];
				(*vec)[i] = pos;
				pos++;
				break;
			} else {
				pos+=GetDimension();
			}	
		}

	}

}

std::ostream& operator<<(std::ostream& fout, Element* element)
{
	Matrix<FEdouble>* stiffnessmatrix = new Matrix<FEdouble>(0);
	element->GetStiffnessMatrix(stiffnessmatrix);
	fout << "Element Stiffnessmatrix: " << element->GetNumber() << std::endl;
	fout << stiffnessmatrix << std::endl;
	delete stiffnessmatrix;
	return fout;
}

std::ostream& operator<<(std::ostream& fout, DoubleVector* vec)
{

	for(FEint i=0;i< static_cast<FEint>(vec->size());i++) {
		fout << std::setprecision(4) << std::right << std::scientific << std::setw(12) << (*vec)[i] << std::endl;
	}
	
	return fout;
}

std::ostream& operator<<(std::ostream& fout, Matrix<FEdouble>* mat)
{

	FEint rows = mat->GetNumberOfRows();
	FEint columns = mat->GetNumberOfColumns();

	for(FEint i=0;i<rows;i++) {
		for(FEint j=0;j<columns;j++) {
			fout << std::setprecision(4) << std::right << std::scientific << std::setw(12) << (*mat)(i,j) << " ";
		}
		fout << std::endl;
	}

	return fout;
}

std::ostream& operator<<(std::ostream& fout, Matrix<FEdouble> mat)
{

	FEint rows = mat.GetNumberOfRows();
	FEint columns = mat.GetNumberOfColumns();

	for(FEint i=0;i<rows;i++) {
		for(FEint j=0;j<columns;j++) {
			fout << std::setprecision(4) << std::right << std::scientific << std::setw(12) << mat(i,j) << " ";
		}
		fout << std::endl;
	}

	return fout;
}

} //end namespace