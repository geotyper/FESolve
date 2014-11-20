// Compare.h: Schnittstelle für die Klasse Compare.
//
//////////////////////////////////////////////////////////////////////

#ifndef COMPARE_H
#define COMPARE_H

namespace fesolv {

template<class T> class Compare  
{
public:
	Compare(){};
	~Compare(){};
	
	bool operator()(T* T1, T* T2) const
	{return T1->GetNumber() < T2->GetNumber();}
};

} //end namespace
#endif 