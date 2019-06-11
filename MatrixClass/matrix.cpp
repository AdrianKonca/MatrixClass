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
		for (auto column = 0; column < columnCount; column++)
			values[row][column] += addedValue;

	return *this;
}

bool matrix::equalDimensions(const matrix & a, const matrix & b)
{
	return (a.rowCount == b.rowCount && a.columnCount == b.columnCount);
}

void matrix::transpose()
{
	matrix transposed = matrix(columnCount, rowCount);
	for (auto row = 0; row < rowCount; row++)
		for (auto column = 0; column < columnCount; column++)
			transposed.values[column][row] = values[row][column];
	*this = transposed;
}

matrix matrix::multiply(const matrix &toMultiply)
{
	if (this->columnCount != toMultiply.rowCount)
		throw std::exception("Trying to multiply matrices where the lefthand Matrix columnCount and righthand Matrix rowCount don't match!");

	auto multiplied = matrix(this->rowCount, toMultiply.columnCount);
	for (auto row = 0; row < multiplied.rowCount; row++)
		for (auto column = 0; column < multiplied.columnCount; column++)
			for (auto edgeValue = 0; edgeValue < this->columnCount; edgeValue++)
				multiplied.values[row][column] += this->values[row][edgeValue] * toMultiply.values[edgeValue][column];

	return multiplied;
}

matrix matrix::add(const matrix &toAdd)
{
	if (!equalDimensions(toAdd, *this))
		throw std::exception("Trying to add matirces of diffrent sizes!");
	
	auto added = matrix(toAdd.rowCount, toAdd.columnCount);

	for (auto row = 0; row < rowCount; row++)
		for (auto column = 0; column < columnCount; column++)
			added.values[row][column] = this->values[row][column] + toAdd.values[row][column];

	return added;
}

matrix matrix::addNumber(const float toAdd)
{
	auto added = matrix(this->rowCount, this->columnCount);

	for (auto row = 0; row < rowCount; row++)
		for (auto column = 0; column < columnCount; column++)
			added.values[row][column] += this->values[row][column] + toAdd;
	
	return added;
}

matrix matrix::substract(const matrix &toSubstract)
{
	if (!equalDimensions(toSubstract, *this))
		throw std::exception("Trying to substract matirces of diffrent sizes!");

	auto substracted = matrix(toSubstract.rowCount, toSubstract.columnCount);

	for (auto row = 0; row < rowCount; row++)
		for (auto column = 0; column < columnCount; column++)
			substracted.values[row][column] = this->values[row][column] - toSubstract.values[row][column];

	return substracted;
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