// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "matrices.h"
#include <iostream>

int main()
{
	/*Matrix* d1 = new Matrix(2,2);
	d1->Assign();
	d1->Print();

	Matrix* d2 = new Matrix(2,2);
	d2->Assign();
	d2->Print();

	Matrix* c = Matrix::Multiplication(d1, d2);

	delete d1,d2,c;*/

	Matrix* a = new Matrix(2, 2);
	a->Assign();
	a->Print();
	a->RowMultiplication(a, 1, 7);

	delete a;

    return 0;
}

