/*
											CSE 241 Homework Assignment 3

												OMER_CEVIK_161044004

					# 			  In that programme ve create vectors and matrixes.						 #
					# 					And we calculate some calculations.							  	 # 

																											*/
#include <iostream>			/* We use cout, etc.				*/
#include <fstream>			/* We use files.					*/
#include <string>			/* We use getline, strings.			*/
#include "SparseVector.h"	/* It's our vector library.			*/
#include "SparseMatrix.h"	/* It's our matrix library.			*/

using namespace std;		/* We use it for cout etc.			*/

int main()					/* It's our main function.			*/
{
	ofstream outfile;										/* It's for to write.					*/
	outfile.open("output.txt", ios::out | ios::trunc );		/* We open our writer file.				*/

	SparseVector a1("a1.txt");								/* We create a vector.					*/
	SparseVector a2("a2.txt");								/* We create a vector.					*/

	outfile << "a1" << endl << a1 << endl;					/* We print a vector to file.			*/

	a1 = a1 + a2;											/* We sum and assign to vectors.		*/
	outfile << "a1+a2" << endl << a1 << endl;				/* We print it.							*/

	a1 = -a1;												/* We negative and assign to vectors.	*/
	outfile << "-a1" << endl << a1 << endl;					/* We print it.							*/
	
	outfile << "dot" << endl << dot(a1,a1) 					/* We multiply two vectors.				*/
			<< endl << endl << endl;

	SparseMatrix m1("m1.txt");								/* We create a matrix.					*/
	SparseMatrix m2("m2.txt");								/* We create a matrix.					*/

	m1 = m1 + m2;											/* We sum and assign two matrixes.		*/
	outfile	<< "m1+m2" << endl << m1 << endl << endl;		/* We print it.							*/

	m1 = m1 - m2;											/* We subtract and assign two matrixes.	*/
	outfile	<< "m1-m2" << endl << m1;						/* We print it.							*/

	outfile.close();										/* We close our output file.			*/

	return 0;					/* Ending programme truely.			*/
}