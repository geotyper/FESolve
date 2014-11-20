// Matrerial.h: Schnittstelle für die Klasse Matrerial.
//
//////////////////////////////////////////////////////////////////////

#ifndef MATRERIAL_H
#define MATRERIAL_H

#include "Fe.h"

namespace fesolv {
using namespace fe;

class Material  
{
public:
	Material(FEint number, FEdouble emodul, FEdouble nue);
	~Material();
	
	FEint GetNumber()		const { return _number; }
	FEdouble GetEmodul()	const { return _emodul; }
	FEdouble GetNue()		const { return _nue; }

protected:
	FEint _number;
	FEdouble _emodul;
	FEdouble _nue;
};


} // end namespace
#endif 