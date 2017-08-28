#include "stdafx.h"
#include "matrices.h"
#include <iostream>

#pragma region Constructor Methods
/**********   Constructor method   ***********/
Matrix::Matrix(int numOfRows, int numOfCols)
{
	if (numOfRows <= 0 || numOfCols <= 0)
	{
		std::cout << "[Error] Invalid matrix dimensions" << std::endl;
	}
	this->numOfRows = numOfRows;
	this->numOfCols = numOfCols;

	this->Rows = new double*[this->numOfRows];
	this->Cols = new double*[this->numOfCols];

	//setup rows
	for (int i = 0; i < this->numOfRows; i++)
	{
		this->Rows[i] = new double[this->numOfCols];
	}

	//setup cols
	for (int i = 0; i < this->numOfCols; i++)
	{
		this->Cols[i] = new double[this->numOfRows];
	}

	InitiateMatrix();
}


/**********   Initiation method   ***********/
void Matrix::InitiateMatrix()
{
	// zeroing Rows
	for (int i = 0; i < this->numOfRows; i++)
	{
		for (int j = 0; j < this->numOfCols; j++)
		{
			this->AssignCell(i, j, 0.0);
		}
	}
}


/**********   Destructor method   ***********/
Matrix::~Matrix()
{
	/* need to check if doing this correctly */
	//zero rows
	for (int i = 0; i < this->numOfRows; i++)
	{
		delete this->Rows[i];
	}

	//zero cols
	for (int i = 0; i < this->numOfCols; i++)
	{
		delete this->Cols[i];
	}

	delete this->Rows, this->Cols, this;
}
#pragma endregion

#pragma region Printing And Assigning Methods
/**********   Printing method   ***********/
void Matrix::Print()
{
	for (int i = 0; i < this->numOfRows; i++)
	{
		for (int j = 0; j < this->numOfCols; j++)
		{
			std::cout << "|" << this->Rows[i][j];
		}
		std::cout << "|" << std::endl;
	}
	std::cout << std::endl;
}


/**********   Cell Assignment method   ***********/
void Matrix::AssignCell(int row, int col, double val)
{
	this->Rows[row][col] = val;
	this->Cols[col][row] = val;
}


/**********   Cell Getting method   ***********/
double Matrix::GetCell(int row, int col) {
	return this->Rows[row][col];
}


/**********   Matrix Assignment method   ***********/
void Matrix::Assign()
{
	std::cout << "Initiated assignment process..." << std::endl;
	std::cout << "Please enter first row values [" << this->numOfCols << " values each row]: " << std::endl;

	for (int i = 0; i < this->numOfRows; i++)
	{
		for (int j = 0; j < this->numOfCols; j++)
		{
			//Looping through every cell of the matrix
			double val;
			std::cout << "[" << j+1 << "]<";
			// handle bad input loop
			while (!(std::cin >> val)) {
				std::cin.clear(); 
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
				std::cout << "[Assign] Invalid input; please re-enter: " << std::endl << "[" << j << "]<";
			}
			this->AssignCell(i, j, val); //Assigning value
		}
		if (i + 1 == this->numOfRows) {
			// at the end of the assignment operation
			std::cout << "done." << std::endl;
		}
		else {
			// every new row
			std::cout << "Row " << i + 2 << ":" << std::endl;
		}
	}
}
#pragma endregion

#pragma region Math Methods
/**********   Addition method   ***********/
Matrix* Matrix::Addition(Matrix* m1, Matrix* m2)
{
	std::cout << "[Addition]" << std::endl;
	// checks if the two matrices don't have the same dimensions
	if (m1->numOfCols != m2->numOfCols || m1->numOfRows != m2->numOfRows) {
		std::cout << "[Add] The two matrices don't have the same dimensions, therefore cannot be added together." << std::endl;
		return nullptr;
	}

	Matrix* addedMat = new Matrix(m1->numOfRows, m1->numOfCols);

	for (int i = 0; i < m1->numOfRows; i++)
	{
		for (int j = 0; j < m1->numOfCols; j++)
		{
			double val = m1->Rows[i][j] + m2->Rows[i][j];
			addedMat->AssignCell(i, j, val);
		}
	}

	return addedMat;
}


/**********   Transpositioning method   ***********/
void Matrix::Transpose()
{
	std::cout << "[Transpose]" << std::endl;
	//changing rows into columns
	double ** temp1 = this->Rows;
	this->Rows = this->Cols;
	this->Cols = temp1;

	//adjusting number of rows and columns accordingly
	int temp2 = this->numOfRows;
	this->numOfRows = this->numOfCols;
	this->numOfCols = temp2;
	
	this->Print();
}


/**********   Transpositioning method   ***********/
Matrix* Matrix::ScalarMultiplication(Matrix* m, double scalar) 
{
	std::cout << "[ScalarMultiplication]" << std::endl;
	for (int i = 0; i < m->numOfRows; i++)
	{
		for (int j = 0; j < m->numOfCols; j++)
		{
			m->AssignCell(i, j, m->GetCell(i, j) * scalar);
		}
	}

	m->Print();
	return m;
}


/**********   Add rows method   ***********/
Matrix* Matrix::AddRows(Matrix* m, int effRow, int otherRow, double multiplier)
{
	//check out of bounds exeption
	if (effRow < 0 || effRow >= m->numOfRows || otherRow < 0 || otherRow >= m->numOfRows) 
	{
		std::cout << "[AddRows] Out of matrix boundries, start at base 0" << std::endl;
		return nullptr;
	} 

	std::cout << "[AddRows]" << std::endl;
	for (int i = 0; i < m->numOfCols; i++)
	{
		double otherRowVal = m->Rows[otherRow][i];
		double effectedRowVal = m->Rows[effRow][i];
		m->AssignCell(effRow, i, (int)(effectedRowVal + (multiplier * otherRowVal)));
	}

	m->Print();

	return m;
}


/**********   Row Multiplication method   ***********/
Matrix* Matrix::RowMultiplication(Matrix* m, int row, double scalar)
{
	//checks out of bounds exeption
	if (row < 0 || row >= m->numOfRows) 
	{
		std::cout << "[AddRows] Out of matrix boundries, start at base 0" << std::endl;
		return nullptr;
	}
	//checks for zero scalar
	if (scalar == 0.0) 
	{
		std::cout << "[AddRows] Cannot multiply a row by zero." << std::endl;
		return nullptr;
	}

	for (int i = 0; i < m->numOfCols; i++)
	{
		m->AssignCell(row, i, m->Rows[row][i] * scalar);
	}

	std::cout << "[RowMultiplication] Row=" << row + 1 << " Scalar=" << scalar << std::endl;
	m->Print();

	return m;
}


/**********   Add rows method   ***********/
Matrix* Matrix::SwapRows(Matrix* m, int fr, int sr)
{
	//check out of bounds exeption
	if (fr < 0 || fr >= m->numOfRows || sr < 0 || sr >= m->numOfRows)
	{
		std::cout << "[SwitchRows] Out of matrix boundries, start at base 0" << std::endl;
		return nullptr;
	}
	for (int i = 0; i < m->numOfCols; i++)
	{
		double temp = m->Rows[fr][i];
		m->AssignCell(fr, i, m->Rows[sr][i]);
		m->AssignCell(sr, i, temp);
	}

	std::cout << "[SwitchRows] " << fr + 1 << "<-->" << sr + 1 << std::endl;
	m->Print();

	return m;
}


/**********   Metrix multiplication method   ***********/
Matrix* Matrix::Multiplication(Matrix* a, Matrix* b) 
{
	// don't have the correct dimensions for multiplication
	if (a->numOfCols != b->numOfRows) 
	{	
		std::cout << "[Multiplication] The matrices provided are not of the correct dimensions, therefore cannot be multiplied." << std::endl;
		return nullptr;
	}

	//Initiating a result metrix
	Matrix* c = new Matrix(a->numOfRows, b->numOfCols);

	//Calculating value for each cell in the result metrix
	for (int i = 0; i < c->numOfRows; i++)
	{
		for (int j = 0; j < c->numOfCols; j++)
		{
			double* row = a->Rows[i];
			double* col = b->Cols[j];
			double sum = 0.0;
			for (int k = 0; k < a->numOfCols; k++)
			{
				sum += row[k] * col[k];
			}
			c->AssignCell(i, j, sum);
		}
	}

	std::cout << "[Multiplication]" << std::endl;
	c->Print();
	return c;
}


/**********   Guassian Elimination method   ***********/
//Matrix * Matrix::GaussianElimination(Matrix* m)
//{
//	if (CheckZeroMatrix(m))
//	{
//		std::cout << "[GaussianElimination] done.";
//		return m;
//	}
//
//	for (int i = 0; i < m->numOfRows; i++)
//	{
//		////if its a zeros row, swap with last row
//		//if (CheckZeroRow(m, i))
//		//{
//		//	m->SwapRows(m, i,)
//		//}
//	}
//}
#pragma endregion

#pragma region Inner Math Methods
/**********   Checks if a matrix is all zeros method   ***********/
bool Matrix::CheckZeroMatrix(Matrix* m) 
{
	if (m->numOfRows == CountZeroRow(m))
	{
		return true;
	}
	return false;
}


/**********   Checks if a certain row is all zeros method   ***********/
bool Matrix::CheckZeroRow(Matrix* m, int row)
{
	for (int i = 0; i < m->numOfCols; i++)
	{
		if (m->Rows[row][i] != 0)
		{
			return false;
		}
	}
	return true;
}


/**********   Addition method   ***********/
int Matrix::CountZeroRow(Matrix* m)
{
	int sum = 0;
	for (int i = 0; i < m->numOfRows; i++)
	{
		if (CheckZeroRow(m, i))
			sum += 0;
	}
	return sum;
}

#pragma endregion




