// Beam2.cpp: Implementierung der Klasse Beam2.
//
//////////////////////////////////////////////////////////////////////

#include "Beam2.h"
#include <cmath>

namespace fesolv {


Beam2::Beam2(Model* model, FEint number, FEint node1, FEint node2, FEdouble area, FEint mat):Element(model,number)
{
	_node1 = node1;
	_node2 = node2;
	_mat = mat;
	_area = area;
}

Beam2::~Beam2()
{

}

void Beam2::GetStiffnessMatrix(Matrix<FEdouble>* S)
{
	Node* node1 = _model->GetNode(_node1);
	Node* node2 = _model->GetNode(_node2);
	Material* mat = _model->GetMaterial(_mat);

	FEdouble l = sqrt((node2->GetY()-node1->GetY())*(node2->GetY()-node1->GetY())+(node2->GetX()-node1->GetX())*(node2->GetX()-node1->GetX()));
	
	FEdouble c = (node2->GetX()-node1->GetX())/sqrt((node2->GetX()-node1->GetX())*(node2->GetX()-node1->GetX())+(node2->GetY()-node1->GetY())*(node2->GetY()-node1->GetY()));
	FEdouble s = sin(acos(c));

	S->SetDimension(4,4);

	(*S)(0,0) = (*S)(2,2) =  c*c;
	(*S)(1,0) = (*S)(0,1) = (*S)(2,3) = (*S)(3,2) =c*s;
	(*S)(0,3) = (*S)(3,0) = (*S)(1,2) = (*S)(2,1) = -c*s;
	(*S)(1,1) = (*S)(3,3) =  s*s;
	(*S)(0,2) = (*S)(2,0) = -s*s;
	(*S)(1,3) = (*S)(3,1) = -c*c;
	
	(*S)*=(mat->GetEmodul()*_area)/l;
}

void Beam2::GetStiffnessNumberVector(IntVector* vec)
{
	vec->resize(4,0);
	
	(*vec)[0]=_node1;
	(*vec)[1]=_node1;
	(*vec)[2]=_node2;
	(*vec)[3]=_node2;

	NumberToInsertPosition(vec);
}

}//end namespace