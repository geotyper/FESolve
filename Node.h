
#ifndef NODE_H
#define NODE_H

#include "Fe.h"

namespace fesolv {
using namespace fe;

class Node
{
public:
	Node(FEint n, FEdouble x, FEdouble y, FEdouble z);
    
    ~Node() { };
	
	FEdouble			GetX() const { return _x; }
	FEdouble			GetY() const { return _y; }
	FEdouble			GetZ() const { return _z; }
	FEuint			GetNumber() const { return _number; }
	FEdouble			GetXForce() const { return _xforce; }
	FEdouble			GetYForce() const { return _yforce; }
	FEdouble			GetZForce() const { return _zforce; }
	FEdouble			GetXXForce() const { return _xxforce; }
	FEdouble			GetYYForce() const { return _yyforce; }
	FEdouble			GetZZForce() const { return _zzforce; }
	FEint				GetXConstrain() const { return _xconstrain; }
	FEint				GetYConstrain() const { return _yconstrain; }
	FEint				GetZConstrain() const { return _zconstrain; }
	FEint				GetXXConstrain() const { return _xxconstrain; }
	FEint				GetYYConstrain() const { return _yyconstrain; }
	FEint				GetZZConstrain() const { return _zzconstrain; }

	void SetCoord(FEdouble x, FEdouble y, FEdouble z);
	void SetNumber(FEint number);
	void SetForce(FEdouble xforce, FEdouble yforce, FEdouble zforce, FEdouble xxforce, FEdouble yyforce, FEdouble zzforce);
	void SetConstrain(FEint xcon, FEint ycon, FEint zcon, FEint xxcon, FEint yycon, FEint zzcon);

	
protected:
	
	FEint _number;
	FEdouble _x;
    FEdouble _y;
    FEdouble _z;
	FEdouble _xforce;
	FEdouble _yforce;
    FEdouble _zforce;
	FEdouble _xxforce;
	FEdouble _yyforce;
    FEdouble _zzforce;
	FEint _xconstrain;
	FEint _yconstrain;
	FEint _zconstrain;
	FEint _xxconstrain;
	FEint _yyconstrain;
	FEint _zzconstrain;
};

}//end namespace

#endif

