
#ifndef READERBUILDER_H
#define READERBUILDER_H

#include "AbstractReader.h"

namespace fesolv {

class ReaderBuilder
{
public:
	ReaderBuilder();
	~ReaderBuilder();
	
	AbstractReader* BuildReader(const std::string filename);

protected:
	AbstractReader* _abstractreader;

};

} //end namespace

#endif