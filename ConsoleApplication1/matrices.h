#pragma once
class Matrix
{
private:
	int numOfRows;
	int numOfCols;
	int ** Rows;
	int ** Cols;
	void InitiateMatrix();

public:
	//constructor methods
	Matrix(int, int);
	~Matrix();

	//printing and assgining methods
	void Print();
	void AssignCell(int row, int col, int val);
	void Assign();
	int GetCell(int row, int col);

	//math methods
	static Matrix* Addition(Matrix*, Matrix*);
	void Transpose();
	static Matrix* ScalarMultiplication(Matrix*, int scalar);
	static Matrix* AddRows(Matrix*, int effectedRow, int otherRow, int multiplier = 1);
	static Matrix* RowMultiplication(Matrix*, int row, int scalar);
	static Matrix* SwitchRows(Matrix*, int firstRow, int secondRow);
	static Matrix* Multiplication(Matrix*, Matrix*);
};

