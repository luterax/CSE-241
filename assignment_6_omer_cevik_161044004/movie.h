#ifndef MOVIE_H
#define MOVIE_H

#include <vector>		/* We use vectors.		*/

class movie : public base		/* Our inherited movie class.	*/
{
public:
	movie();						/* Default constructor of movie class.		*/

	void ApplyCommands();			/* It applies commands.						*/		
	void CreatePartialEntries();	/* It creates parts of datas.				*/
	void ErrorPrinter();			/* It checks and prints errors.				*/
private:
	std::vector<std::string> title;			/* Our movie' title vector.			*/
	std::vector<std::string> director;		/* Our movie' director vector.		*/
	std::vector<std::string> year;			/* Our movie' year vector.			*/
	std::vector<std::string> genre;			/* Our movie' genre vector.			*/
	std::vector<std::string> starring;		/* Our movie' starring vector.		*/
};

#endif