/*
											CSE 241 Homework Assignment 5

												OMER_CEVIK_161044004

					# 					In that programme, we create links.								 #
					# 			Using linked list structure and creating documents.					  	 # 

																														*/
#include <iostream>
#include <fstream>
using namespace std;
#include "reader.h"
#include "linkedlist.h"

int main()
{
	linkedlist* L = new linkedlist;	/*  Creating object.		*/

	L = L->CreateLinks();			/*  We create links.		*/

	for (int i = 0; i < L->getCommandLineSize(); ++i)	/*  Checking commands.		*/
	{
		if ( L->getCommandLine(i,0) == "delete" )		/*  Command delete: deletes.		*/
		{
			L = L->deleteFunction(L,i,L->getCommandLine(i,1));
		}
		else if ( L->getCommandLine(i,0) == "cd" )		/*  Command cd: changes current.	*/
		{
			L = L->cd(L,i,L->getCommandLine(i,1));
		}
		else if ( L->getCommandLine(i,0) == "copy" )	/*  Command copy: copy target.		*/
		{
			L = L->copy(L,i,L->getCommandLine(i,1),L->getCommandLine(i,2));
		}
		else if ( L->getCommandLine(i,0) == "move" )	/*  Command move: moves the target.	*/
		{
			L = L->move(L,i,L->getCommandLine(i,1),L->getCommandLine(i,2));
		}
	}

	while( L->getPrev() != NULL )	/* Getting root.		*/
	{
		L = L->getPrev();
	}

	linkedlist* T = new linkedlist;
	T = L;

	ofstream outfile;										/* It's for to write.					*/
	outfile.open("output.txt", ios::out );					/* We open our writer file.				*/

	while( L != NULL )		/* Print to text.		*/
	{
		T->printAll(T,L,outfile);
		L = L->getNext();
	}

	outfile.close();

	return 0;
}