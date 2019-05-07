#include "pch.h"
#include "matrixPointers.h"

matrixPointers::matrixPointers(int rowCount, int columnCount)
{
	this->columnCount = columnCount;
	this->rowCount = rowCount;

	allocateMemory();
}

matrixPointers::matrixPointers(std::string &filePath)
{
	std::fstream file = std::fstream(filePath, std::fstream::in);
	std::string line;
	file >> rowCount;
	file >> columnCount;

	allocateMemory();

	int currentRow = 0;
	int currentColumn = 0;
	while (!file.eof())
	{
		file >> line;
		if (line == std::string(1, rowSeparator))
		{
			currentRow++;
			currentColumn = 0;
		}
		else
		{
			values[currentRow][currentColumn] = stof(line);
			currentColumn++;
		}
	}
	file.close();
}


matrixPointers::matrixPointers(std::fstream &file)
{
	std::string line;
	file >> rowCount;
	file >> columnCount;

	allocateMemory();

	int currentRow = 0;
	int currentColumn = 0;
	while (!file.eof())
	{
		file >> line;
		if (line == std::to_string(rowSeparator))
		{
			currentRow++;
			currentColumn = 0;
		}
		else
		{
			values[currentRow][currentColumn] = stof(line);
			currentColumn++;
		}
	}
}

matrixPointers::~matrixPointers()
{
}

void matrixPointers::allocateMemory()
{
	this->values = new double*[rowCount];
	for (auto i = 0; i < rowCount; i++)
	{
		this->values[i] = new double[columnCount];
	}

	for (auto row = 0; row < rowCount; row++)
	{
		for (auto column = 0; column < columnCount; column++)
		{
			values[row][column] = 0;
		}
	}
}

void matrixPointers::save(std::string &fileName)
{
	std::fstream file;
	file.open(fileName, std::fstream::out);
	file << rowCount << std::endl;
	file << columnCount << std::endl;
	for (auto row = 0; row < rowCount; row++)
	{
		for (auto column = 0; column < columnCount; column++)
		{
			file << values[row][column] << std::endl;
		}
		file << rowSeparator << std::endl;
	}
	file.flush();
	file.close();
}

matrixPointers matrixPointers::operator + (double const &addedValue)
{
	for (auto row = 0; row < rowCount; row++)
	{
		for (auto column = 0; column < columnCount; column++)
		{
			values[row][column] += addedValue;
		}
	}
	return *this;
}

void matrixPointers::transpose()
{
	matrixPointers transposed = matrixPointers(columnCount, rowCount);
	for (auto row = 0; row < rowCount; row++)
	{
		for (auto column = 0; column < columnCount; column++)
		{
			transposed.values[column][row] = values[row][column];
		}
	}
	*this = transposed;
}

std::string matrixPointers::getCellString(int row, int column)
{
	std::stringstream stringStream;
	stringStream << std::setprecision(precision) << std::fixed;
	stringStream << "[ " << values[row][column] << " ] ";
	return stringStream.str();
}

std::string matrixPointers::getRowString(int row)
{
	std::stringstream stringStream;
	stringStream << std::setprecision(precision) << std::fixed;
	stringStream << "[ ";
	for (auto column = 0; column < columnCount; column++)
	{
		stringStream << values[row][column] << columnSeparator << " ";
	}
	stringStream << "]";
	return stringStream.str();
}

std::string matrixPointers::getColumnString(int column)
{
	std::stringstream stringStream;
	stringStream << std::setprecision(precision) << std::fixed;
	stringStream << "[ ";
	for (auto row = 0; row < rowCount; row++)
	{
		stringStream << values[row][column] << rowSeparator << " ";
	}
	stringStream << "]";
	return stringStream.str();
}

std::string matrixPointers::getString()
{
	std::stringstream stringStream;
	stringStream << std::setprecision(precision) << std::fixed;
	stringStream << "[ ";
	for (auto row = 0; row < rowCount; row++)
	{
		if (row > 0)
		{
			stringStream << "  ";
		}
		for (auto column = 0; column < columnCount; column++)
		{
			stringStream << values[row][column];
			if (column == (columnCount - 1))
			{
				stringStream << rowSeparator;
			}
			else
			{
				stringStream << columnSeparator << " ";
			}
		}
		if (row != (rowCount - 1))
		{
			stringStream << std::endl;
		}
	}
	stringStream << " ]";
	return stringStream.str();
}