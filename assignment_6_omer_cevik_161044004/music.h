#ifndef MUSIC_H
#define MUSIC_H

#include <vector>		/* We use vectors.		*/

class music : public base		/* Our inherited music class.	*/
{
public:
	music();						/* Default constructor of music class.		*/

	void ApplyCommands();			/* It applies commands.						*/		
	void CreatePartialEntries();	/* It creates parts of datas.				*/
	void ErrorPrinter();			/* It checks and prints errors.				*/
private:
	std::vector<std::string> title;		/* Our music' title vector.			*/
	std::vector<std::string> artists;	/* Our music' artists vector.		*/
	std::vector<std::string> year;		/* Our music' year vector.			*/
	std::vector<std::string> genre;		/* Our music' genre vector.			*/
};

#endif