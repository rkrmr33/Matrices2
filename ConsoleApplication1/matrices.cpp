#include "stdafx.h"
#include "matrices.h"
#include <iostream>

#pragma region Constructor Methods
/**********   Constructor Function   ***********/
Matrix::Matrix(int NumOfrows, int NumOfCols)
{
	this->numOfRows = NumOfrows;
	this->numOfCols = NumOfCols;

	this->Rows = new int*[this->numOfRows];
	this->Cols = new int*[this->numOfCols];

	//setup rows
	for (int i = 0; i < this->numOfRows; i++)
	{
		this->Rows[i] = new int[this->numOfCols];
	}

	//setup cols
	for (int i = 0; i < this->numOfCols; i++)
	{
		this->Cols[i] = new int[this->numOfRows];
	}

	InitiateMatrix();

	std::cout << "called matrix constructor." << std::endl;
}


/**********   Initiation Function   ***********/
void Matrix::InitiateMatrix()
{
	// zeroing Rows
	for (int i = 0; i < this->numOfRows; i++)
	{
		for (int j = 0; j < this->numOfCols; j++)
		{
			this->Rows[i][j] = 0;
		}
	}

	//zeroing Cols
	for (int i = 0; i < this->numOfCols; i++)
	{
		for (int j = 0; j < this->numOfRows; j++)
		{
			this->Cols[i][j] = 0;
		}
	}
}


/**********   Destructor Function   ***********/
Matrix::~Matrix()
{
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

	delete this->Rows, this->Cols;
}
#pragma endregion

#pragma region Printing And Assigning Methods
/**********   Printing Function   ***********/
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


/**********   Cell Assignment Function   ***********/
void Matrix::AssignCell(int row, int col, int val)
{
	this->Rows[row][col] = val;
	this->Cols[col][row] = val;
}


/**********   Cell Getting Function   ***********/
int Matrix::GetCell(int row, int col) {
	return this->Rows[row][col];
}


/**********   Matrix Assignment Function   ***********/
void Matrix::Assign()
{
	std::cout << "Initiated assignment process..." << std::endl;
	std::cout << "Please enter first row values [" << this->numOfCols << " values each row]: " << std::endl;

	for (int i = 0; i < this->numOfRows; i++)
	{
		for (int j = 0; j < this->numOfCols; j++)
		{
			int val;
			std::cout << "[" << j+1 << "]<";
			while (!(std::cin >> val)) {
				std::cin.clear(); //clear bad input flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
				std::cout << "[Assign] Invalid input; please re-enter: " << std::endl << "[" << j << "]<";
			}
			this->Rows[i][j] = val;
			this->Cols[j][i] = val;
		}
		if (i + 1 == this->numOfRows) {
			std::cout << "done." << std::endl;
		}
		else {
			std::cout << "Row " << i + 2 << ":" << std::endl;
		}
	}
}
#pragma endregion

#pragma region Math Methods
/**********   Addition Function   ***********/
Matrix* Matrix::Addition(Matrix* m1, Matrix* m2)
{
	std::cout << "[Addition]" << std::endl;
	if (m1->numOfCols != m2->numOfCols || m1->numOfRows != m2->numOfRows) {
		// don't have the same dimensions
		std::cout << "[Add] The two matrices don't have the same dimensions, therefore cannot be added together" << std::endl;
		return nullptr;
	}

	Matrix* addedMat = new Matrix(m1->numOfRows, m1->numOfCols);

	for (int i = 0; i < m1->numOfRows; i++)
	{
		for (int j = 0; j < m1->numOfCols; j++)
		{
			int val = m1->Rows[i][j] + m2->Rows[i][j];
			addedMat->AssignCell(i, j, val);
		}
	}

	return addedMat;
}


/**********   Transpositioning Function   ***********/
void Matrix::Transpose()
{
	std::cout << "[Transpose]" << std::endl;
	//changing rows into columns
	int ** temp = this->Rows;
	this->Rows = this->Cols;
	this->Cols = temp;

	//adjusting number of rows and columns accordingly
	int temp1 = this->numOfRows;
	this->numOfRows = this->numOfCols;
	this->numOfCols = temp1;
	
	this->Print();
}


/**********   Transpositioning Function   ***********/
Matrix* Matrix::ScalarMultiplication(Matrix* m, int s) 
{
	std::cout << "[ScalarMultiplication]" << std::endl;
	for (int i = 0; i < m->numOfRows; i++)
	{
		for (int j = 0; j < m->numOfCols; j++)
		{
			m->AssignCell(i, j, m->GetCell(i, j) * s);
		}
	}

	m->Print();
	return m;
}


/**********   Add rows Function   ***********/
Matrix* Matrix::AddRows(Matrix* m, int effRow, int otherRow, int multiplier)
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
		int otherRowVal = m->Rows[otherRow][i];
		int effectedRowVal = m->Rows[effRow][i];
		m->AssignCell(effRow, i, (int)(effectedRowVal + (multiplier * otherRowVal)));
	}

	m->Print();

	return m;
}


/**********   Row Multiplication Function   ***********/
Matrix* Matrix::RowMultiplication(Matrix* m, int row, int scalar)
{
	//check out of bounds exeption
	if (row < 0 || row >= m->numOfRows) 
	{
		std::cout << "[AddRows] Out of matrix boundries, start at base 0" << std::endl;
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


/**********   Add rows Function   ***********/
Matrix* Matrix::SwitchRows(Matrix* m, int fr, int sr)
{
	//check out of bounds exeption
	if (fr < 0 || fr >= m->numOfRows || sr < 0 || sr >= m->numOfRows)
	{
		std::cout << "[SwitchRows] Out of matrix boundries, start at base 0" << std::endl;
		return nullptr;
	}
	for (int i = 0; i < m->numOfCols; i++)
	{
		int temp;
		temp = m->Rows[fr][i];
		m->AssignCell(fr, i, m->Rows[sr][i]);
		m->AssignCell(sr, i, temp);
	}

	std::cout << "[SwitchRows] " << fr + 1 << "<-->" << sr + 1 << std::endl;
	m->Print();

	return m;
}


Matrix* Matrix::Multiplication(Matrix* a, Matrix* b) 
{
	if (a->numOfCols != b->numOfRows) 
	{
		// don't have the correct dimensions
		std::cout << "[Multiplication] The matrices provided are not of the correct dimensions, therefore cannot be multiplied" << std::endl;
		return nullptr;
	}

	Matrix* c = new Matrix(a->numOfRows, b->numOfCols);
	c->InitiateMatrix();

	for (int i = 0; i < c->numOfRows; i++)
	{
		for (int j = 0; j < c->numOfCols; j++)
		{
			int* row = a->Rows[i];
			int* col = b->Cols[j];
			int sum = 0;
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
#pragma endregion



