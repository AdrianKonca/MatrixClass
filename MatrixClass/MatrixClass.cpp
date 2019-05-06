#include "pch.h"
#include "matrix.h"

int main()
{
	auto codematrix = matrix(4, 3);
	std::cout << "All cells are empty:" << std::endl;
	std::cout << codematrix.getString() << std::endl; //all cells - but empty

	codematrix(1, 1) = 10.5;
	std::cout << "Cell [1, 1] is changed to 10.5 and printed out" << std::endl;
	std::cout << codematrix.getCellString(1, 1) << std::endl; //one cell

	std::cout << "Print out row [1]:" << std::endl;
	std::cout << codematrix.getRowString(1) << std::endl; //one row
	std::cout << "Print out column [1]:" << std::endl;
	std::cout << codematrix.getColumnString(1) << std::endl; //one column
	std::cout << "Print out all cells in matrix:" << std::endl;
	std::cout << codematrix.getString() << std::endl; //all cells

	std::cout << "5.0 is added to all cells and matrix gets printed out:" << std::endl;
	codematrix += 5.0; //add to all cells
	std::cout << codematrix.getString() << std::endl;

	std::cout << "Matrix is transpored and gets printed out:" << std::endl;
	codematrix.transpose(); //transpose all cells
	std::cout << codematrix.getString() << std::endl;

	std::cout << "Load another matrix from TEXT.TXT and show all cells:" << std::endl;
	std::string matrixName = "TEST.TXT";
	auto testmatrixload = matrix(matrixName);
	std::cout << testmatrixload.getString() << std::endl; //show matrix before changing anything
	std::cout << "Transpose loaded array and show all cells:" << std::endl;
	testmatrixload.transpose();
	std::cout << testmatrixload.getString() << std::endl; //show transposed matrix

	matrixName = "TEST2.TXT";
	std::cout << "Save array to TEST2.TXT and load it as another array. Next print out the content of newly loaded array:" << std::endl;
	testmatrixload.save(matrixName);
	auto testmatrixsave = matrix(matrixName);
	std::cout << testmatrixsave.getString() << std::endl; //show that nothing changed during load/save

	std::cout << "19.05 is added to all cells of array and printed out:" << std::endl;
	testmatrixsave += 19.05;
	std::cout << testmatrixsave.getString() << std::endl; //show that adding still works on newly loaded array

}
