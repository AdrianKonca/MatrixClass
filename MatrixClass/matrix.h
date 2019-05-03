#pragma once
class matrix
{
private:
	int rowCount;
	int columnCount;
	std::vector<std::vector<double>> values;
	static const char rowSeparator = ';';
	static const char columnSeparator = ',';
	static const int precision = 3;
public:
	std::string getCellString(int row, int column);
	std::string getRowString(int row);
	std::string getColumnString(int column);
	std::string getString();

	matrix operator + (double const &addedValue);
	matrix operator += (double const &addedValue) { return (*this + addedValue); };
	void transpose ();

	matrix(int rowCount, int columnCount);
	~matrix();

	std::vector<double>& operator[](std::size_t idx) { return values[idx]; }
	const std::vector<double>& operator[](std::size_t idx) const { return values[idx]; }

	double& operator()(int column, int row) { return values[column][row]; }
	const double& operator()(int column, int row) const { return values[column][row]; }
};

