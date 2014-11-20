
#include "ReaderBuilder.h"
#include "FEMReader.h"

namespace fesolv {


ReaderBuilder::ReaderBuilder()
{	
}

ReaderBuilder::~ReaderBuilder()
{
	delete _abstractreader;
}

AbstractReader* ReaderBuilder::BuildReader(const std::string filename)
{
	// case *.FEM - file
	if(!_abstractreader)
		delete _abstractreader;

	if(filename.find(".FEM") != std::string::npos || filename.find(".fem") != std::string::npos ) {
		_abstractreader = new FEMReader(filename);
	}
	return _abstractreader;
}



} //end namespace