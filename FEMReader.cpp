
#include "FEMReader.h"
#include "Node.h"
#include "Tri3.h"

namespace fesolv {

	FEMReader::FEMReader(const std::string fileName)
{
	_fileName = fileName;
	_model = 0;
}

FEMReader::~FEMReader()
{

}

void FEMReader::Read(Model* model)
{
	_model = model;

	FEchar buf[DATA_LINE_LENGTH];
	// Datei öffnen
	_file.open(_fileName.c_str(), std::ios::in);

    if (_file.good())
    {
        // Wenn die Datei geoeffnet werden konnte...
		// An den Anfang der Datei springen
		_file.seekg(0L, std::ios::beg);
		
		while (!_file.eof()) {
			_file.getline(buf,DATA_LINE_LENGTH);
			if (strncmp(buf,"---KNOTEN",9) == 0)
				ReadNodes();
			if (strncmp(buf,"---ELEMENTE",11) == 0)
				ReadElements();
			if (strncmp(buf,"---MATERIAL",11) == 0)
				ReadMaterial();
		}
    }
	_file.close();
}

FEbool FEMReader::ReadNodes()
{
	FEint number;
	FEdouble x,y,z; 
	FEchar buf[DATA_LINE_LENGTH];
	FEint X,Y,Z,XX,YY,ZZ;
	FEdouble stressX,stressY,stressZ;
	FEchar get;
	Node* nodePtr;

	while (!_file.eof()) {
		_file.get(get);
		if (get != '*') {
			_file.putback(get);
			break;
		}
		_file.getline(buf,DATA_LINE_LENGTH);
	}
	
	while (!_file.eof()) {

		_file.get(get);
		if (get == '*' || get == '-') {
			_file.putback(get);
			break;
		}
		_file.putback(get);

		if(!(_file >> number >> x >> y >> z))
			break;

		nodePtr = new Node(number,x,y,z);
		_file.get(get);
		//READ CONSTRAINS
		if(get=='\n') {
			//_file.getline(buf,DATA_LINE_LENGTH);
		} else {
			_file.putback(get);
			if(_file >> X >> Y >> Z >> XX >> YY >> ZZ)
				nodePtr->SetConstrain(X,Y,Z,XX,YY,ZZ);
			
			_file.get(get);
			//READ FORCES
			if(get=='\n') {
				//_file.getline(buf,DATA_LINE_LENGTH);
			} else {
				_file.putback(get);
				if(_file >> stressX >> stressY >> stressZ)
					nodePtr->SetForce(stressX,stressY,stressZ,0.0,0.0,0.0);

				_file.get(get);
				if(get!='\n') {
					_file.putback(get);
				}
			}
		}

		_model->AddNode(nodePtr);
	}

	_file.clear();
	return FEtrue;
}

FEbool FEMReader::ReadElements()
{
	FEint elemnumber, elemtype, matnumber, node1, node2, node3;
	FEdouble thickness;
	FEchar buf[DATA_LINE_LENGTH];
	FEchar get;
	Tri3* elemPtr;

	while (!_file.eof()) {
		_file.get(get);
		if (get != '*') {
			_file.putback(get);
			break;
		}
		_file.getline(buf,DATA_LINE_LENGTH);
	}
	
	while (!_file.eof()) {
		
		_file.get(get);
		if (get == '*' || get == '-') {
			_file.putback(get);
			break;
		}
		_file.putback(get);
				
		
		if(!(_file >> elemnumber >> elemtype >> node1 >> node2 >> node3 >> matnumber >> thickness))
			break;

		elemPtr = new Tri3(_model,elemnumber,node1,node2,node3,thickness,matnumber);
	
		_file.getline(buf,DATA_LINE_LENGTH);
		_model->AddElement(elemPtr);
	}

	_file.clear();
	return FEtrue;
}

FEbool FEMReader::ReadMaterial()
{
	FEint matnumber;
	FEdouble nue,emodul;
	FEchar buf[DATA_LINE_LENGTH];
	FEchar get;
	Material* matPtr;

	while (!_file.eof()) {
		_file.get(get);
		if (get != '*') {
			_file.putback(get);
			break;
		}
		_file.getline(buf,DATA_LINE_LENGTH);
	}
	
	while (!_file.eof()) {

		_file.get(get);
		if (get == '*' || get == '-') {
			_file.putback(get);
			break;
		}
		_file.putback(get);
		if(!(_file >> matnumber >> emodul >> nue))
			break;

		matPtr = new Material(matnumber,emodul,nue);
	
		_file.getline(buf,DATA_LINE_LENGTH);
		_model->AddMaterial(matPtr);
	}

	_file.clear();
	return FEtrue;
}


}//end namespace