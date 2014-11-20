#include "Node.h"

namespace fesolv {

Node::Node(FEint n, FEdouble x, FEdouble y, FEdouble z)
{
	_number = n;
	_x = x;
	_y = y;
	_z = z;
	_xforce=_yforce=_zforce=_xxforce=_yyforce=_zzforce=0.0;
	_xconstrain=_yconstrain=_zconstrain=_xxconstrain=_yyconstrain=_zzconstrain = FEfalse;
}

void Node::SetCoord(FEdouble x, FEdouble y, FEdouble z)
{
	_x = x;
	_y = y;
	_z = z;
}

void Node::SetNumber(FEint number)
{ 
	_number = number;
}

void Node::SetForce(FEdouble xforce, FEdouble yforce, FEdouble zforce, FEdouble xxforce, FEdouble yyforce, FEdouble zzforce)
{
	_xforce = xforce;
	_yforce = yforce;
	_zforce = zforce;
	_xxforce = xxforce;
	_yyforce = yyforce;
	_zzforce = zzforce;
}

void Node::SetConstrain(FEint xcon, FEint ycon, FEint zcon, FEint xxcon, FEint yycon, FEint zzcon)
{
	_xconstrain = xcon;
	_yconstrain = ycon;
	_zconstrain = zcon;
	_xxconstrain = xxcon;
	_yyconstrain = yycon;
	_zzconstrain = zzcon;
}

}//end namespace