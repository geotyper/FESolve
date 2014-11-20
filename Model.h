
#ifndef MODEL_H
#define MODEL_H

#include "Fe.h"

#include "Node.h"
#include "Material.h"

#include <vector>
#include <string>

namespace fesolv {
using namespace fe;

class AbstractSolver;
class AbstractReader;
class ReaderBuilder;
class Element;

/**
* Typedefs for the container implementation.
*/
typedef std::vector<Node*>							nodes;
typedef std::vector<Node*>::iterator				node_iterator;
typedef std::vector<Node*>::const_iterator			const_node_iterator;
typedef std::vector<Node*>::reverse_iterator		node_reverse_iterator;
typedef std::vector<Element*>						elements;
typedef std::vector<Element*>::iterator				element_iterator;
typedef std::vector<Element*>::const_iterator		const_element_iterator;
typedef std::vector<Element*>::reverse_iterator		element_reverse_iterator;
typedef std::vector<Material*>						materials;
typedef std::vector<Material*>::iterator			material_iterator;
typedef std::vector<Material*>::const_iterator		const_material_iterator;
typedef std::vector<Material*>::reverse_iterator	material_reverse_iterator;


class Model
{
public:
	Model(const std::string fileName);
    ~Model();
	
	void AddNode(Node* const nodePtr);
	void AddElement(Element* const elementPtr);
	void AddMaterial(Material* const materialPtr);

	nodes*		GetNodes() const { return _nodes; }
	elements*	GetElements() const { return _elements; }
	materials*	GetMaterials() const { return _materials; }
	
	Node*		GetNode(FEint n) const;
	Element*	GetElement(FEint n) const;
	Material*	GetMaterial(FEint n) const;

private:
	// no copy's!
    Model(const Model& original);
    Model& operator=(const Model& original);
	
	void FinalizeModelInit();


	AbstractReader*	_reader;
	ReaderBuilder*	_readerbuilder;

	nodes*		_nodes;
	elements*	_elements;
	materials*  _materials;
	
};


}//end namespace

#endif