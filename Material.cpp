// Material.cpp: Implementierung der Klasse Material.
//
//////////////////////////////////////////////////////////////////////

#include "Material.h"

namespace fesolv {

Material::Material(FEint number, FEdouble emodul, FEdouble nue)
{
	_number = number;
	_emodul = emodul;
	_nue = nue;
}

Material::~Material()
{

}

} //end namespace
