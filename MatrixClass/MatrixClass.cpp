#include "pch.h"
#include "matrix.h"
#include "matrixPointers.h"

void loadSaveMatrixTest()
{
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

void operatorMatrixTest()
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
}


void operatorMatrixPointersTest()
{
	auto codematrix = matrixPointers(4, 3);
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
}

void speedComparisonTest(int TEST_SIZE, int rowCount, int columnCount)
{
	auto matrixSmall = matrix(rowCount, columnCount);
	clock_t startTime = clock();
	for (auto i = 0; i < TEST_SIZE; i++)
	{
		matrixSmall.transpose();
	}
	clock_t endTime = clock() - startTime;
	std::cout << "Time for matrix using <vector> of <vector> of doubles: " << endTime << std::endl;
	startTime = clock();
	auto matrixPointerSmall = matrixPointers(rowCount, columnCount);
	for (auto i = 0; i < TEST_SIZE; i++)
	{
		matrixSmall.transpose();
	}
	endTime = clock() - startTime;
	std::cout << "Time for matrix using double pointer: " << endTime << std::endl;
	
}

void multiplyTest()
{
	auto codematrix = matrix(2, 2);
	codematrix += 2;
	auto resultMatrix = codematrix.multiply(codematrix);
	std::cout << resultMatrix[0][0];
}

int main()
{
	//operatorMatrixTest();
	//loadSaveMatrixTest();
	
	//operatorMatrixPointersTest();
	//speedComparisonTest(10000, 5, 5);
	//speedComparisonTest(1000, 50, 50);

	multiplyTest();
}
