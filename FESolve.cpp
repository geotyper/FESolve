// FESolve.cpp : Definiert den Einsprungpunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "Model.h"
#include "LinearSolver.h"

#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
	
	if(argc < 2 || argc > 4) {
		std::cout << "ERROR: fesolve input.* ?output.*?" << std::endl;
	} else {
		fesolv::Model model(argv[1]);
		fesolv::LinearSolver solver(&model);
		
		solver.Solve();
		
		if(argc != 2){

			std::ofstream fout(argv[2]);
			if(!fout){
				std::cout << "could not open" << argv[2] << std::endl;
				goto stdoutput;
			}
			
			fout << "################# FESOLVE #################" << std::endl;
			fout << "#	Sascha Leuthold						    " << std::endl << std::endl;
			
			solver.PrintData(fout);
			solver.PrintElementStiffnessMatrix(fout);
			solver.PrintSystemStiffnessMatrix(fout);
			solver.PrintSystemDVector(fout);
			solver.PrintSystemDisplacementVector(fout);
			solver.PrintReactionForceVector(fout);

		} else {
stdoutput:
			std::cout << "################# FESOLVE #################" << std::endl;
			std::cout << "#	Sascha Leuthold							 " << std::endl << std::endl;
			
			solver.PrintData(std::cout);
			solver.PrintElementStiffnessMatrix(std::cout);
			solver.PrintSystemStiffnessMatrix(std::cout);
			solver.PrintSystemDVector(std::cout);
			solver.PrintSystemDisplacementVector(std::cout);
			solver.PrintReactionForceVector(std::cout);
		}
	}
	
	system("PAUSE");
	return 1;
}




