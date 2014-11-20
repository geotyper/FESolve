
#ifndef FEMREADER_H
#define FEMREADER_H

#include "Fe.h"
#include "Model.h"
#include "AbstractReader.h"

#include <iostream>
#include <fstream>
#include <cstring> //strncmp
#include <string>

namespace fesolv {

using namespace fe;

class FEMReader : public AbstractReader  
{
public:
	FEMReader(const std::string fileName);
	~FEMReader();
	
	void Read(Model* model);

private:

	FEbool ReadNodes();
	FEbool ReadElements();
	FEbool ReadMaterial();

	std::string	_fileName;
	std::ifstream		_file;
	Model*				_model;
};

}//end namespace

#endif 
