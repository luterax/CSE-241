/*
											CSE 241 Homework Assignment 6

												OMER_CEVIK_161044004

					# 					In that programme, we create different objects.					 #
					# 				  And we make sort, search and exception operations.			  	 # 

																														*/
#include <iostream>			/*                    				*/
#include "base.h"			/*     		 				        */
#include "book.h"			/*            Our Libraries.		*/
#include "music.h"			/*                    				*/
#include "movie.h"			/*                    				*/

using namespace std;		/* 		We use cerr. 				*/

int main()					/*      Our main function.			*/
{
	try{
		
		base BaseObject;								/* We create it to check dataType. 	*/

		if ( BaseObject.getDataType() == "book" )		/* We check if it's a book.			*/
		{
			book BookObject;							/* Then we create book object.		*/
		}
		else if ( BaseObject.getDataType() == "music" )	/* We check if it's a music.		*/
		{
			music MusicObject;							/* Then we create music object.		*/
		}
		else if ( BaseObject.getDataType() == "movie" )	/* We check if it's a movie.		*/
		{
			movie MovieObject;							/* Then we create a movie object.	*/
		}
		else											/* If our object is undefined.		*/
		{
			throw 1.5;									/* We throw a double. 				*/	
		}
	}
	catch(const char* ErrorMessage){					/* Catch prints if files can not open.	*/
		cerr << ErrorMessage << endl;
	}
	catch(double){
		cerr << "Unacceptable data type." << endl;		/* Undefined object error prints.	*/
	}

	return 0;				/* Ending programme truely.			*/
}