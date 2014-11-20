
#ifndef ABSTRACTREADER_H
#define ABSTRACTREADER_H

#include "Model.h"

namespace fesolv {

class AbstractReader  
{
public:
	AbstractReader();
	virtual ~AbstractReader();
	
	virtual void Read(Model* model)=0;

};

}//end namespace

#endif 