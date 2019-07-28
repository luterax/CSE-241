#ifndef SPARSEVECTOR_H			/* It checks if header is not defined.		*/
#define SPARSEVECTOR_H			/* If header not defined then we define.	*/

#include <vector>				/* We use vector library.					*/

class SparseVector 				/* It's our vector class.					*/
{
public:							/* Our public members.						*/
	SparseVector();								/* It's default constructor.		*/							
	SparseVector(const char* filename);			/* It's our real constructor.		*/

	double getVectorData(int ind) const;		/* It returns vector's data.		*/
	int getSize() const;						/* It returns vector's size.		*/
	int getVectorIndex(int ind) const;			/* It returns vector's index.		*/

	friend const SparseVector operator+(const SparseVector& left, const SparseVector& right);		/* It's our vector addition operator function.		*/
	friend const SparseVector operator-(const SparseVector& left, const SparseVector& right);		/* It's our vector substraction operator function.	*/
	friend const SparseVector operator-(const SparseVector& neg);									/* It's our vector negative operator function.		*/
	friend std::ostream& operator<<(std::ostream& out, const SparseVector& other);					/* It's our vector print operator.					*/
	SparseVector& operator=(const SparseVector& right);												/* It's our vector assignment operator.				*/

private:						/* Our private members.						*/

	int size = 0;						/* It's our vector's size.					*/

	class Cell							/* It's our vector's members.				*/
	{
	public:								/* Our public members.						*/
		double data;					/* It's our vector's data.					*/
		int index;						/* It's our vector's index.					*/
	};

	std::vector<Cell> v;				/* It's our vector.							*/
};

double dot(const SparseVector& left, const SparseVector& right);			/* It products two vectors.			*/
int check_errors(std::ifstream *f);											/* It checks error for the file.	*/

#endif							/* We end the header.						*/