#include "Model.h"
#include "AbstractReader.h"
#include "ReaderBuilder.h"
#include "FEMReader.h"
#include "Element.h"
#include "Compare.h"
#include "Predicate.h"

#include <iterator>
#include <algorithm>

namespace fesolv {

Model::Model(const std::string fileName)
{
	_nodes = new nodes;
	_elements = new elements;
	_materials = new materials;
	_readerbuilder = new ReaderBuilder;
	_reader = _readerbuilder->BuildReader(fileName);

	if (_reader){
		_reader->Read(this);
		FinalizeModelInit();
	}
}

Model::~Model()
{
	node_reverse_iterator node = _nodes->rbegin();
	for ( ; node != _nodes->rend(); node++ )
		delete *node;
	
	_nodes->clear();
	delete _nodes;
	
	element_reverse_iterator element = _elements->rbegin();
	for ( ; element != _elements->rend(); element++ )
		delete *element;
	
	_elements->clear();
	delete _elements;

	material_reverse_iterator material = _materials->rbegin();
	for ( ; material != _materials->rend(); material++ )
		delete *material;
	
	_materials->clear();
	delete _materials;

	delete _readerbuilder;
}

Node* Model::GetNode(FEint n) const
{	
	Predicate<Node,FEint> nodepred;
	return *find_if(_nodes->begin(),_nodes->end(),nodepred,n);
}

Element* Model::GetElement(FEint n) const
{	
	Predicate<Element,FEint> elempred;
	return *find_if(_elements->begin(),_elements->end(),elempred,n);
}

Material* Model::GetMaterial(FEint n) const
{	
	Predicate<Material,FEint> matpred;
	return *find_if(_materials->begin(),_materials->end(),matpred,n);
}

void Model::AddNode(Node* const nodePtr)
{
	_nodes->push_back(nodePtr);
}

void Model::AddElement(Element* const elementPtr)
{
	_elements->push_back(elementPtr);
}

void Model::AddMaterial(Material* const materialPtr)
{
	_materials->push_back(materialPtr);
}

Model::Model(const Model& original)
{
	
}

Model& Model::operator=(const Model& original)
{
	return *this;
}

void Model::FinalizeModelInit()
{
	Compare<Element>	cmpElem;
	Compare<Node>		cmpNode;
	Compare<Material>	cmpMat;
	std::sort(_elements->begin(), _elements->end(), cmpElem);
	std::sort(_nodes->begin(), _nodes->end(), cmpNode);
	std::sort(_materials->begin(), _materials->end(), cmpMat);
}

}//end namespace