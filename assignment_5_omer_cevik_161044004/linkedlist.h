#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <vector>

class linkedlist : public reader	/*  Creating links and doing commands.		*/
{
public:
	linkedlist();
	const string getDirName()const { return dirName; }
	const string getFileName(const int index)const { return fileName[index]; }
	const std::vector<string> getFile()const { return fileName; }
	linkedlist* getNext()const { return this->next; }
	linkedlist* getPrev()const { return this->prev; }

	linkedlist* deleteFunction(linkedlist* root, const int index, const string data);
	linkedlist* cd(linkedlist* root, const int index, const string data);
	linkedlist* copy(linkedlist* root, const int index, const string data1, const string data2);
	linkedlist* move(linkedlist* root, const int index, const string data1, const string data2);

	void printAll(linkedlist* root, linkedlist* link, ofstream& outfile)const;

	linkedlist* CreateLinks();
	~linkedlist();
private:
	linkedlist* next = NULL;
	linkedlist* prev = NULL;
	string dirName;
	std::vector<string> fileName;
};

#endif