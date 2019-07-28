#include <iostream>			/* We use cout, etc.		*/
#include <string>			/* We use getline, strings.	*/
#include <fstream>			/* We use files.			*/
#include "SparseVector.h"	/* We use vector class.		*/

using namespace std;		/* We use it for cout etc.	*/

SparseVector::SparseVector(){}		/* It's our default constructor.	*/

SparseVector::SparseVector(const char* filename)					/* It's our real constructor.		*/
{
	ifstream inputFile;											/* It's our input file variable.		*/
	int i = 0, j = 0, ValueCounter = 0;							/* They are our counters.				*/
	string inputLine;											/* It's our input string.				*/
	char c, temp[50];											/* They are just temps.					*/

	inputFile.open(filename);									/* We open the file.					*/

	while(1)													/* We make a loop to read all lines.	*/
	{
		if ( inputFile.is_open() )								/* We check if our file is open.		*/
		{
			getline(inputFile, inputLine);						/* Then we get the line into our string.*/

			if ( check_errors(&inputFile) )						/* We check if there is a problem.		*/
			{
				break;											/* And we end the loop.					*/
			}

			v.resize(inputLine.length());						/* We resize our vector.				*/

			while( i < inputLine.length() )						/* We make a loop for to make partials.	*/
			{
				if ( inputLine[i] == ' ' || i+1 == inputLine.length() )	/* We check if we have any space or are we at the end.	*/
				{
					if ( i+1 == inputLine.length() )			/* We check for last element.			*/
					{
						temp[j++] = inputLine[i];				/* We assign last elements.				*/
					}

					temp[j] = '\0';								/* Then we make temp as a string.		*/
					sscanf(temp,"%d%c%lf",&v[ValueCounter].index, &c, &v[ValueCounter].data);	/* We read indexes, datas into our vector.	*/
					j = 0;										/* We re-initialize our counter.		*/
					++ValueCounter;								/* We count vectors.					*/
				}
				else											/* If we are not at space or end.		*/
				{
					temp[j] = inputLine[i];						/* We assign characters into temp.		*/
					++j;										/* We count them.						*/
				}
				++i;											/* We count inputline's characters.		*/
			}
			i = 0;
		}
	}

	size = ValueCounter;					/* We assign our size.			*/

	inputFile.close();						/* We close our file.			*/
}

double dot(const SparseVector& left, const SparseVector& right)						/* It products two vectors.		*/
{
	int max = 0, min = 0, tempRight = 0;									/* They are our counters.				*/
	double result = 0.0;													/* It's our result.						*/

	if ( left.getSize() >= right.getSize() )								/* We check which size is bigger.		*/
	{
		max = left.getSize();												/* If left then it's max.				*/
		min = right.getSize();												/* Then right is min.					*/
	}
	else																	/* If right is bigger.					*/
	{
		max = right.getSize();												/* Then max is right.					*/
		min = left.getSize();												/* And left is min.						*/
	}

	for (int i = 0; i < max; ++i)											/* We make a loop for to product.		*/
	{
		for (int j = tempRight; j < min; ++j)								/* We make a loop for to product.		*/
		{
			if ( left.getVectorIndex(i) == right.getVectorIndex(j) )		/* If indexes are same we check.		*/
			{
				result += left.getVectorData(i) * right.getVectorData(j);	/* Then we product and save it.			*/
				++tempRight;												/* We count min.						*/
				break;														/* We count max.						*/
			}
		}
	}
}

double SparseVector::getVectorData(int ind) const 	/* It returns data of vector.		*/
{ 
	return this->v[ind].data; 	/* It returns.		*/
}

int SparseVector::getSize() const 					/* It returns size of vector.		*/
{ 
	return this->size; 			/* It returns.		*/
}

int SparseVector::getVectorIndex(int ind) const 	/* It returns index of vector.		*/
{ 
	return this->v[ind].index;	/* It returns.		*/
}

const SparseVector operator+(const SparseVector& left, const SparseVector& right)			/* It makes addition in vectors.		*/
{
	SparseVector temp;											/* It's our temp vector.						*/
	int i = 0, j = 0, tempCounter = 0, countTempSize = 0,		/* They are our counters.						*/
	tempRight = 0, max = 0, min = 0;							/* They are our counter and sizes.				*/

	if ( left.size >= right.size )								/* We check whose size is bigger.				*/
	{
		max = left.size;										/* If left is bigger then its max.				*/
		min = right.size;										/* Then right is min.							*/
	}
	else														/* If right is bigger we check.					*/
	{
		max = right.size;										/* Then right is max.							*/
		min = left.size;										/* And left is min.								*/
	}

	for (int i = 0; i < left.size; ++i)							/* We make a loop for to find results size.		*/
	{
		for(int j = 0; j < right.size; ++j)						/* We make a loop for to find results size.		*/
		{
			if ( left.v[i].index == right.v[j].index )			/* We check same indexes.						*/
			{
				++countTempSize;								/* Then we count it.							*/
			}
		}
	}
	
	temp.size = left.size + right.size - countTempSize;			/* We find our temp's new size.					*/
	temp.v.resize(temp.size);									/* We resize our temp vector size.				*/

	for (i = 0; i < max; ++i)									/* We create a loop for max vector.				*/
	{
		for (j = tempRight; j < min; ++j)						/* We create a loop for min vector.				*/
		{
			if ( left.v[i].index == right.v[j].index )			/* We check if indexes are same.				*/
			{
				temp.v[tempCounter].index = left.v[i].index;	/* Then our temp's index is same with others.	*/
				temp.v[tempCounter].data = left.v[i].data + right.v[j].data;	/* We sum datas.				*/
				++tempCounter;									/* We count our vector.							*/
				++tempRight;									/* We count min vector.							*/
				break;											/* We count max vector.							*/
			}
			else if ( left.v[i].index < right.v[j].index )		/* We check if right's index is bigger.			*/
			{
				temp.v[tempCounter].index = left.v[i].index;	/* Then our index is left's.					*/
				temp.v[tempCounter].data = left.v[i].data;		/* Our data is left's.							*/
				++tempCounter;									/* We count our vector.							*/
				break;											/* We count max vector.							*/
			}
			else if ( left.v[i].index > right.v[j].index )		/* We check if left's index is bigger.			*/
			{
				temp.v[tempCounter].index = right.v[j].index;	/* Then our index is right's.					*/
				temp.v[tempCounter].data = right.v[j].data;		/* Our data is right's.							*/
				++tempRight;									/* We count min vector.							*/
				++tempCounter;									/* We count our vector.							*/
			}
		}

		if ( max == left.size && right.size == tempRight )		/* We check if our min vector is done.			*/
		{
			if ( temp.v[tempCounter-1].index == left.v[i].index )/* We check for last item.					*/
			{
				++i;											/* We count it.									*/
			}
			for (int a = 0; a < left.size - right.size; ++a)	/* Then we make a loop for min vector.			*/
			{
				temp.v[tempCounter+a].index = left.v[i+a].index;/* We count our indexes.						*/
				temp.v[tempCounter+a].data = left.v[i+a].data;	/* We count our datas.							*/
			}
			break;												/* We end the loop.								*/
		}
		else if ( max == right.size && left.size == tempRight )	/* We check if our min vector is done.			*/
		{
			if ( temp.v[tempCounter-1].index == right.v[i].index )/* We check for last item.					*/
			{
				++i;											/* We count it.									*/
			}
			for (int a = 0; a < right.size - left.size; ++a)	/* Then we make a loop for min vector.			*/
			{
				temp.v[tempCounter+a].index = right.v[i+a].index;/* We count our indexes.						*/
				temp.v[tempCounter+a].data = right.v[i+a].data;	/* We count our datas.							*/
			}
			break;												/* We end the loop.								*/
		}
	}

	return temp;												/* We return our summed vector.					*/
}

const SparseVector operator-(const SparseVector& left, const SparseVector& right)			/* It makes subtraction in vectors.		*/
{
	SparseVector temp;											/* It's our temp vector.						*/
	int i = 0, j = 0, tempCounter = 0, countTempSize = 0,		/* They are our counters.						*/
	tempRight = 0, max = 0, min = 0;							/* They are our counter and sizes.				*/

	if ( left.size >= right.size )								/* We check whose size is bigger.				*/
	{
		max = left.size;										/* If left is bigger then its max.				*/
		min = right.size;										/* Then right is min.							*/
	}
	else														/* If right is bigger we check.					*/
	{
		max = right.size;										/* Then right is max.							*/
		min = left.size;										/* And left is min.								*/
	}

	for (int i = 0; i < left.size; ++i)							/* We make a loop for to find results size.		*/
	{
		for(int j = 0; j < right.size; ++j)						/* We make a loop for to find results size.		*/
		{
			if ( left.v[i].index == right.v[j].index )			/* We check same indexes.						*/
			{
				++countTempSize;								/* Then we count it.							*/
			}
		}
	}
	
	temp.size = left.size + right.size - countTempSize;			/* We find our temp's new size.					*/
	temp.v.resize(temp.size);									/* We resize our temp vector size.				*/

	for (i = 0; i < max; ++i)									/* We create a loop for max vector.				*/
	{
		for (j = tempRight; j < min; ++j)						/* We create a loop for min vector.				*/
		{
			if ( left.v[i].index == right.v[j].index )			/* We check if indexes are same.				*/
			{
				temp.v[tempCounter].index = left.v[i].index;	/* Then our temp's index is same with others.	*/
				temp.v[tempCounter].data = left.v[i].data - right.v[j].data;	/* We subtract datas.			*/
				++tempCounter;									/* We count our vector.							*/
				++tempRight;									/* We count min vector.							*/
				break;											/* We count max vector.							*/
			}
			else if ( left.v[i].index < right.v[j].index )		/* We check if right's index is bigger.			*/
			{
				temp.v[tempCounter].index = left.v[i].index;	/* Then our index is left's.					*/
				temp.v[tempCounter].data = left.v[i].data;		/* Our data is left's.							*/
				++tempCounter;									/* We count our vector.							*/
				break;											/* We count max vector.							*/
			}
			else if ( left.v[i].index > right.v[j].index )		/* We check if left's index is bigger.			*/
			{
				temp.v[tempCounter].index = right.v[j].index;	/* Then our index is right's.					*/
				temp.v[tempCounter].data = -right.v[j].data;	/* Our data is right's.							*/
				++tempRight;									/* We count min vector.							*/
				++tempCounter;									/* We count our vector.							*/
			}
		}

		if ( max == left.size && right.size == tempRight )		/* We check if our min vector is done.			*/
		{
			if ( temp.v[tempCounter-1].index == left.v[i].index )	/* We check for last item.					*/
			{
				++i;											/* We count it.									*/
			}
			for (int a = 0; a < left.size - right.size; ++a)	/* Then we make a loop for min vector.			*/
			{
				temp.v[tempCounter+a].index = left.v[i+a].index;/* We count our indexes.						*/
				temp.v[tempCounter+a].data = left.v[i+a].data;	/* We count our datas.							*/
			}
			break;												/* We end the loop.								*/
		}
		else if ( max == right.size && left.size == tempRight )	/* We check if our min vector is done.			*/
		{
			if ( temp.v[tempCounter-1].index == right.v[i].index )/* We check for last item.					*/
			{
				++i;											/* We count it.									*/
			}
			for (int a = 0; a < right.size - left.size; ++a)	/* Then we make a loop for min vector.			*/
			{
				temp.v[tempCounter+a].index = right.v[i+a].index;/* We count our indexes.						*/
				temp.v[tempCounter+a].data = -right.v[i+a].data;/* We count our datas.							*/
			}
			break;												/* We end the loop.								*/
		}
	}

	return temp;												/* We return our subtracted vector.				*/
}

const SparseVector operator-(const SparseVector& neg)		/* It makes negative vector.	*/
{
	SparseVector temp;									/* It's our temp vector.			*/
	temp.v.resize(neg.size);							/* We resize our temp vector.		*/
	temp.size = neg.size;								/* We assign size to our temp.		*/

	for (int i = 0; i < neg.size; ++i)					/* We make loop in our vector.		*/
	{
		temp.v[i].index = neg.v[i].index;				/* We assign indexes to temp.		*/
		temp.v[i].data = neg.v[i].data * -1;			/* We make a negative vector.		*/
	}

	return temp;										/* We return our negative vector.	*/
}

ostream& operator<<(ostream& out, const SparseVector& other)		/* It prints vectors.	*/
{
	for (int i = 0; i < other.size; ++i)						/* It makes a loop to print all datas.	*/
	{
		out << other.v[i].index << ":";							/* It prints index and ':' character.	*/
		out.setf(ios::fixed);									/* It fix to print.						*/
		out.setf(ios::showpoint);								/* It shows points.						*/
		out.precision(1);										/* It defines how many point prints.	*/
		out << other.v[i].data << " ";							/* It prints datas and spaces.			*/
	}

	out << endl;												/* It prints end of line.				*/

	return out;													/* It returns to print others.			*/
}

SparseVector& SparseVector::operator=(const SparseVector& right)	/* It assigns vectors.			*/
{
	if ( this == &right )					/* It checks if its same left and right.	*/
	{
		return *this;						/* Then we return left.						*/
	}
	else									/* If it is not same it checks.				*/
		v.clear();							/* We clear our vector.						*/
		size = right.size;					/* Then it makes same sizes.				*/
		v.resize(size);						/* We resize our vector.					*/
		
		for (int i = 0; i < size; ++i)		/* It creates a loop to make same vectors.	*/
		{
			v[i].data = right.v[i].data;	/* It makes same datas.						*/
			v[i].index = right.v[i].index;	/* It makes same indexes.					*/
		}

	return *this;							/* We return our new vector.				*/
}

int check_errors(ifstream *f)	/* It checks if file openned or not.		*/
{
	int stop = 0;		/* It's our flag.							*/

	if( f->eof() )		/* It checks if it's in end of file.		*/
	{
		stop = 0;		/* Then we make it zero.					*/
	}
	if( f->fail() )		/* It checks if it failed.					*/
	{
		stop = 1;		/* Then we make it one.						*/
	}
	if( f->bad() )		/* It checks if it's bad.					*/
	{
		stop = 1;		/* Then we make it one.						*/
	}

	return stop;		/* We return our result.					*/
}