#include <iostream>			/* We use cout, etc.		*/
#include <fstream>			/* We use files.			*/
#include "SparseMatrix.h"	/* It's our library.		*/

using namespace std;		/* We use it for cout etc.	*/

SparseMatrix::SparseMatrix(){}						/* Default constructor.				*/

SparseMatrix::SparseMatrix(const char* filename)	/* Real constructor.				*/
{
	ifstream inputFile;											/* Our file reader.						*/
	int i = 0, j = 0, ValueCounter = 0;							/* They are our counters.				*/
	string inputLine;											/* It's our input string.				*/
	char c, temp[50];											/* They are just temps.					*/
	inputFile.open(filename);									/* They are our temps.					*/

	if ( inputFile.is_open() )									/* We check if it's open.				*/
	{
		while(1)												/* We make a loop to get lines.			*/
		{
			getline(inputFile, inputLine);						/* We read lines.						*/

			if ( check_errors(&inputFile) )						/* We check errors.						*/
			{
				break;											/* If there is something wrong we out.	*/
			}

			indexOfRow.resize(sizeRow+1);						/* Initialize row index vector size.	*/
			v.resize(sizeRow+1);								/* Initialize vector size.				*/
			v[sizeRow].resize(inputLine.length());				/* Initialize vector size's 2D.			*/

			while( i < inputLine.length() )								/* We make a loop for to make partials.	*/
			{
				if ( inputLine[i] == ' ' || i+1 == inputLine.length() )	/* We check if we have any space or are we at the end.	*/
				{
					if ( i+1 == inputLine.length() )			/* We check for the last element.		*/
					{
						temp[j++] = inputLine[i];				/* We assign our last elements.			*/
					}

					temp[j] = '\0';								/* Then we make temp as a string.		*/

					if ( i == 1 )								/* We check for indexRow.				*/
					{
						sscanf(temp,"%d",&indexOfRow[sizeRow]);	/* We assign index row.					*/
					}
					else
					{
						sscanf(temp,"%d%c%lf",&v[sizeRow][ValueCounter].index, &c, &v[sizeRow][ValueCounter].data);	/* We read indexes, datas into our vector.	*/
						++ValueCounter;								/* We count vectors.					*/
					}
					j = 0;										/* We re-initialize our counter.		*/
				}
				else											/* If we are not at space or end.		*/
				{
					temp[j] = inputLine[i];						/* We assign characters into temp.		*/
					++j;										/* We count them.						*/
				}
				++i;											/* We count inputline's characters.		*/
			}
			size.resize(sizeRow+1);								/* We initialize our size.				*/
			size[sizeRow] = ValueCounter;						/* We initialize our size's 2D.			*/
			ValueCounter = 0;									/* Re-initialize Valuecounter.			*/
			++sizeRow;											/* Count size row.						*/
			i = 0;												/* Re-initialize i.						*/
		}
	}
}

const SparseMatrix SparseMatrix::transpose(){}			/* It's our transpose function. Not Initialized!! 	*/

const SparseMatrix operator+(const SparseMatrix& left,const SparseMatrix& right)		/* It makes addition two matrixes.		*/
{
	SparseMatrix temp;															/* It's our temp vector.						*/
	int i = 0, j = 0, tempCounter = 0, countTempSizeRow = 0, l = 0, k = 0, 		/* They are our counters.						*/
	countTempSize = 0, tempRight = 0, max = 0, min = 0, t = 0, tempLeft = 0;	/* They are our counter and sizes.				*/

	if ( left.sizeRow >= right.sizeRow )										/* We check whose sizeRow is bigger.			*/
	{
		max = left.sizeRow;														/* If left is bigger then its max.				*/
		min = right.sizeRow;													/* Then right is min.							*/
	}
	else																		/* If right is bigger we check.					*/
	{
		max = right.sizeRow;													/* Then right is max.							*/
		min = left.sizeRow;														/* And left is min.								*/
	}

	for (int i = 0; i < left.sizeRow; ++i)							/* We make a loop for to find results sizeRow.		*/
	{
		for(int j = 0; j < right.sizeRow; ++j)						/* We make a loop for to find results sizeRow.		*/
		{
			if ( left.indexOfRow[i] == right.indexOfRow[j] )		/* We check indexes.								*/
			{
				++countTempSizeRow;									/* We count index rows.								*/
			}
		}
	}

	temp.sizeRow = left.sizeRow + right.sizeRow - countTempSizeRow;	/* We find our temp's new size.					*/
	temp.v.resize(temp.sizeRow);									/* We resize our temp matrix size.				*/
	temp.indexOfRow.resize(temp.sizeRow);							/* We resize our temp matrix indexrow.			*/
	temp.size.resize(temp.sizeRow);									/* We resize our temp matrix row sizes.			*/

	for (int i = 0; i < max; ++i)									/* We make a loop to resize temp.				*/
	{
		for (int j = 0; j < min; ++j)								/* We make a loop to resize temp.				*/
		{	
			if ( left.indexOfRow[i] == right.indexOfRow[j] )		/* We check same indexes of rows.				*/
			{
				for (int l = 0; l < left.size[i]; ++l)				/* We make a loop to check same vectors.		*/
				{
					for (int k = 0; k < right.size[j]; ++k)			/* We make a loop to check same vecors.			*/
					{
						++countTempSize;							/* We count them.								*/
					}
					temp.v[i].resize(left.size[i] + right.size[j] - countTempSize);		/* We resize temp vector's 2D. 	*/
					countTempSize = 0;													/* Re-initialize counttempsize.	*/
				}
			}
			else if ( left.indexOfRow[i] > right.indexOfRow[j] )	/* We check if index of row is bigger.			*/
			{
				temp.v[i].resize(left.size[i]);						/* We resize temp.								*/
			}
		}
	}

	for (i = 0; i < max; ++i)											/* We create a loop for max vector.				*/
	{
		for (j = tempLeft; j < min; ++j)								/* We create a loop for min vector.				*/
		{
			if ( left.indexOfRow[i] == right.indexOfRow[j] )			/* We check if index of rows are same.			*/
			{
				temp.indexOfRow[t] = left.indexOfRow[i];				/* Then we assign them.							*/

				for (l = 0; l < left.size[i]; ++l)						/* We make a loop in left matrix.				*/
				{
					for (k = tempRight; k < right.size[j]; ++k)			/* We make a loop in right matrix.				*/
					{
						if ( left.v[i][l].index == right.v[j][k].index )							/* We check if indexes are same.				*/
						{
							temp.v[t][tempCounter].index = left.v[i][l].index;						/* Then our temp's index is same with others.	*/
							temp.v[t][tempCounter].data = left.v[i][l].data + right.v[j][k].data;	/* We sum datas.								*/
							++tempCounter;															/* We count our vector.							*/
							++tempRight;															/* We count min vector.							*/
							break;																	/* We count max vector.							*/
						}
						else if ( left.v[i][l].index < right.v[j][k].index )		/* We check if right's index is bigger.			*/
						{
							temp.v[t][tempCounter].index = left.v[i][l].index;		/* Then our index is left's.					*/
							temp.v[t][tempCounter].data = left.v[i][l].data;		/* Our data is left's.							*/
							++tempCounter;											/* We count our vector.							*/
							break;													/* We count max vector.							*/
						}
						else if ( left.v[i][l].index > right.v[j][k].index )		/* We check if left's index is bigger.			*/
						{
							temp.v[t][tempCounter].index = right.v[j][k].index;		/* Then our index is right's.					*/
							temp.v[t][tempCounter].data = right.v[j][k].data;		/* Our data is right's.							*/
							++tempRight;											/* We count min vector.							*/
							++tempCounter;											/* We count our vector.							*/
						}
					}

					if ( right.size[j] == tempRight )								/* We check if our min vector is done.			*/
					{
						if ( temp.v[t][tempCounter-1].index == left.v[i][l].index )	/* We check for last item.					*/
						{
							++l;													/* We count it.									*/
						}
						for (int a = 0; a < left.size[i] - right.size[j]; ++a)		/* Then we make a loop for min vector.			*/
						{
							temp.v[t][tempCounter+a].index = left.v[i][l+a].index;	/* We count our indexes.						*/
							temp.v[t][tempCounter+a].data = left.v[i][l+a].data;	/* We count our datas.							*/
						}
						break;														/* We end the loop.								*/
					}
				}
				temp.size[t] = tempCounter;											/* We resize temp's size.						*/
				++t;																/* We count temp.								*/
				tempRight = 0;														/* Reinitilialize tempright.					*/
				tempCounter = 0;													/* Reinitilialize tempcounter.					*/
				++tempLeft;															/* Reinitilialize templeft.						*/
				break;																/* We count i.									*/
			}
			else if ( left.indexOfRow[i] < right.indexOfRow[j] )					/* We check if left's index of row is lesser.	*/
			{
				temp.indexOfRow[t] = left.indexOfRow[i];							/* We assign left's to temp.					*/

				for (l = 0; l < left.size[i]; ++l)									/* We make a loop in left matrix.				*/
				{
					for (k = tempRight; k < right.size[j]; ++k)						/* We make a loop in right matrix.				*/
					{
						if ( left.v[i][l].index == right.v[j][k].index )							/* We check if indexes are same.				*/
						{
							temp.v[t][tempCounter].index = left.v[i][l].index;						/* Then our temp's index is same with others.	*/
							temp.v[t][tempCounter].data = left.v[i][l].data + right.v[j][k].data;	/* We sum datas.								*/
							++tempCounter;															/* We count our vector.							*/
							++tempRight;															/* We count min vector.							*/
							break;																	/* We count max vector.							*/
						}
						else if ( left.v[i][l].index < right.v[j][k].index )		/* We check if right's index is bigger.			*/
						{						
							temp.v[t][tempCounter].index = left.v[i][l].index;		/* Then our index is left's.					*/
							temp.v[t][tempCounter].data = left.v[i][l].data;		/* Our data is left's.							*/
							++tempCounter;											/* We count our vector.							*/
							break;													/* We count max vector.							*/
						}
						else if ( left.v[i][l].index > right.v[j][k].index )		/* We check if left's index is bigger.			*/
						{
							temp.v[t][tempCounter].index = right.v[j][k].index;		/* Then our index is right's.					*/
							temp.v[t][tempCounter].data = right.v[j][k].data;		/* Our data is right's.							*/
							++tempRight;											/* We count min vector.							*/
							++tempCounter;											/* We count our vector.							*/
						}
					}

					if ( right.size[j] == tempRight )								/* We check if our min vector is done.			*/
					{
						if ( temp.v[t][tempCounter-1].index == left.v[i][l].index )	/* We check for last item.						*/
						{
							++l;													/* We count it.									*/
						}
						for (int a = 0; a < left.size[i] - right.size[j]; ++a)		/* Then we make a loop for min vector.			*/
						{
							temp.v[t][tempCounter+a].index = left.v[i][l+a].index;	/* We count our indexes.						*/
							temp.v[t][tempCounter+a].data = left.v[i][l+a].data;	/* We count our datas.							*/
						}
						break;														/* We end the loop.								*/
					}
				}

				temp.size[t] = tempCounter;											/* We resize temp's size.						*/
				++t;																/* We count temp.								*/
				tempRight = 0;														/* Reinitilialize tempright.					*/
				tempCounter = 0;													/* Reinitilialize tempcounter.					*/
				break;																/* We count i.									*/
			}
			else if ( left.indexOfRow[i] > right.indexOfRow[j] )					/* We check if left is bigger.					*/
			{
				temp.indexOfRow[t] = right.indexOfRow[j];							/* Then we assign right to temp.				*/

				for (l = 0; l < left.size[i]; ++l)									/* We make a loop in left matrix.				*/
				{
					for (k = tempRight; k < right.size[j]; ++k)						/* We make a loop in right matrix.				*/
					{
						if ( left.v[i][l].index == right.v[j][k].index )							/* We check if indexes are same.				*/
						{
							temp.v[t][tempCounter].index = left.v[i][l].index;						/* Then our temp's index is same with others.	*/
							temp.v[t][tempCounter].data = left.v[i][l].data + right.v[j][k].data;	/* We sum datas.								*/
							++tempCounter;															/* We count our vector.							*/
							++tempRight;															/* We count min vector.							*/
							break;																	/* We count max vector.							*/
						}
						else if ( left.v[i][l].index < right.v[j][k].index )		/* We check if right's index is bigger.			*/
						{
							temp.v[t][tempCounter].index = left.v[i][l].index;		/* Then our index is left's.					*/
							temp.v[t][tempCounter].data = left.v[i][l].data;		/* Our data is left's.							*/
							++tempCounter;											/* We count our vector.							*/
							break;													/* We count max vector.							*/
						}
						else if ( left.v[i][l].index > right.v[j][k].index )		/* We check if left's index is bigger.			*/
						{
							temp.v[t][tempCounter].index = right.v[j][k].index;		/* Then our index is right's.					*/
							temp.v[t][tempCounter].data = right.v[j][k].data;		/* Our data is right's.							*/
							++tempRight;											/* We count min vector.							*/
							++tempCounter;											/* We count our vector.							*/
						}
					}

					if ( right.size[j] == tempRight )								/* We check if our min vector is done.			*/
					{
						if ( temp.v[t][tempCounter-1].index == left.v[i][l].index )	/* We check for last item.					*/
						{
							++l;													/* We count it.									*/
						}
						for (int a = 0; a < left.size[i] - right.size[j]; ++a)		/* Then we make a loop for min vector.			*/
						{
							temp.v[t][tempCounter+a].index = left.v[i][l+a].index;	/* We count our indexes.						*/
							temp.v[t][tempCounter+a].data = left.v[i][l+a].data;	/* We count our datas.							*/
						}
						break;														/* We end the loop.								*/
					}
				}

				temp.size[t] = tempCounter;											/* We resize temp's size.						*/
				++t;																/* We count temp.								*/
				tempRight = 0;														/* Reinitilialize tempright.					*/
				tempCounter = 0;													/* Reinitilialize tempcounter.					*/
				++tempLeft;															/* Reinitilialize templeft.						*/
				break;																/* We count i.									*/
			}

			if ( tempLeft == min )													/* We check it for last elements.				*/
			{
				for (int a = 0; a < max - min; ++a)									/* We make a loop for last elements.			*/
				{
					for (int b = 0; b < left.size[i+a]; ++b)						/* We make a loop for last elements.			*/
					{
						temp.v[t][tempCounter+b].index = left.v[i][b].index;		/* We assign last elements indexes.				*/
						temp.v[t][tempCounter+b].data = left.v[i][b].data;			/* We assign last elements datas.				*/
					}
				}
			}
		}
	}

	return temp;												/* We return our summed matrix.					*/
}

const SparseMatrix operator-(const SparseMatrix& left,const SparseMatrix& right)		/* It's our subtraction matrix function.	*/
{
	SparseMatrix temp;															/* It's our temp vector.						*/
	int i = 0, j = 0, tempCounter = 0, countTempSizeRow = 0, l = 0, k = 0, 		/* They are our counters.						*/
	countTempSize = 0, tempRight = 0, max = 0, min = 0, t = 0, tempLeft = 0;	/* They are our counter and sizes.				*/

	if ( left.sizeRow >= right.sizeRow )										/* We check whose sizeRow is bigger.			*/
	{
		max = left.sizeRow;														/* If left is bigger then its max.				*/
		min = right.sizeRow;													/* Then right is min.							*/
	}
	else																		/* If right is bigger we check.					*/
	{
		max = right.sizeRow;													/* Then right is max.							*/
		min = left.sizeRow;														/* And left is min.								*/
	}

	for (int i = 0; i < left.sizeRow; ++i)							/* We make a loop for to find results sizeRow.		*/
	{
		for(int j = 0; j < right.sizeRow; ++j)						/* We make a loop for to find results sizeRow.		*/
		{
			if ( left.indexOfRow[i] == right.indexOfRow[j] )		/* We check indexes.								*/
			{
				++countTempSizeRow;									/* We count index rows.								*/
			}
		}
	}

	temp.sizeRow = left.sizeRow + right.sizeRow - countTempSizeRow;	/* We find our temp's new size.					*/
	temp.v.resize(temp.sizeRow);									/* We resize our temp matrix size.				*/
	temp.indexOfRow.resize(temp.sizeRow);							/* We resize our temp matrix indexrow.			*/
	temp.size.resize(temp.sizeRow);									/* We resize our temp matrix row sizes.			*/

	for (int i = 0; i < max; ++i)									/* We make a loop to resize temp.				*/
	{
		for (int j = 0; j < min; ++j)								/* We make a loop to resize temp.				*/
		{	
			if ( left.indexOfRow[i] == right.indexOfRow[j] )		/* We check same indexes of rows.				*/
			{
				for (int l = 0; l < left.size[i]; ++l)				/* We make a loop to check same vectors.		*/
				{
					for (int k = 0; k < right.size[j]; ++k)			/* We make a loop to check same vecors.			*/
					{
						++countTempSize;							/* We count them.								*/
					}
					temp.v[i].resize(left.size[i] + right.size[j] - countTempSize);		/* We resize temp vector's 2D. 	*/
					countTempSize = 0;													/* Re-initialize counttempsize.	*/
				}
			}
			else if ( left.indexOfRow[i] > right.indexOfRow[j] )	/* We check if index of row is bigger.			*/
			{
				temp.v[i].resize(left.size[i]);						/* We resize temp.								*/
			}
		}
	}

	for (i = 0; i < max; ++i)											/* We create a loop for max vector.				*/
	{
		for (j = tempLeft; j < min; ++j)								/* We create a loop for min vector.				*/
		{
			if ( left.indexOfRow[i] == right.indexOfRow[j] )			/* We check if index of rows are same.			*/
			{
				temp.indexOfRow[t] = left.indexOfRow[i];				/* Then we assign them.							*/

				for (l = 0; l < left.size[i]; ++l)						/* We make a loop in left matrix.				*/
				{
					for (k = tempRight; k < right.size[j]; ++k)			/* We make a loop in right matrix.				*/
					{
						if ( left.v[i][l].index == right.v[j][k].index )							/* We check if indexes are same.				*/
						{
							temp.v[t][tempCounter].index = left.v[i][l].index;						/* Then our temp's index is same with others.	*/
							temp.v[t][tempCounter].data = left.v[i][l].data - right.v[j][k].data;	/* We subtract datas.							*/
							++tempCounter;															/* We count our vector.							*/
							++tempRight;															/* We count min vector.							*/
							break;																	/* We count max vector.							*/
						}
						else if ( left.v[i][l].index < right.v[j][k].index )		/* We check if right's index is bigger.			*/
						{
							temp.v[t][tempCounter].index = left.v[i][l].index;		/* Then our index is left's.					*/
							temp.v[t][tempCounter].data = left.v[i][l].data;		/* Our data is left's.							*/
							++tempCounter;											/* We count our vector.							*/
							break;													/* We count max vector.							*/
						}
						else if ( left.v[i][l].index > right.v[j][k].index )		/* We check if left's index is bigger.			*/
						{
							temp.v[t][tempCounter].index = right.v[j][k].index;		/* Then our index is right's.					*/
							temp.v[t][tempCounter].data = -right.v[j][k].data;		/* Our data is right's.							*/
							++tempRight;											/* We count min vector.							*/
							++tempCounter;											/* We count our vector.							*/
						}
					}

					if ( right.size[j] == tempRight )								/* We check if our min vector is done.			*/
					{
						if ( temp.v[t][tempCounter-1].index == left.v[i][l].index )	/* We check for last item.					*/
						{
							++l;													/* We count it.									*/
						}
						for (int a = 0; a < left.size[i] - right.size[j]; ++a)		/* Then we make a loop for min vector.			*/
						{
							temp.v[t][tempCounter+a].index = left.v[i][l+a].index;	/* We count our indexes.						*/
							temp.v[t][tempCounter+a].data = left.v[i][l+a].data;	/* We count our datas.							*/
						}
						break;														/* We end the loop.								*/
					}
				}
				temp.size[t] = tempCounter;											/* We resize temp's size.						*/
				++t;																/* We count temp.								*/
				tempRight = 0;														/* Reinitilialize tempright.					*/
				tempCounter = 0;													/* Reinitilialize tempcounter.					*/
				++tempLeft;															/* Reinitilialize templeft.						*/
				break;																/* We count i.									*/
			}
			else if ( left.indexOfRow[i] < right.indexOfRow[j] )					/* We check if left's index of row is lesser.	*/
			{
				temp.indexOfRow[t] = left.indexOfRow[i];							/* We assign left's to temp.					*/

				for (l = 0; l < left.size[i]; ++l)									/* We make a loop in left matrix.				*/
				{
					for (k = tempRight; k < right.size[j]; ++k)						/* We make a loop in right matrix.				*/
					{
						if ( left.v[i][l].index == right.v[j][k].index )							/* We check if indexes are same.				*/
						{
							temp.v[t][tempCounter].index = left.v[i][l].index;						/* Then our temp's index is same with others.	*/
							temp.v[t][tempCounter].data = left.v[i][l].data - right.v[j][k].data;	/* We subtract datas.							*/
							++tempCounter;															/* We count our vector.							*/
							++tempRight;															/* We count min vector.							*/
							break;																	/* We count max vector.							*/
						}
						else if ( left.v[i][l].index < right.v[j][k].index )		/* We check if right's index is bigger.			*/
						{						
							temp.v[t][tempCounter].index = left.v[i][l].index;		/* Then our index is left's.					*/
							temp.v[t][tempCounter].data = left.v[i][l].data;		/* Our data is left's.							*/
							++tempCounter;											/* We count our vector.							*/
							break;													/* We count max vector.							*/
						}
						else if ( left.v[i][l].index > right.v[j][k].index )		/* We check if left's index is bigger.			*/
						{
							temp.v[t][tempCounter].index = right.v[j][k].index;		/* Then our index is right's.					*/
							temp.v[t][tempCounter].data = -right.v[j][k].data;		/* Our data is right's.							*/
							++tempRight;											/* We count min vector.							*/
							++tempCounter;											/* We count our vector.							*/
						}
					}

					if ( right.size[j] == tempRight )								/* We check if our min vector is done.			*/
					{
						if ( temp.v[t][tempCounter-1].index == left.v[i][l].index )	/* We check for last item.						*/
						{
							++l;													/* We count it.									*/
						}
						for (int a = 0; a < left.size[i] - right.size[j]; ++a)		/* Then we make a loop for min vector.			*/
						{
							temp.v[t][tempCounter+a].index = left.v[i][l+a].index;	/* We count our indexes.						*/
							temp.v[t][tempCounter+a].data = left.v[i][l+a].data;	/* We count our datas.							*/
						}
						break;														/* We end the loop.								*/
					}
				}

				temp.size[t] = tempCounter;											/* We resize temp's size.						*/
				++t;																/* We count temp.								*/
				tempRight = 0;														/* Reinitilialize tempright.					*/
				tempCounter = 0;													/* Reinitilialize tempcounter.					*/
				break;																/* We count i.									*/
			}
			else if ( left.indexOfRow[i] > right.indexOfRow[j] )					/* We check if left is bigger.					*/
			{
				temp.indexOfRow[t] = right.indexOfRow[j];							/* Then we assign right to temp.				*/

				for (l = 0; l < left.size[i]; ++l)									/* We make a loop in left matrix.				*/
				{
					for (k = tempRight; k < right.size[j]; ++k)						/* We make a loop in right matrix.				*/
					{
						if ( left.v[i][l].index == right.v[j][k].index )							/* We check if indexes are same.				*/
						{
							temp.v[t][tempCounter].index = left.v[i][l].index;						/* Then our temp's index is same with others.	*/
							temp.v[t][tempCounter].data = left.v[i][l].data - right.v[j][k].data;	/* We subtract datas.							*/
							++tempCounter;															/* We count our vector.							*/
							++tempRight;															/* We count min vector.							*/
							break;																	/* We count max vector.							*/
						}
						else if ( left.v[i][l].index < right.v[j][k].index )		/* We check if right's index is bigger.			*/
						{
							temp.v[t][tempCounter].index = left.v[i][l].index;		/* Then our index is left's.					*/
							temp.v[t][tempCounter].data = left.v[i][l].data;		/* Our data is left's.							*/
							++tempCounter;											/* We count our vector.							*/
							break;													/* We count max vector.							*/
						}
						else if ( left.v[i][l].index > right.v[j][k].index )		/* We check if left's index is bigger.			*/
						{
							temp.v[t][tempCounter].index = right.v[j][k].index;		/* Then our index is right's.					*/
							temp.v[t][tempCounter].data = -right.v[j][k].data;		/* Our data is right's.							*/
							++tempRight;											/* We count min vector.							*/
							++tempCounter;											/* We count our vector.							*/
						}
					}

					if ( right.size[j] == tempRight )								/* We check if our min vector is done.			*/
					{
						if ( temp.v[t][tempCounter-1].index == left.v[i][l].index )	/* We check for last item.					*/
						{
							++l;													/* We count it.									*/
						}
						for (int a = 0; a < left.size[i] - right.size[j]; ++a)		/* Then we make a loop for min vector.			*/
						{
							temp.v[t][tempCounter+a].index = left.v[i][l+a].index;	/* We count our indexes.						*/
							temp.v[t][tempCounter+a].data = left.v[i][l+a].data;	/* We count our datas.							*/
						}
						break;														/* We end the loop.								*/
					}
				}

				temp.size[t] = tempCounter;											/* We resize temp's size.						*/
				++t;																/* We count temp.								*/
				tempRight = 0;														/* Reinitilialize tempright.					*/
				tempCounter = 0;													/* Reinitilialize tempcounter.					*/
				++tempLeft;															/* Reinitilialize templeft.						*/
				break;																/* We count i.									*/
			}

			if ( tempLeft == min )													/* We check it for last elements.				*/
			{
				for (int a = 0; a < max - min; ++a)									/* We make a loop for last elements.			*/
				{
					for (int b = 0; b < left.size[i+a]; ++b)						/* We make a loop for last elements.			*/
					{
						temp.v[t][tempCounter+b].index = left.v[i][b].index;		/* We assign last elements indexes.				*/
						temp.v[t][tempCounter+b].data = left.v[i][b].data;			/* We assign last elements datas.				*/
					}
				}
			}
		}
	}

	return temp;												/* We return our subtracted matrix.					*/
}

const SparseMatrix operator*(const SparseMatrix& left,const SparseMatrix& right)		/* It's our multiplication matrix.			*/
{
	SparseMatrix temp;															/* It's our temp vector.						*/
	int i = 0, j = 0, tempCounter = 0, countTempSizeRow = 0, l = 0, k = 0, 		/* They are our counters.						*/
	countTempSize = 0, tempRight = 0, max = 0, min = 0, t = 0;					/* They are our counter and sizes.				*/

	if ( left.sizeRow >= right.sizeRow )										/* We check whose sizeRow is bigger.			*/
	{
		max = left.sizeRow;														/* If left is bigger then its max.				*/
		min = right.sizeRow;													/* Then right is min.							*/
	}
	else																		/* If right is bigger we check.					*/
	{
		max = right.sizeRow;													/* Then right is max.							*/
		min = left.sizeRow;														/* And left is min.								*/
	}

	for (int i = 0; i < left.sizeRow; ++i)							/* We make a loop for to find results sizeRow.		*/
	{
		for(int j = 0; j < right.sizeRow; ++j)						/* We make a loop for to find results sizeRow.		*/
		{
			if ( left.indexOfRow[i] == right.indexOfRow[j] )
			{
				++countTempSizeRow;
			}
		}
	}
	
	temp.sizeRow = left.sizeRow + right.sizeRow - countTempSizeRow;	/* We find our temp's new size.					*/
	temp.v.resize(temp.sizeRow);									/* We resize our temp vector size.				*/

	for (int i = 0; i < temp.sizeRow; ++i)
	{
		for (int j = 0; j < left.sizeRow; ++j)
		{
			for (int k = 0; k < right.size[j]; ++k)
			{
				if ( left.v[i][k].index == right.v[j][k].index )
				{
					++countTempSize;
				}
			}
		}
		temp.v[i].resize(countTempSize);
	}

	for (i = 0; i < max; ++i)									/* We create a loop for max vector.				*/
	{
		for (j = 0; j < min; ++j)								/* We create a loop for min vector.				*/
		{
			if ( left.indexOfRow[i] == right.indexOfRow[j] )
			{
				if ( left.size[i] >= right.size[j] )
				{
					for (l = 0; l < left.size[i]; ++l)
					{
						for (k = tempRight; k < right.size[j]; ++k)
						{
							if ( left.v[i][l].index == right.v[i][k].index )	/* We check if indexes are same.				*/
							{
								temp.v[t][tempCounter].index = left.v[i][l].index;						/* Then our temp's index is same with others.	*/
								temp.v[t][tempCounter].data = left.v[i][l].data * right.v[i][k].data;	/* We sum datas.								*/
								++tempCounter;									/* We count our vector.							*/
								++tempRight;									/* We count min vector.							*/
								break;											/* We count max vector.							*/
							}
							else if ( left.v[i][l].index < right.v[i][k].index )		/* We check if right's index is bigger.			*/
							{
								temp.v[t][tempCounter].index = left.v[i][l].index;		/* Then our index is left's.					*/
								temp.v[t][tempCounter].data = 0.0;		/* Our data is left's.							*/
								++tempCounter;											/* We count our vector.							*/
								break;													/* We count max vector.							*/
							}
							else if ( left.v[i][l].index > right.v[i][k].index )		/* We check if left's index is bigger.			*/
							{
								temp.v[t][tempCounter].index = right.v[i][k].index;		/* Then our index is right's.					*/
								temp.v[t][tempCounter].data = 0.0;		/* Our data is right's.							*/
								++tempRight;											/* We count min vector.							*/
								++tempCounter;											/* We count our vector.							*/
							}
						}

						if ( right.size[j] == tempRight )								/* We check if our min vector is done.			*/
						{
							if ( temp.v[t][tempCounter-1].index == left.v[i][l].index )/* We check for last item.					*/
							{
								++l;											/* We count it.									*/
							}
							for (int a = 0; a < left.size[i] - right.size[j]; ++a)	/* Then we make a loop for min vector.			*/
							{
								temp.v[t][tempCounter+a].index = left.v[i][l+a].index;/* We count our indexes.						*/
								temp.v[t][tempCounter+a].data = 0.0;	/* We count our datas.							*/
							}
							break;												/* We end the loop.								*/
						}
						++t;
					}
				}
				else
				{
					for (l = 0; l < right.size[i]; ++l)
					{
						for (k = tempRight; k < left.size[j]; ++k)
						{
							if ( left.v[i][l].index == right.v[j][k].index )	/* We check if indexes are same.				*/
							{
								temp.v[t][tempCounter].index = left.v[i][l].index;						/* Then our temp's index is same with others.	*/
								temp.v[t][tempCounter].data = left.v[i][l].data * right.v[j][k].data;	/* We sum datas.								*/
								++tempCounter;									/* We count our vector.							*/
								++tempRight;									/* We count min vector.							*/
								break;											/* We count max vector.							*/
							}
							else if ( left.v[i][l].index < right.v[j][k].index )		/* We check if right's index is bigger.			*/
							{
								temp.v[t][tempCounter].index = left.v[i][l].index;		/* Then our index is left's.					*/
								temp.v[t][tempCounter].data = 0.0;						/* Our data is left's.							*/
								++tempCounter;											/* We count our vector.							*/
								break;													/* We count max vector.							*/
							}
							else if ( left.v[i][l].index > right.v[j][k].index )		/* We check if left's index is bigger.			*/
							{
								temp.v[t][tempCounter].index = right.v[j][k].index;		/* Then our index is right's.					*/
								temp.v[t][tempCounter].data = 0.0;						/* Our data is right's.							*/
								++tempRight;											/* We count min vector.							*/
								++tempCounter;											/* We count our vector.							*/
							}
						}

						if ( left.size[i] == tempRight )								/* We check if our min vector is done.			*/
						{
							if ( temp.v[t][tempCounter-1].index == right.v[j][l].index )/* We check for last item.					*/
							{
								++l;											/* We count it.									*/
							}
							for (int a = 0; a < right.size[j] - left.size[i]; ++a)	/* Then we make a loop for min vector.			*/
							{
								temp.v[t][tempCounter+a].index = right.v[i][l+a].index;/* We count our indexes.						*/
								temp.v[t][tempCounter+a].data = 0.0;					/* We count our datas.							*/
							}
							break;												/* We end the loop.								*/
						}
						++t;
					}
				}
			}
		}
	}

	return temp;												/* We return our summed vector.					*/
}

const SparseMatrix operator-(const SparseMatrix& neg)					/* It makes a negative matrix.				*/
{
	SparseMatrix temp;										/* It's our temp vector.				*/
	
	temp = neg;												/* We get copy of matrix.				*/

	for (int i = 0; i < neg.sizeRow; ++i)					/* We make loop in our matrix columns.	*/
	{
		for (int j = 0; j < neg.size[i]; ++j)				/* We make a loop in our matrix row.	*/
		{
			temp.v[i][j].index = neg.v[i][j].index;			/* We assign indexes to temp.			*/
			temp.v[i][j].data = neg.v[i][j].data * -1;		/* We make a negative matrix.			*/
		}
	}

	return temp;										/* We return our negative matrix.			*/
}

SparseMatrix& SparseMatrix::operator=(const SparseMatrix& right)		/* It assigns two matrixes.				*/
{
	if ( this == &right )					/* It checks if its same left and right.	*/
	{
		return *this;						/* Then we return left.						*/
	}
	else									/* If it is not same it checks.				*/
		v.clear();										/* We clear our matrix.							*/
		v.resize(right.sizeRow);						/* We resize our matrix.						*/

		size = right.size;								/* We assign our sizes.							*/
		sizeRow = right.sizeRow;						/* We assign our size of rows.					*/
		indexOfRow = right.indexOfRow;					/* We assign our row indexes.					*/	
		
		for (int i = 0; i < right.sizeRow; ++i)			/* It creates a loop to make same matrix.		*/
		{
			v[i].resize(right.size[i]);					/* We resize our matrix with right's.			*/

			for (int j = 0; j < right.size[i]; ++j)		/* We make a loop for to get datas and indexes.	*/
			{
				v[i][j].data = right.v[i][j].data;		/* It makes same datas.							*/
				v[i][j].index = right.v[i][j].index;	/* It makes same indexes.						*/
			}
		}

	return *this;							/* We return our new matrix.			*/
}

ostream& operator<<(ostream& out, const SparseMatrix& other)			/* It prints.							*/
{
	for (int i = 0; i < other.sizeRow; ++i)								/* We make a loop for all rows.			*/
	{
		out << other.indexOfRow[i] << " ";								/* It prints index of rows.				*/

		for (int j = 0; j < other.size[i]; ++j)							/* It makes a loop to print all datas.	*/
		{
			out << other.v[i][j].index << ":";							/* It prints index and ':' character.	*/
			out.setf(ios::fixed);										/* It fix to print.						*/
			out.setf(ios::showpoint);									/* It shows points.						*/
			out.precision(1);											/* It defines how many point prints.	*/
			out << other.v[i][j].data << " ";							/* It prints datas and spaces.			*/
		}

		out << endl;													/* It prints end of line.				*/
	}

	return out;													/* It returns to print others.			*/
}