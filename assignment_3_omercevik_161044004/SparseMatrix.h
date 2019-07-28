#ifndef SPARSEMATRIX_H			/* It checks if header is not defined.		*/
#define SPARSEMATRIX_H			/* If header not defined then we define.	*/

#include <vector>				/* We use vector library.					*/

class SparseMatrix 				/* It's our vector class.					*/
{
public:							/* Our public members.						*/
	SparseMatrix();								/* It's default constructor.		*/	
	SparseMatrix(const char* filename);			/* It's our real constructor.		*/

	friend const SparseMatrix operator+(const SparseMatrix& left,const SparseMatrix& right);		/* It's our matrix addition operator function.			*/
	friend const SparseMatrix operator-(const SparseMatrix& left,const SparseMatrix& right);		/* It's our matrix substraction operator function.		*/
	friend const SparseMatrix operator-(const SparseMatrix& neg);									/* It's our matrix negative operator function.			*/
	friend const SparseMatrix operator*(const SparseMatrix& left,const SparseMatrix& right);		/* It's our matrix multiplication operator function.	*/
	SparseMatrix& operator=(const SparseMatrix& right);												/* It's our matrix assignment operator.					*/
	friend std::ostream& operator<<(std::ostream& out,const SparseMatrix& other);					/* It's our matrix print operator.						*/
	const SparseMatrix transpose();																	/* It's our matrix transpose function.					*/

private:							/* Our private members.						*/

	std::vector<int> size;				/* Our size vector.							*/

	std::vector<int> indexOfRow;		/* Our row indexes vector.					*/

	int sizeRow = 0;					/* Size of rows.							*/

	class Cell							/* It's our vector's members.				*/
	{
	public:								/* Our public members.						*/
		double data;					/* It's our vector's data.					*/
		int index;						/* It's our vector's index.					*/
	};

	std::vector< std::vector<Cell> >v;	/* It's our 2D vector.						*/
};

int check_errors(std::ifstream *f);		/* It checks if file is openned or not.		*/

#endif							/* We end the header.						*/