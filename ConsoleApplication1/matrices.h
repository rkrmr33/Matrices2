#pragma once
class Matrix
{
private:
	int numOfRows;
	int numOfCols;
	double ** Rows;
	double ** Cols;
	void InitiateMatrix();

public:
	//constructor methods
	Matrix(int, int);
	~Matrix();

	//printing and assgining methods
	void Print();
	void AssignCell(int row, int col, double val);
	void Assign();
	double GetCell(int row, int col);
	static bool CheckZeroMatrix(Matrix*);
	static bool CheckZeroRow(Matrix*, int row);
	static int CountZeroRow(Matrix*);

	//math methods
	static Matrix* Addition(Matrix*, Matrix*);
	void Transpose();
	static Matrix* ScalarMultiplication(Matrix*, double scalar);
	static Matrix* AddRows(Matrix*, int effectedRow, int otherRow, double multiplier = 1);
	static Matrix* RowMultiplication(Matrix*, int row, double scalar);
	static Matrix* SwapRows(Matrix*, int firstRow, int secondRow);
	static Matrix* Multiplication(Matrix*, Matrix*);
	static Matrix* GaussianElimination(Matrix *);
};

