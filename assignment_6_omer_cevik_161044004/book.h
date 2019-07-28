#ifndef BOOK_H
#define BOOK_H

#include <vector>		/* We use vectors.		*/

class book : public base		/* Our inherited book class.	*/
{
public:
	book();						/* Default constructor of book class.			*/

	void ApplyCommands();			/* It applies commands.						*/		
	void CreatePartialEntries();	/* It creates parts of datas.				*/
	void ErrorPrinter();			/* It checks and prints errors.				*/
private:
	std::vector<std::string> title;			/* Our book' title vector.			*/
	std::vector<std::string> authors;		/* Our book' authors vector.		*/
	std::vector<std::string> year;			/* Our book' year vector.			*/
	std::vector<std::string> tags;			/* Our book' tags vector.			*/
};

#endif