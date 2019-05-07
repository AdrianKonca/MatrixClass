#pragma once
class matrixPointers
{
private:
	int rowCount;
	int columnCount;
	double **values;
	static const char rowSeparator = ';';
	static const char columnSeparator = ',';
	static const int precision = 3;
	void allocateMemory();
public:
	std::string getCellString(int row, int column);
	std::string getRowString(int row);
	std::string getColumnString(int column);
	std::string getString();

	matrixPointers operator + (double const &addedValue);
	matrixPointers operator += (double const &addedValue) { return (*this + addedValue); };
	void transpose();
	void save(std::string &filePath);

	matrixPointers(int rowCount, int columnCount);
	matrixPointers(std::string &filePath);
	matrixPointers(std::fstream &file);
	~matrixPointers();

	double*& operator[](std::size_t idx) { return values[idx]; }
	double*& operator[](std::size_t idx) const { return values[idx]; }

	double& operator()(int column, int row) { return values[column][row]; }
	const double& operator()(int column, int row) const { return values[column][row]; };
};
