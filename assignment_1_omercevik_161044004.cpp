/*
											CSE 241 Homework Assignment 1 

												OMER_CEVIK_161044004

					# 					We are trying to find the cost of an object.					 #
					# 	And we calculate while asking to user piece of that object.					  	 # 

																											*/
#include <cstdio>		/* We use printf, sscanf, etc.				*/
#include <cstring>		/* We use strcpy, getline, strlen, etc.		*/
#include <cstdlib>		/* We use malloc for dynammic allocation.	*/

double recursiveCalculate(char *line, int LinePartInteger, char LinePartString[100], double *doublePart);	/* It asks user and finds the result.	*/
char* CheckSpaces(char *line);						/* It checks if there is any space.			*/
void ShiftString(char *str, int index);				/* It shifts the used string.				*/
int findIndex(char *str);							/* It finds and returns index of plus.		*/
int CheckValue(char *line, double *doublePart);		/* It checks if we have only double value.	*/

int main(void)		/* It's our main function.	*/
{
	char *line = NULL, PartLine[100], *definedObject = NULL;		/* We declare our line objects.		*/
	int PartInt;													/* It's our integer part of string.	*/
	double PartDouble;												/* It's our cost of piece.			*/
	size_t len = 100;												/* It's our size to read input.		*/

	line = (char*)malloc(sizeof(char)*100);							/* We allocate our line.			*/
	definedObject = (char*)malloc(sizeof(char)*100);				/* We allocate our defined object.	*/

	printf("Define the object:\n");									/* We ask to user to define object.	*/

	getline(&line,&len,stdin);										/* We read input.					*/
	line[strlen(line)-1] = '\0';									/* We delete newline character.		*/

	strcpy(definedObject,line);										/* We copy our defined object.		*/

	printf("What is %s?:\n",definedObject );						/* We ask user what is defined obj.	*/

	printf("Total cost of %s is %.2f\n",definedObject,recursiveCalculate(line,PartInt,PartLine,&PartDouble)); 	/* We print and calculate the result.		*/

	free(definedObject);		/* We free defined object.	*/
	free(line);					/* We free our line.		*/

    return 0;			/* Ending programme truely.			*/
}

double recursiveCalculate(char *line, int LinePartInteger, char LinePartString[100], double *doublePart)	/* It's our main recursive calculator.	*/
{
	size_t len = 100;												/* It's our size to read input.							*/
	char multiple;													/* We read '*' character inside.						*/
	int index = 0;													/* It's our index of plus.								*/
	double temp = 0.0;												/* We save our result in it.							*/

	getline(&line,&len,stdin);										/* We read input.										*/
	line[strlen(line)-1] = '\0';									/* We delete newline character.							*/

	line = CheckSpaces(line);										/* We check and remove spaces.							*/

	if ( CheckValue(line,doublePart) == 1 )							/* Our base case, if we find cost.						*/
	{
		return *doublePart;											/* Then we return cost.									*/
	}	
	else 															/* If we didn't find cost.								*/
	{	
		while( line[0] != '\0' )									/* We start a loop until null.							*/
		{
			index = findIndex(line);								/* We find index of plus.								*/
			char *Saver = (char*)malloc(sizeof(char)*100);			/* We allocate our saver string.						*/

			if ( index == strlen(line) )							/* We check if our index equals to length of string.	*/
			{
				strcpy(Saver,line);									/* We copy line into our saver string.					*/
				line[0] = '\0';										/* We make null into line string.						*/
			}
			else 													/* If our index is not equals to length of string.		*/
			{
				strncpy(Saver,line,index);							/* We copy our line to our Saver as index. 				*/
				ShiftString(line,index+1);							/* We shift our line.									*/
			}

			sscanf(Saver,"%d%c%s",&LinePartInteger,&multiple,LinePartString);	/* We read our parts.						*/
			
			printf("What is %s?:\n",LinePartString);							/* We ask to user what is next object.		*/

			temp += recursiveCalculate(Saver,LinePartInteger,LinePartString,doublePart)*LinePartInteger;	/* We calculate and call recursive function.	*/

			free(Saver);		/* We free our saver.		*/
		}
	}

	return temp;		/* We return our result.		*/
}

char* CheckSpaces(char *line)		/* It checks for spaces and ignore them.	*/
{
	int i = 0, j = 0;					/* They are just for counters.			*/

	for (i = 0; line[i] != '\0'; ++i)	/* We make loop inside of our line.		*/
	{
		if ( line[i] == ' ' )			/* We check if we find a space.			*/
		{
			continue;					/* Then we ignore it.					*/
		}

		line[j] = line[i];				/* We replace space with other letter.	*/
		++j;							/* We count it.							*/
	}

	line[j] = '\0';						/* We put null character to end of line.*/

	return line;						/* We return our unspaces line.			*/
}

int CheckValue(char *line, double *doublePart)	/* It checks for quotient.		*/
{
	int i = 0, find = 0;				/* They are just for counters.			*/

	for (i = 0; line[i] != '\0'; ++i)	/* We make loop inside of our line.		*/
	{
		if ( line[i] == '*' )			/* We check if we have multiplication.	*/
		{
			++find;						/* So we don't have a double value.		*/
			return 0;					/* We return false.						*/
		}
	}

	if ( find == 0 )					/* We check if we have double value.	*/
	{
		sscanf(line,"%lf",doublePart);	/* We scan our double.					*/
		return 1;						/* So we have, then return true.		*/
	}
}

int findIndex(char *str)	/* It returns index of plus.			*/
{
	int i = 0;					/* It's just a counter.				*/

	while( str[i] != '\0' )		/* We make a loop in string.		*/
	{
		if ( str[i] == '+' )	/* We check if we find plus.		*/
		{
			return i;			/* Then we return index of plus.	*/
		}

		++i;					/* We count it.						*/
	}

	return strlen(str);			/* Else we return length of string.	*/
}

void ShiftString(char *str, int index)		/* It shifts used characters.			*/
{
	int i;										/* It's just a counter.				*/

	for (i = 0; i < strlen(str)-index; ++i)		/* We make a loop in string.		*/
	{
		str[i] = str[index+i];					/* We shift string.					*/
	}		

	str[i] = '\0'; 								/* We push null character to end.	*/
}