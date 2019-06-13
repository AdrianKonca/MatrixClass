#include "pch.h"
#include "matrixTemplate.h"

template <typename numberType>
matrixTemplate<numberType>::matrixTemplate(int rowCount, int columnCount)
{
	this->columnCount = columnCount;
	this->rowCount = rowCount;
	this->values = std::vector<std::vector<numberType>>(rowCount, std::vector<numberType>(columnCount));
}

template <typename numberType>
matrixTemplate<numberType>::matrixTemplate(std::string &filePath)
{
	std::fstream file = std::fstream(filePath, std::fstream::in);
	std::string line;
	file >> rowCount;
	file >> columnCount;
	this->values = std::vector<std::vector<numberType>>(rowCount, std::vector<numberType>(columnCount));

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


template <typename numberType>
matrixTemplate<numberType>::matrixTemplate(std::fstream &file)
{
	std::string line;
	file >> rowCount;
	file >> columnCount;
	this->values = std::vector<std::vector<numberType>>(rowCount, std::vector<numberType>(columnCount));

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

template <typename numberType>
matrixTemplate<numberType>::~matrixTemplate()
{
}

template <typename numberType>
void matrixTemplate<numberType>::save(std::string &fileName)
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

template <typename numberType>
bool matrixTemplate<numberType>::equalDimensions(const matrixTemplate & a, const matrixTemplate & b)
{
	return (a.rowCount == b.rowCount && a.columnCount == b.columnCount);
}

template<typename numberType>
matrixTemplate<numberType> matrixTemplate<numberType>::operator+=(matrixTemplate const & addedMatrix)
{
	auto matrixToReturn = *this + addedMatrix;
	*this = matrixToReturn;
	return *this;
}

template<typename numberType>
matrixTemplate<numberType> matrixTemplate<numberType>::operator*=(matrixTemplate const & multipliedMatrix)
{
	auto matrixToReturn = *this * multipliedMatrix;
	*this = matrixToReturn;
	return *this;
}

template<typename numberType>
matrixTemplate<numberType> matrixTemplate<numberType>::operator=(matrixTemplate const & copiedMatrix)
{
	this->columnCount = copiedMatrix.columnCount;
	this->rowCount = copiedMatrix.rowCount;
	std::copy(copiedMatrix.values.begin(), copiedMatrix.values.begin() + copiedMatrix.values.size(), this->values.begin());

	return *this;
}

template <typename numberType>
matrixTemplate<numberType> matrixTemplate<numberType>::transpose()
{
	matrixTemplate transposed = matrixTemplate(columnCount, rowCount);
	for (auto row = 0; row < rowCount; row++)
		for (auto column = 0; column < columnCount; column++)
			transposed.values[column][row] = values[row][column];
	*this = transposed;
	return *this;
}

template <typename numberType>
matrixTemplate<numberType> matrixTemplate<numberType>::multiply(const matrixTemplate &toMultiply)
{
	if (this->columnCount != toMultiply.rowCount)
		throw std::exception("Trying to multiply matrices where the lefthand Matrix columnCount and righthand Matrix rowCount don't match!");

	auto multiplied = matrixTemplate(this->rowCount, toMultiply.columnCount);
	for (auto row = 0; row < multiplied.rowCount; row++)
		for (auto column = 0; column < multiplied.columnCount; column++)
			for (auto edgeValue = 0; edgeValue < this->columnCount; edgeValue++)
				multiplied.values[row][column] += this->values[row][edgeValue] * toMultiply.values[edgeValue][column];

	return multiplied;
}

template <typename numberType>
matrixTemplate<numberType> matrixTemplate<numberType>::add(const matrixTemplate &toAdd)
{
	if (!equalDimensions(toAdd, *this))
		throw std::exception("Trying to add matirces of diffrent sizes!");

	auto added = matrixTemplate(toAdd.rowCount, toAdd.columnCount);

	for (auto row = 0; row < rowCount; row++)
		for (auto column = 0; column < columnCount; column++)
			added.values[row][column] = this->values[row][column] + toAdd.values[row][column];

	return added;
}

template <typename numberType>
matrixTemplate<numberType> matrixTemplate<numberType>::addNumber(const float toAdd)
{
	auto added = matrixTemplate(this->rowCount, this->columnCount);

	for (auto row = 0; row < rowCount; row++)
		for (auto column = 0; column < columnCount; column++)
			added.values[row][column] += this->values[row][column] + toAdd;

	return added;
}

template <typename numberType>
matrixTemplate<numberType> matrixTemplate<numberType>::substract(const matrixTemplate &toSubstract)
{
	if (!equalDimensions(toSubstract, *this))
		throw std::exception("Trying to substract matirces of diffrent sizes!");

	auto substracted = matrixTemplate(toSubstract.rowCount, toSubstract.columnCount);

	for (auto row = 0; row < rowCount; row++)
		for (auto column = 0; column < columnCount; column++)
			substracted.values[row][column] = this->values[row][column] - toSubstract.values[row][column];

	return substracted;
}

template<typename numberType>
numberType & matrixTemplate<numberType>::solve()
{
	if (rowCount != columnCount)
		throw std::exception("Trying to solve non-square matrix!");
	if (rowCount != 2)
		throw std::exception("Only 2x2 matrices are handled by this method!");
	numberType result = values[0][0] * values[1][1] - values[1][0] * values[0][1];
	return result;
}

template <typename numberType>
std::string matrixTemplate<numberType>::getCellString(int row, int column)
{
	std::stringstream stringStream;
	stringStream << std::setprecision(precision) << std::fixed;
	stringStream << "[ " << values[row][column] << " ] ";
	return stringStream.str();
}

template <typename numberType>
std::string matrixTemplate<numberType>::getRowString(int row)
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

template <typename numberType>
std::string matrixTemplate<numberType>::getColumnString(int column)
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

template <typename numberType>
std::string matrixTemplate<numberType>::getString()
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

template class matrixTemplate<int>;
template class matrixTemplate<float>;