// AbstractSolver.cpp: Implementierung der Klasse AbstractSolver.
//
//////////////////////////////////////////////////////////////////////

#include "AbstractSolver.h"
#include <iomanip>

namespace fesolv {

AbstractSolver::AbstractSolver(Model* model)
{
	_model = model;
	_systemstiffnessmatrix = new Matrix<FEdouble>(0);
	_d = new DoubleVector;
	_displacement = new DoubleVector;
	_reactionforce = new DoubleVector;
}

AbstractSolver::~AbstractSolver()
{
	delete _d;
	delete _systemstiffnessmatrix;
	delete _displacement;
	delete _reactionforce;
}

void AbstractSolver::PrintData(std::ostream& out)
{

	out << "Model-Data:" << std::endl << std::endl;
	out << "Node: Number / X / Y / Z / Fx / Fy / Fz / Fxx / Fyy / Fzz / Cx / Cy / Cz / Cxx / Cyy / Czz" << std::endl;

	nodes* node = _model->GetNodes();
	const_node_iterator iterNode = node->begin();
	for ( ; iterNode != node->end(); iterNode++ )
	{
		out << std::setprecision(3) << std::right << std::fixed << std::setw(10) << (*iterNode)->GetNumber() << " "
			<< std::setprecision(3) << std::right << std::fixed << std::setw(10) << (*iterNode)->GetX() << " "
			<< std::setprecision(3) << std::right << std::fixed << std::setw(10) << (*iterNode)->GetY() << " "
			<< std::setprecision(3) << std::right << std::fixed << std::setw(10) << (*iterNode)->GetZ() << " "
			<< std::setprecision(3) << std::right << std::fixed << std::setw(10) << (*iterNode)->GetXForce() << " "
			<< std::setprecision(3) << std::right << std::fixed << std::setw(10) << (*iterNode)->GetYForce() << " "
			<< std::setprecision(3) << std::right << std::fixed << std::setw(10) << (*iterNode)->GetZForce() << " "
			<< std::setprecision(3) << std::right << std::fixed << std::setw(10) << (*iterNode)->GetXXForce() << " "
			<< std::setprecision(3) << std::right << std::fixed << std::setw(10) << (*iterNode)->GetYYForce() << " "
			<< std::setprecision(3) << std::right << std::fixed << std::setw(10) << (*iterNode)->GetZZForce() << " "
			<< std::setprecision(3) << std::right << std::fixed << std::setw(10) << (*iterNode)->GetXConstrain() << " "
			<< std::setprecision(3) << std::right << std::fixed << std::setw(10) << (*iterNode)->GetYConstrain() << " "
			<< std::setprecision(3) << std::right << std::fixed << std::setw(10) << (*iterNode)->GetZConstrain() << " "
			<< std::setprecision(3) << std::right << std::fixed << std::setw(10) << (*iterNode)->GetXXConstrain() << " "
			<< std::setprecision(3) << std::right << std::fixed << std::setw(10) << (*iterNode)->GetYYConstrain() << " "
			<< std::setprecision(3) << std::right << std::fixed << std::setw(10) << (*iterNode)->GetZZConstrain() << " "
			<< std::endl;
	}
	out << std::endl;

	out << "Element: Number / NumberOfNodes / Dimension" << std::endl;

	elements* elem = _model->GetElements();
	const_element_iterator iterElem = elem->begin();
	for ( ; iterElem != elem->end(); iterElem++ )
	{
		out << std::right << std::setw(5) << (*iterElem)->GetNumber() << " "
			<< std::right << std::setw(5) << (*iterElem)->GetNumberOfNodes() << " "
			<< std::right << std::setw(5) << (*iterElem)->GetDimension() << " "
			<< std::endl;
	}
	out << std::endl;

	out << "Material: Number / EModul / Nue" << std::endl; 

	materials* mat = _model->GetMaterials();
	const_material_iterator iterMat = mat->begin();
	for ( ; iterMat != mat->end(); iterMat++ )
	{
		out << std::right << std::setw(5) << (*iterMat)->GetNumber() << " "
			<< std::right << std::scientific << std::setw(5) << (*iterMat)->GetEmodul() << " "
			<< std::right << std::scientific << std::setw(5) << (*iterMat)->GetNue() << " "
			<< std::endl;
	}
	out << std::endl;
}

void AbstractSolver::PrintElementStiffnessMatrix(std::ostream& out)
{
	elements* elem = _model->GetElements();
	const_element_iterator iter = elem->begin();
	for ( ; iter != elem->end(); iter++ )
	{
		out << (*iter) << std::endl;
		
	}
}

void AbstractSolver::PrintSystemStiffnessMatrix(std::ostream& out)
{
	out << "SystemStiffnessMatrix:" << std::endl;
	out << _systemstiffnessmatrix << std::endl;
}

void AbstractSolver::PrintReactionForceVector(std::ostream& out)
{
	out << "SystemReactionForceVector:" << std::endl;
	nodes* node = _model->GetNodes();
	const_node_iterator nodeIter = node->begin(); 
	int i = 0;
	for ( ; nodeIter != node->end(); nodeIter++ )
	{
		if((*nodeIter)->GetXConstrain() == 1){
			out << "Node " << std::setprecision(6) << std::right << std::fixed << std::setw(5) 
				<< (*nodeIter)->GetNumber() << " x:" 
				<< std::setprecision(6) << std::right << std::scientific << std::setw(16) 
				<< (*_reactionforce)[i] << std::endl;
		}
		i++;
		if((*nodeIter)->GetYConstrain() == 1){
			out << "Node " << std::setprecision(6) << std::right << std::fixed << std::setw(5) 
				<< (*nodeIter)->GetNumber() << " y:" 
				<< std::setprecision(6) << std::right << std::scientific << std::setw(16) 
				<< (*_reactionforce)[i] << std::endl;
		}
		i++;
	}
	out << std::endl;
}

void AbstractSolver::PrintSystemDVector(std::ostream& out)
{
	out << "SystemDVector(Forces):" << std::endl;
	nodes* node = _model->GetNodes();
	const_node_iterator nodeIter = node->begin(); 
	int i = 0;
	for ( ; nodeIter != node->end(); nodeIter++ )
	{
		if((*nodeIter)->GetXConstrain() != 1){
			out << "Node " << std::setprecision(6) << std::right << std::fixed << std::setw(5) 
				<< (*nodeIter)->GetNumber() << " x:" 
				<< std::setprecision(6) << std::right << std::scientific << std::setw(16) 
				<< (*_d)[i] << std::endl;
			i++;
		}
		if((*nodeIter)->GetYConstrain() != 1){
			out << "Node " << std::setprecision(6) << std::right << std::fixed << std::setw(5) 
				<< (*nodeIter)->GetNumber() << " y:" << std::setprecision(6) 
				<< std::right << std::scientific << std::setw(16) 
				<< (*_d)[i] << std::endl;
			i++;
		}
	}
	out << std::endl;
}

void AbstractSolver::PrintSystemDisplacementVector(std::ostream& out)
{
	out << "SystemDisplacementVector:" << std::endl;
	nodes* node = _model->GetNodes();
	const_node_iterator nodeIter = node->begin(); 
	FEint i = 0;
	for ( ; nodeIter != node->end(); nodeIter++ )
	{
		if((*nodeIter)->GetXConstrain() != 1){
			out << "Node " << std::setprecision(6) << std::right << std::fixed << std::setw(5) 
				<< (*nodeIter)->GetNumber() << " x:" 
				<< std::setprecision(6) << std::right << std::scientific << std::setw(16) 
				<< (*_displacement)[i] << std::endl;
			i++;
		}
		if((*nodeIter)->GetYConstrain() != 1){
			out << "Node " << std::setprecision(6) << std::right << std::fixed << std::setw(5) 
				<< (*nodeIter)->GetNumber() << " y:" 
				<< std::setprecision(6) << std::right << std::scientific << std::setw(16) 
				<< (*_displacement)[i] << std::endl;
			i++;
		}
	}
	out << std::endl;
}


}//end namespace
