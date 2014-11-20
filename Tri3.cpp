// Tri3.cpp: Implementierung der Klasse Tri3.
//
//////////////////////////////////////////////////////////////////////

#include "Tri3.h"
#include "Material.h"
#include "Node.h"
#include "Material.h"
#include <cmath>

namespace fesolv {

Tri3::Tri3(Model* model, FEint  number, FEint node1, FEint node2, FEint node3, FEdouble thickness, FEint mat):Element(model,number)
{
	_numberofnodes = 3;
	_dimension = 2;
	_thickness =thickness;
	_node1 = node1;
	_node2 = node2;
	_node3 = node3;
	_mat = mat;
}

Tri3::~Tri3()
{

}

void Tri3::GetStiffnessMatrix(Matrix<FEdouble>* S)
{
	Node* node1 = _model->GetNode(_node1);
	Node* node2 = _model->GetNode(_node2);
	Node* node3 = _model->GetNode(_node3);
	Matrix<FEdouble>* Fe = new Matrix<FEdouble>(3,6);
	(*Fe)(0,0) = (*Fe)(2,1) = node2->GetY()-node3->GetY();
	(*Fe)(2,0) = (*Fe)(1,1) = -(node2->GetX()-node3->GetX());
	(*Fe)(0,2) = (*Fe)(2,3) = node3->GetY()-node1->GetY();
	(*Fe)(2,2) = (*Fe)(1,3) = -(node3->GetX()-node1->GetX());
	(*Fe)(0,4) = (*Fe)(2,5) = node1->GetY()-node2->GetY();
	(*Fe)(2,4) = (*Fe)(1,5) = -(node1->GetX()-node2->GetX());

	FEdouble F = 0.5*static_cast<FEdouble>(fabs(
		node1->GetX()*(node2->GetY()-node3->GetY())+
		node2->GetX()*(node3->GetY()-node1->GetY())+
		node3->GetX()*(node1->GetY()-node2->GetY())
		));

	(*Fe)*=1/(2*F);

	Material* mat = _model->GetMaterial(_mat);

	FEdouble D = mat->GetEmodul()*_thickness/(1-(mat->GetNue()*mat->GetNue()));

	Matrix<FEdouble>* E = new Matrix<FEdouble>(3);
	(*E)(0,0) = (*E)(1,1) = D;
	(*E)(1,0) = (*E)(0,1) = D*mat->GetNue();
	(*E)(2,2) = 0.5*D*(1-mat->GetNue());

	Matrix<FEdouble> K = (*E)*(*Fe);
	Fe->Transpose();

	(*S) = (*Fe)*K;
	(*S)*=F;
	
}

void Tri3::GetStiffnessNumberVector(IntVector* vec)
{
	vec->resize(6,0);
	
	(*vec)[0]=_node1;
	(*vec)[1]=_node1;
	(*vec)[2]=_node2;
	(*vec)[3]=_node2;
	(*vec)[4]=_node3;
	(*vec)[5]=_node3;

	NumberToInsertPosition(vec);
}

} //end namespace