#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <fstream>
using namespace std;
#include "reader.h"
#include "linkedlist.h"

linkedlist::linkedlist() : reader() {}		/* We read text.		*/

linkedlist::~linkedlist() 					/* We delete all.			*/
{
	while( this->next != NULL )
	{
		delete[] this;
	}
}

linkedlist* linkedlist::CreateLinks()		/* It creates links.			*/
{
	bool flag = true;

	linkedlist* header = new linkedlist;
	linkedlist* temp1 = new linkedlist;
	linkedlist* temp2 = new linkedlist;
	linkedlist* temp3 = new linkedlist;
	temp3->next = new linkedlist;
	
	for (int i = 0; i < getFileLineSize(); ++i)
	{
		if( header->next != NULL )
		{
			temp1 = header;

			while ( header != NULL && flag )
			{
				for (int j = 0; j < getFileNameSize(i)-1; ++j)
				{
					if ( getFileLine(i,j) == header->dirName )
					{
						if ( j != 0 )
						{
							temp3->dirName = getFileLine(i,0);
							temp3->next = temp1;
							temp1 = temp3;
							flag = false;
						}
						header->fileName.push_back(getFileLine(i,getFileNameSize(i)-1));
					}
				}
				header = header->next;
			}
			flag = true;
			header = temp1;
		}
		else
		{
			header->dirName = getFileLine(i,0);
			temp2 = header;
			
			for (int k = 1; k < getFileNameSize(i); ++k)
			{
				if ( getFileNameSize(i)-1 > k )
				{
					header->next = new linkedlist;
					header->next->dirName = getFileLine(i,k);
					header = header->next;
				}
				else
				{
					header->next = NULL;
					header->fileName.push_back(getFileLine(i,k));
					header = temp2;
 				}
			}
		}
	}

	temp1 = NULL;
	temp2 = NULL;
	temp1 = temp2 = header;

	header->prev = new linkedlist;
	header->prev = NULL;

	while( temp1->next != NULL )
	{
		temp1->next->prev = new linkedlist;
		temp1->next->prev = temp1;
		temp1 = temp1->next;
	}

	header = temp2;
	temp2 = NULL;
	temp3 = NULL;

	return header;
}

linkedlist* linkedlist::copy(linkedlist* root, const int index, const string data1, const string data2)	/* We copy an argument in here. 	*/ 
{
	bool flag = true;
	linkedlist* temp1 = new linkedlist;
	linkedlist* temp2 = new linkedlist;

	temp1 = temp2 = root;
	
	string token;

	istringstream iss(data1);

	while( getline(iss,token,'/') );

	while( root != NULL && flag )
	{
		for(int i = 0; i < root->fileName.size(); ++i)
		{
			if ( root->fileName[i] == token )
			{
				string token2;
				istringstream iss1(data2);

				while( getline(iss1,token2,'/') );

				while( temp1 != NULL && flag )
				{
					if ( temp1->getDirName() == token2 )
					{
						temp1->fileName.push_back(token);
						flag = false;
					}
					if ( flag == false )
					{
						break;
					}
					temp1 = temp1->next;
				}
			}
			if ( flag == false )
			{
				break;
			}
		}
		if ( flag == false )
		{
			break;
		}
		root = root->next;
	}

	temp1 = temp2;

	return temp1;
}

linkedlist* linkedlist::move(linkedlist* root, const int index, const string data1, const string data2)	/* It copies then deletes argument.	*/
{
	bool flag = true;
	linkedlist* temp1 = new linkedlist;
	linkedlist* temp2 = new linkedlist;

	temp1 = temp2 = root;
	
	string token;

	istringstream iss(data1);

	while( getline(iss,token,'/') );

	while( root != NULL && flag )
	{
		for(int i = 0; i < root->fileName.size(); ++i)
		{
			if ( root->fileName[i] == token )
			{
				string token2;
				istringstream iss1(data2);

				while( getline(iss1,token2,'/') );

				while( temp1 != NULL && flag )
				{
					if ( temp1->getDirName() == token2 )
					{
						temp1->fileName.push_back(token);
						flag = false;
					}
					if ( flag == false )
					{
						break;
					}
					temp1 = temp1->next;
				}
				root->fileName.erase(root->fileName.begin()+i);
			}
			if ( flag == false )
			{
				break;
			}
		}
		if ( flag == false )
		{
			break;
		}
		root = root->next;
	}

	temp1 = temp2;

	return temp1;
}

linkedlist* linkedlist::deleteFunction(linkedlist* root, const int index, const string data)	/* It deletes argument.			*/
{
	bool flag = true;
	linkedlist* temp = new linkedlist;

	temp = root;

	string token;

	std::istringstream iss(data);

	while( getline(iss,token,'/') );

	while( root != NULL && flag )
	{
		if ( root->getDirName() == data && root->prev != NULL)
		{
			root = root->prev;
			root->next = NULL;
			root = temp;
			flag = false;
		}
		else
		{
			for (int i = 0; i < root->fileName.size() && flag; ++i)
			{
				if ( root->fileName[i] == data )
				{
					root->fileName.erase(root->fileName.begin()+i);
					flag = false;
					root = temp;
				}
			}
			if ( flag == false )
			{
				break;
			}
		}
		root = root->next;
	}

	return temp;
}

linkedlist* linkedlist::cd(linkedlist* root, const int index, const string data)	/* It changes current.			*/
{
	linkedlist* temp = new linkedlist;

	if ( data == ".." )
	{
		if ( root->prev == NULL )
		{
			return root;
		}
		else
		{
			return root->prev;
		}
	}
	else
	{
		string token;

		std::istringstream iss(data);

		while( getline(iss,token,'/') );

		while( root != NULL )
		{
			if ( root->dirName == token )
			{
				return root;
			}
			else
			{
				root = root->next;
			}
		}
		
		return root;
	}
}

void linkedlist::printAll(linkedlist* root, linkedlist* link, ofstream& outfile)const
{
	string str;

	if ( outfile.is_open() )
	{
		while( root != link->next )
		{
			str+=root->dirName;
			str+="/";
			root = root->next;
		}

		outfile << str << endl;

		for (int i = 0; i < link->fileName.size(); ++i)
		{
			outfile << str <<link->fileName[i] << endl;
		}
	}
}