#pragma once
template <typename numberType>
class matrixTemplate
{
private:
	int rowCount;
	int columnCount;
	std::vector<std::vector<numberType>> values;
	static const char rowSeparator = ';';
	static const char columnSeparator = ',';
	static const int precision = 3;
	static bool equalDimensions(const matrixTemplate &a, const matrixTemplate &b);
public:
	std::string getCellString(int row, int column);
	std::string getRowString(int row);
	std::string getColumnString(int column);
	std::string getString();

	matrixTemplate operator + (numberType const &addedValue) { return this->addNumber(addedValue); };
	matrixTemplate operator += (numberType const &addedValue) { return (*this + addedValue); };
	matrixTemplate operator + (matrixTemplate const &addedMatrix) { return this->add(addedMatrix); };
	matrixTemplate operator * (matrixTemplate const &multipliedMatrix) { return this->multiply(multipliedMatrix); };
	matrixTemplate operator += (matrixTemplate const &addedMatrix);
	matrixTemplate operator *= (matrixTemplate const &multipliedMatrix);
	matrixTemplate operator = (matrixTemplate const &copiedMatrix);
	matrixTemplate operator ! () { return this->transpose(); };

	matrixTemplate transpose();
	matrixTemplate multiply(const matrixTemplate &toMultiply);
	matrixTemplate add(const matrixTemplate &toAdd);
	matrixTemplate addNumber(const float toAdd);
	matrixTemplate substract(const matrixTemplate &toSubstract);
	numberType& solve();
	void save(std::string &filePath);

	matrixTemplate(int rowCount, int columnCount);
	matrixTemplate(std::string &filePath);
	matrixTemplate(std::fstream &file);
	~matrixTemplate();

	std::vector<numberType>& operator[](std::size_t idx) { return values[idx]; }
	const std::vector<numberType>& operator[](std::size_t idx) const { return values[idx]; }

	numberType& operator()(int column, int row) { return values[column][row]; }
	const numberType& operator()(int column, int row) const { return values[column][row]; }
};

