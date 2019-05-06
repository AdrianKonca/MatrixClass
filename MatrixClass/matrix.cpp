#include "pch.h"
#include "matrix.h"


matrix::matrix(int rowCount, int columnCount)
{
	this->columnCount = columnCount;
	this->rowCount = rowCount;
	this->values = std::vector<std::vector<double>>(rowCount, std::vector<double>(columnCount));
}

matrix::matrix(std::string &filePath)
{
	std::fstream file = std::fstream(filePath, std::fstream::in);
	std::string line;
	file >> rowCount;
	file >> columnCount;
	this->values = std::vector<std::vector<double>>(rowCount, std::vector<double>(columnCount));

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


matrix::matrix(std::fstream &file)
{
	std::string line;
	file >> rowCount;
	file >> columnCount;
	this->values = std::vector<std::vector<double>>(rowCount, std::vector<double>(columnCount));
	
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

matrix::~matrix()
{
}

void matrix::save(std::string &fileName)
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

matrix matrix::operator + (double const &addedValue)
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

void matrix::transpose()
{
	matrix transposed = matrix(columnCount, rowCount);
	for (auto row = 0; row < rowCount; row++)
	{
		for (auto column = 0; column < columnCount; column++)
		{
			transposed.values[column][row] = values[row][column];
		}
	}
	*this = transposed;
}

std::string matrix::getCellString(int row, int column)
{
	std::stringstream stringStream;
	stringStream << std::setprecision(precision) << std::fixed;
	stringStream << "[ " <<  values[row][column] << " ] ";
	return stringStream.str();
}

std::string matrix::getRowString(int row)
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

std::string matrix::getColumnString(int column)
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

std::string matrix::getString()
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