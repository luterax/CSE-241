/*
											CSE 241 Homework Assignment 2 

												OMER_CEVIK_161044004

						# 					In that programme we create 				 #
						# 			a game named Tsuro. There are two players.		 	 #
						#		And they try to keep inside the board. Have fun!		 #

																											*/
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Tsuro
{
public:
	Tsuro() : size(3) {}					/* Creates size.		*/
	Tsuro(int newsize) : size(newsize) {}	/* Creates size.		*/

	void CreateBoard();						/* Creates board.			*/
	void RandomValueCreater();				/* Create random values.	*/
	void Player1Functions();				/* Calls player 1 functions.	*/
	void Player2Functions();				/* Calls player 2 functions.	*/
	void CreatePlayersTokens();				/* Creates players tokens.		*/
	void MakeItSameBoard(Tsuro& other) const;	/* Makes a same board.		*/
	void BoardPrinter() const;						/* It prints the board.		*/

	
private:
	void firstCard(int Card[6][4]) const;			/* Creates a random card.	*/
	void secondCard(int Card[6][4]) const;			/* Creates a random card.	*/
	void thirdCard(int Card[6][4]) const;			/* Creates a random card.	*/
	void fourthCard(int Card[6][4]) const;			/* Creates a random card.	*/
	void fifthCard(int Card[6][4]) const;			/* Creates a random card.	*/
	void sixthCard(int Card[6][4]) const;			/* Creates a random card.	*/
	void seventhCard(int Card[6][4]) const;			/* Creates a random card.	*/
	void eighthCard(int Card[6][4]) const;			/* Creates a random card.	*/
	void ninethCard(int Card[6][4]) const;			/* Creates a random card.	*/
	void tenthCard(int Card[6][4]) const;			/* Creates a random card.	*/
	void CardInitialize(int Card[6][4]) const;		/* Initialize card. 		*/
	void CardPrinter(const int Card[6][4]) const;	/* It prints the card.		*/
	void printTo(const int Card[6][4], int k, int n);/* It prints card into the board.	*/
	void TurnLeftTheCard(int Card[6][4]);			/* It turns the card to left.		*/
	void TurnRightTheCard(int Card[6][4]);			/* It turns the card to right.		*/
	void TurnCardOrNot(int Card[6][4]);				/* It ask to turn or not to user.	*/
	void CardCreater(int Card[6][4]);				/* It creates random cards.			*/
	void PrintCardToBoard(int Card[6][4]);			/* It prints card to board.			*/
	void MoveTokensPlayer(char token, char otherToken);	/* It moves the tokens.			*/

	char tokenX = 'X';
	char tokenY = 'Y';
	int RandomValues[8];
	int ReverseValues[8];
	int size;
	char Board[20][40];
	int Card1[6][4];
	int Card2[6][4];
	int Card3[6][4];
	int Tokens[24];
};

int main(void)
{
	Tsuro Player1(3), Player2(3);
	int CardCounter = 9, flag = 1;

	srand(time(NULL));

	Player1.CreateBoard();
	Player1.CreatePlayersTokens();

	Player1.MakeItSameBoard(Player2);

	Player1.BoardPrinter();

	cin.clear();
	fflush(stdin);

	cout << endl << endl;

	while( CardCounter > 0 )
	{
		Player1.RandomValueCreater();
		Player2.RandomValueCreater();
		
		Player1.Player1Functions();

		Player1.MakeItSameBoard(Player2);

		--CardCounter;

		if ( CardCounter <= 0 )
		{
			cout << endl << "It's a tie! No one wins..." << endl;
			break;
		}

		Player2.Player2Functions();

		--CardCounter;

		Player2.MakeItSameBoard(Player1);

		if ( CardCounter <= 0 )
		{
			cout << endl << "It's a tie! No one wins..." << endl;
			break;
		}

		cin.clear();
		fflush(stdin);
	}

	return 0;
}

void Tsuro::MoveTokensPlayer(char token, char otherToken)
{
	char temp;

	for (int i = 0; i < size*6+2; ++i)
	{
		for (int j = 0; j < size*12+4; ++j)
		{
			if ( Board[i][j] == token )
			{
				if ( (j == 0) && (Board[i][j+2] != ' ') && (i%2 == 1) )
				{
					if ( Board[i][j+6] == Board[i+1][j+2] )
					{
						if ( Board[i+1][j] == otherToken)
						{
							cout << endl << "It's a tie! No one wins." << endl;
							exit(1);
						}

						Board[i+1][j] = token;
						Board[i][j] = 'o';
						BoardPrinter();
						if ( token == tokenY )
						{
							cout << endl << "Player 1 Win !" << endl;
						}
						else
						{
							cout << endl << "Player 2 Win !" << endl;
						}
						exit(1);
					}
					else if ( Board[i][j+6] == Board[i-2][j+6] )
					{
						if ( Board[i-3][j+6] == otherToken )
						{
							cout << endl << "It's a tie! No one wins." << endl;
							exit(1);
						}

						Board[i-3][j+6] = token;
						Board[i][j] = 'o';
						BoardPrinter();
						if ( token == tokenY )
						{
							cout << endl << "Player 1 Win !" << endl;
						}
						else
						{
							cout << endl << "Player 2 Win !" << endl;
						}
						exit(1);
					}
					else if ( Board[i][j+6] == Board[i-2][j+9] )
					{
						if ( Board[i-3][j+9] == otherToken )
						{
							cout << endl << "It's a tie! No one wins." << endl;
							exit(1);
						}

						Board[i-3][j+9] = token;
						Board[i][j] = 'o';
						BoardPrinter();
						if ( token == tokenY )
						{
							cout << endl << "Player 1 Win !" << endl;
						}
						else
						{
							cout << endl << "Player 2 Win !" << endl;
						}
						exit(1);
					}
					else if ( Board[i][j+6] == Board[i+3][j+6] )
					{
						temp = Board[i+3][j+6];
						Board[i+3][j+6] = token;
						Board[i][j] = 'o';
					}
					else if ( Board[i][j+6] == Board[i+3][j+9] )
					{
						temp = Board[i+3][j+9];
						Board[i+3][j+9] = token;
						Board[i][j] = 'o';
					}
					else if ( Board[i][j+6] == Board[i][j+13] )
					{
						temp = Board[i][j+13];
						Board[i][j+13] = token;
						Board[i][j] = 'o';
					}
					else if ( Board[i][j+6] == Board[i+1][j+13] )
					{
						temp = Board[i+1][j+13];
						Board[i+1][j+13] = token;
						Board[i][j] = 'o';
					}
				}
				else if ( (j == 0) && (Board[i][j+2] != ' ') && (i%2 == 0) )
				{
					if ( Board[i][j+6] == Board[i-1][j+2] )
					{
						if ( Board[i-1][j] == otherToken)
						{
							cout << endl << "It's a tie! No one wins." << endl;
							exit(1);
						}

						Board[i-1][j] = token;
						Board[i][j] = 'o';
						BoardPrinter();
						if ( token == tokenY )
						{
							cout << endl << "Player 1 Win !" << endl;
						}
						else
						{
							cout << endl << "Player 2 Win !" << endl;
						}
						exit(1);
					}
					else if ( Board[i][j+6] == Board[i-3][j+6] )
					{
						if ( Board[i-4][j+6] == otherToken )
						{
							cout << endl << "It's a tie! No one wins." << endl;
							exit(1);
						}

						Board[i-4][j+6] = token;
						Board[i][j] = 'o';
						BoardPrinter();
						if ( token == tokenY )
						{
							cout << endl << "Player 1 Win !" << endl;
						}
						else
						{
							cout << endl << "Player 2 Win !" << endl;
						}
						exit(1);
					}
					else if ( Board[i][j+6] == Board[i-3][j+9] )
					{
						if ( Board[i-4][j+9] == otherToken )
						{
							cout << endl << "It's a tie! No one wins." << endl;
							exit(1);
						}

						Board[i-4][j+9] = token;
						Board[i][j] = 'o';
						BoardPrinter();
						if ( token == tokenY )
						{
							cout << endl << "Player 1 Win !" << endl;
						}
						else
						{
							cout << endl << "Player 2 Win !" << endl;
						}
						exit(1);
					}
					else if ( Board[i][j+6] == Board[i+2][j+6] )
					{
						temp = Board[i+2][j+6];
						Board[i+2][j+6] = token;
						Board[i][j] = 'o';
					}
					else if ( Board[i][j+6] == Board[i+2][j+9] )
					{
						temp = Board[i+2][j+9];
						Board[i+2][j+9] = token;
						Board[i][j] = 'o';
					}
					else if ( Board[i][j+6] == Board[i][j+13] )
					{
						temp = Board[i][j+13];
						Board[i][j+13] = token;
						Board[i][j] = 'o';
					}
					else if ( Board[i][j+6] == Board[i-1][j+13] )
					{
						temp = Board[i-1][j+13];
						Board[i-1][j+13] = token;
						Board[i][j] = 'o';
					}
				}



				else if ( (j == size*12+3) && (Board[i][j-2] != ' ') && (i%2 == 1) )
				{
					if ( Board[i][j-6] == Board[i+1][j-2] )
					{
						if ( Board[i+1][j] == otherToken )
						{
							cout << endl << "It's a tie! No one wins." << endl;
							exit(1);
						}

						Board[i+1][j] = token;
						Board[i][j] = 'o';
						BoardPrinter();
						if ( token == tokenY )
						{
							cout << endl << "Player 1 Win !" << endl;
						}
						else
						{
							cout << endl << "Player 2 Win !" << endl;
						}
						exit(1);
					}
					else if ( Board[i][j-6] == Board[i-2][j-6] )
					{
						if ( Board[i-3][j-6] == otherToken )
						{
							cout << endl << "It's a tie! No one wins." << endl;
							exit(1);
						}

						Board[i-3][j-6] = token;
						Board[i][j] = 'o';
						BoardPrinter();
						if ( token == tokenY )
						{
							cout << endl << "Player 1 Win !" << endl;
						}
						else
						{
							cout << endl << "Player 2 Win !" << endl;
						}
						exit(1);
					}
					else if ( Board[i][j-6] == Board[i-2][j-9] )
					{
						if ( Board[i-3][j-9] == otherToken )
						{
							cout << endl << "It's a tie! No one wins." << endl;
							exit(1);
						}

						Board[i-3][j-9] = token;
						Board[i][j] = 'o';
						BoardPrinter();
						if ( token == tokenY )
						{
							cout << endl << "Player 1 Win !" << endl;
						}
						else
						{
							cout << endl << "Player 2 Win !" << endl;
						}
						exit(1);
					}
					else if ( Board[i][j-6] == Board[i+3][j-6] )
					{
						temp = Board[i+3][j-6];
						Board[i+3][j-6] = token;
						Board[i][j] = 'o';
					}
					else if ( Board[i][j-6] == Board[i+3][j-9] )
					{
						temp = Board[i+3][j-9];
						Board[i+3][j-9] = token;
						Board[i][j] = 'o';
					}
					else if ( Board[i][j-6] == Board[i][j-13] )
					{
						temp = Board[i][j-13];
						Board[i][j-13] = token;
						Board[i][j] = 'o';
					}
					else if ( Board[i][j-6] == Board[i+1][j-13] )
					{
						temp = Board[i+1][j-13];
						Board[i+1][j-13] = token;
						Board[i][j] = 'o';
					}
				}
				else if ( (j == 0) && (Board[i][j-2] != ' ') && (i%2 == 0) )
				{
					if ( Board[i][j-6] == Board[i-1][j-2] )
					{
						if ( Board[i-1][j] == otherToken)
						{
							cout << endl << "It's a tie! No one wins." << endl;
							exit(1);
						}

						Board[i-1][j] = token;
						Board[i][j] = 'o';
						BoardPrinter();
						if ( token == tokenY )
						{
							cout << endl << "Player 1 Win !" << endl;
						}
						else
						{
							cout << endl << "Player 2 Win !" << endl;
						}
						exit(1);
					}
					else if ( Board[i][j-6] == Board[i-3][j-6] )
					{
						if ( Board[i-4][j-6] == otherToken )
						{
							cout << endl << "It's a tie! No one wins." << endl;
							exit(1);
						}

						Board[i-4][j-6] = token;
						Board[i][j] = 'o';
						BoardPrinter();
						if ( token == tokenY )
						{
							cout << endl << "Player 1 Win !" << endl;
						}
						else
						{
							cout << endl << "Player 2 Win !" << endl;
						}
						exit(1);
					}
					else if ( Board[i][j-6] == Board[i-3][j-9] )
					{
						if ( Board[i-4][j-9] == otherToken )
						{
							cout << endl << "It's a tie! No one wins." << endl;
							exit(1);
						}

						Board[i-4][j-9] = token;
						Board[i][j] = 'o';
						BoardPrinter();
						if ( token == tokenY )
						{
							cout << endl << "Player 1 Win !" << endl;
						}
						else
						{
							cout << endl << "Player 2 Win !" << endl;
						}
						exit(1);
					}
					else if ( Board[i][j-6] == Board[i+2][j-6] )
					{
						temp = Board[i+2][j-6];
						Board[i+2][j-6] = token;
						Board[i][j] = 'o';
					}
					else if ( Board[i][j-6] == Board[i+2][j-9] )
					{
						temp = Board[i+2][j+9];
						Board[i+2][j+9] = token;
						Board[i][j] = 'o';
					}
					else if ( Board[i][j-6] == Board[i][j-13] )
					{
						temp = Board[i][j-13];
						Board[i][j-13] = token;
						Board[i][j] = 'o';
					}
					else if ( Board[i][j-6] == Board[i-1][j-13] )
					{
						temp = Board[i-1][j-13];
						Board[i-1][j-13] = token;
						Board[i][j] = 'o';
					}
				}
			}
		}
	}
}

void Tsuro::Player1Functions()
{
	char CardReader, BoardReader;

	CardInitialize(Card1);
	CardCreater(Card1);
	cout << "A)" << endl;
	CardPrinter(Card1);

	CardInitialize(Card2);
	CardCreater(Card2);
	cout << endl << "B)" << endl;
	TurnLeftTheCard(Card2);
	CardPrinter(Card2);

	CardInitialize(Card3);
	CardCreater(Card3);
	cout << endl << "C)" << endl;
	TurnRightTheCard(Card3);
	CardPrinter(Card3);

	cout << endl << endl << "Player 1 : " << endl;
	cout << "Choose your card:   'A'   'B'   'C' ? " << endl;
	cin >> CardReader;
	cout << endl;

	Acceptable1:
		{
			switch(CardReader)
			{
				case 'A': 
				case 'a':	CardPrinter(Card1); TurnCardOrNot(Card1); MoveTokensPlayer(tokenX, tokenY); MoveTokensPlayer(tokenY, tokenX); BoardPrinter();
				break;

				case 'B':	
				case 'b':	CardPrinter(Card2); TurnCardOrNot(Card2); MoveTokensPlayer(tokenX, tokenY); MoveTokensPlayer(tokenY, tokenX); BoardPrinter();
				break;

				case 'C':
				case 'c':	CardPrinter(Card3); TurnCardOrNot(Card3); MoveTokensPlayer(tokenX, tokenY); MoveTokensPlayer(tokenY, tokenX); BoardPrinter();
				break;

				default: cout << "Unacceptable card! Don't you want to play? Enter an acceptable card:" << endl;
						 cin >> CardReader; goto Acceptable1;
			}
		}
}

void Tsuro::Player2Functions()
{
	char CardReader, BoardReader;

	CardInitialize(Card1);
	CardInitialize(Card1);
	CardCreater(Card1);
	cout << "A)" << endl;
	CardPrinter(Card1);

	CardInitialize(Card2);
	CardCreater(Card2);
	cout << endl << "B)" << endl;
	TurnLeftTheCard(Card2);
	CardPrinter(Card2);

	CardInitialize(Card3);
	CardCreater(Card3);
	cout << endl << "C)" << endl;
	TurnRightTheCard(Card3);
	CardPrinter(Card3);

	cout << endl << endl << "Player 2 : " << endl;
	cout << "Choose your card:   'A'   'B'   'C' ? " << endl;
	cin >> CardReader;
	cout << endl;

	Acceptable2:
		{
			switch(CardReader)
			{
				case 'A': 
				case 'a':	CardPrinter(Card1); TurnCardOrNot(Card1); MoveTokensPlayer(tokenY, tokenX); MoveTokensPlayer(tokenX, tokenY); BoardPrinter();
				break;

				case 'B':	
				case 'b':	CardPrinter(Card2); TurnCardOrNot(Card2); MoveTokensPlayer(tokenY, tokenX); MoveTokensPlayer(tokenX, tokenY); BoardPrinter();
				break;

				case 'C':
				case 'c':	CardPrinter(Card3); TurnCardOrNot(Card3); MoveTokensPlayer(tokenY, tokenX); MoveTokensPlayer(tokenX, tokenY); BoardPrinter();
				break;

				default: cout << "Unacceptable card! Don't you want to play? Enter an acceptable card:" << endl;
						 cin >> CardReader; goto Acceptable2;
			}
		}
}

void Tsuro::CreatePlayersTokens()
{
	int x = 0, tok1 = 0, tok2 = 0;

	for (int i = 0; i < 24; ++i)
	{
		Tokens[i] = 0;
	}

	for (int i = 0; i < 6*size+2; ++i)
	{
		for (int j = 0; j < 12*size+4; ++j)
		{
			if ( Board[i][j] == 'o' )
			{
				Tokens[x] = i;
				Tokens[x+1] = j;
				x += 2;
			}
		}
	}

	tok1 = rand()%24;
	tok2 = rand()%24;

	if ( (tok1 == tok2) && (tok2 > 12) )
	{
		tok2 -= 2; 
	}
	else if ( (tok1 == tok2) && (tok2 <= 12) )
	{
		tok2 += 2;
	}

	if ( tok1%2 == 0 )
	{
		Board[Tokens[tok1]][Tokens[tok1+1]] = tokenX;
	}
	else
	{
		if ( tok1 == 23 )
		{
			Board[Tokens[tok1-1]][Tokens[tok1]] = tokenX;
		}
		else
			Board[Tokens[tok1+1]][Tokens[tok1+2]] = tokenX;
	}

	if ( tok2%2 == 0 )
	{
		Board[Tokens[tok2]][Tokens[tok2+1]] = tokenY;
	}
	else
	{
		if ( tok2 == 23 )
		{
			Board[Tokens[tok2-3]][Tokens[tok2-2]] = tokenY;
		}
		else
			Board[Tokens[tok2+1]][Tokens[tok2+2]] = tokenY;
	}
}

void Tsuro::MakeItSameBoard(Tsuro& other) const 			/* It makes same boards.		*/
{
	other.size = size;							/* We make same sizes.						*/

	for (int i = 0; i < size*6+2; ++i)			/* We make a loop for coloumns.				*/
	{
		for (int j = 0; j < size*12+4; ++j)		/* We make a loop for rows.					*/
		{
			other.Board[i][j] = Board[i][j];	/* We assign two boards.					*/
		}
	}

	//BoardPrinter();								/* We print our board.						*/
}

void Tsuro::printTo(const int Card[6][4], int k, int n)		/* It prints cards to board.			*/
{
	int l = 1;												/* It's our counter.					*/

	for (int i = 0; i < 6; ++i, ++n)						/* We make a loop for cards coloumns.	*/
	{
		for (int j = 0; j < 4; ++j)							/* We make a loop for cards rows.		*/
		{
			if ( Card[i][j] != 0 )							/* We check if card member is not zero.	*/
			{
				if ( i == 0 || i == 5 )						/* We check indexes.					*/
				{
					for (l = 1; l <= 4; ++l)				/* We make a loop for dots.				*/
					{
						Board[n+1][k+l] = '.';				/* We push dots.						*/
					}

					Board[n+1][k+l] = static_cast<char>(Card[i][j]) + '0';		/* We push card member into board.	*/
					Board[n+1][k+l+1] = '.';									/* We push dots.					*/
					Board[n+1][k+l+2] = '.';									/* We push dots.					*/
					Board[n+1][k+l+3] = static_cast<char>(Card[i][j+1]) + '0';	/* We push card member into board.	*/
					l += 3;									/* We count.							*/
					++j;									/* We count.							*/

					for (int m = 1; m <= 4; ++m)			/* We make a loop for dots.				*/
					{
						Board[n+1][k+l+m] = '.';			/* We push dots.						*/
					}
				}
				else if ( i == 1 || i == 4 )				/* We check indexes.					*/
				{
					for (l = 1; l <= 4; ++l)				/* We make a loop for space and colons.	*/
					{
						if ( l == 1 )						/* We check indexes.					*/	
						{
							Board[n+1][k+l] = ':';			/* We push colon.						*/
						}
						else 								/* We check indexes.					*/
							Board[n+1][k+l] = ' ';			/* We push spaces.						*/
					}

					Board[n+1][k+l] = static_cast<char>(Card[i][j]) + '0';	/* We push card member into board.	*/
					Board[n+1][k+l+1] = ' ';				/* We push spaces.						*/
					Board[n+1][k+l+2] = ' ';				/* We push spaces.						*/
					Board[n+1][k+l+3] = static_cast<char>(Card[i][j+1]) + '0';	/* We push card member into board.	*/
					l += 3;									/* We count.							*/
					++j;									/* We count.							*/

					for (int m = 1; m <= 4; ++m)			/* We make a loop for space and colons.	*/
					{
						if ( m == 4 )						/* We check indexes.					*/
						{
							Board[n+1][k+l+m] = ':';		/* We push colon.						*/
						}
						else 								/* We check indexes.					*/
							Board[n+1][k+l+m] = ' ';		/* We push spaces.						*/
					}
				}
				else if ( i == 2 || i == 3 )				/* We check indexes.					*/
				{	
					for (l = 1; l <= 4; ++l)				/* We make a loop for space and members.*/
					{
						if ( l == 1 )						/* We check indexes.					*/
						{
							Board[n+1][k+l] = static_cast<char>(Card[i][j-2]) + '0';	/* We push card member into board.	*/
						}
						else 								/* We check indexes.					*/
							Board[n+1][k+l] = ' ';			/* We push spaces.						*/
					}

					Board[n+1][k+l] = static_cast<char>(Card[i][j-1]) + '0';	/* We push card member into board.	*/
					Board[n+1][k+l+1] = ' ';				/* We push spaces.						*/
					Board[n+1][k+l+2] = ' ';				/* We push spaces.						*/
					Board[n+1][k+l+3] = static_cast<char>(Card[i][j]) + '0';	/* We push card member into board.	*/
					l += 3;									/* We count.							*/
					++j;									/* We count.							*/

					for (int m = 1; m <= 4; ++m)			/* We make a loop for card member.		*/
					{
						if ( m == 4 )						/* We check indexes.					*/
						{
							Board[n+1][k+l+m] = static_cast<char>(Card[i][j]) + '0';	/* We push card member into board.	*/
						}
						else 								/* We check indexes.					*/
							Board[n+1][k+l+m] = ' ';		/* We push spaces.						*/
					}
				}
			}
		}
	}
}

void Tsuro::TurnCardOrNot(int Card[6][4])			/* It makes a choose for to turn card or not.		*/
{
	char turn;				/* User enters the decision.			*/

	cout << endl << "Enter if you want to turn your card 'right' or 'left' or 'not': 'R' 'L' 'N' " << endl;		/* Asking to user.		*/

	cin >> turn;			/* User enters.							*/

	while(1)				/* We make a loop.						*/
	{
		if ( turn == 'R' || turn == 'r' )		/* We check if user wants to turn right.		*/
		{
			TurnRightTheCard(Card);				/* We turn right the card.						*/
			cout << endl << endl;				/* We print new lines.							*/
			CardPrinter(Card);					/* We print the card.							*/
		}
		else if ( turn == 'L' || turn == 'l' )	/* We check if user wants to turn left.			*/
		{
			TurnLeftTheCard(Card);				/* We turn left the card.						*/
			cout << endl << endl;				/* We print new lines.							*/
			CardPrinter(Card);					/* We print the card.							*/
		}
		else if ( turn == 'N' || turn == 'n' )	/* We check if user doesn't want to turn.		*/
		{
			PrintCardToBoard(Card);				/* Then we print card to board.					*/
			break;								/* We end the loop.								*/
		}
		else 									/* If user entered different values we check.	*/
		{
			cout << endl << "Unacceptable turn! Try again." << endl;	/* We inform user.		*/						
		}

		cout << endl << "Enter if you want to turn your card 'right' or 'left' or 'not': 'R' 'L' 'N' " << endl;	/* We ask user to enter a turn move.	*/
		cin >> turn;		/* User enters.			*/
	}
}

void Tsuro::CreateBoard()								/* It creates the board.		*/
{
	int temp1 = 0, temp2 = 1, i = 0, j = 0,				/* They are just counters and temps.		*/
	 m = 0, n = 0, k = 0, flag = 1, count = 1;			/* They are just counters and flags.		*/

	for (i = 0; i < size*6+2; ++i)						/* We make a loop for coloumns.				*/
	{
		if ( i == 0 || i == (6*size+1) )				/* We check our indexes.					*/
		{
			Board[i][0] = '-';							/* We print our first minuses.				*/
			Board[i][1] = '-';							/* We print our first minuses.				*/

			for (j = 0; j < size; ++j)					/* We make a loop for size times.			*/
			{
				for (k = 0; k < 12; ++k)				/* We make a loop for to print 'o' and '-'.	*/
				{
					if ( j == 0 && flag )				/* We check our print.						*/
					{
						temp1 += 2;						/* We count.								*/
						flag = 0;						/* We make flag zero.						*/
					}
					if ( k == 4 || k == 7 )				/* We check indexes.						*/
					{
						Board[i][temp1] = 'o';			/* We push 'o'.								*/
					}
					else								/* Else we check.							*/
					{
						Board[i][temp1] = '-';			/* We push '-'.								*/
					}
					++temp1;							/* We count.								*/
				}
			}

			Board[i][12*size+2] = '-';					/* We push our last minuses.				*/
			Board[i][12*size+3] = '-';					/* We push our last minuses.				*/

			temp1 = 0;									/* We re-initialize our temp.				*/
			flag = 1;									/* We make our flag one.					*/
		}
		else 											/* Else we check.							*/
		{
			for (j = 0; j < size; ++j)					/* We make a loop for size times.			*/
			{
				for (k = 0; k < 6; ++k)					/* We make a loop for to print 'o' and '-'.	*/
				{
					if ( k == 2 || k == 3 )				/* We check our indexes.					*/
					{
						Board[temp2][0] = 'o';			/* We push 'o'.								*/

						for (m = 1; m < 12*size+3; ++m)	/* We make a loop for card numbers.			*/
						{
							if ( m%10 == 0 && k == 2 )	/* We check for card numbers counters.		*/
							{
								Board[temp2][m] = static_cast<char>(count) + 48;	/* We push card numbers.	*/
								++count;				/* We count.								*/
							}
							else
								Board[temp2][m] = ' ';	/* We push space.							*/
						}

						Board[temp2][m] = 'o';			/* We push 'o'.								*/
					}
					else 								/* We check our indexes.					*/
					{
						Board[temp2][0] = '|';			/* We push '|'.								*/

						for (n = 1; n < 12*size+3; ++n)	/* We make a loop for spaces.				*/
						{
							Board[temp2][n] = ' ';		/* We push space.							*/
						}

						Board[temp2][n] = '|';			/* We push '|'.								*/
					}
					++temp2;							/* We count.								*/
				}
			}

			i = temp2-1;								/* We count.								*/		
		}
	}
}

void Tsuro::BoardPrinter() const					/* It prints the board.				*/
{
	for (int i = 0; i < size*6+2; ++i)			/* We make a loop for coloumns.		*/
	{
		for (int j = 0; j < size*12+4; ++j)		/* We make a loop for rows.			*/
		{
			cout << Board[i][j];				/* We print members of board.		*/
		}
		cout << endl;							/* We print a new line for a row.	*/
	}
}

void Tsuro::PrintCardToBoard(int Card[6][4])		/* It prints the choosen card into the board.		*/
{
	char BoardReader;					/* It gets input from user.			*/

	cout << endl << "Choose place for your card: 1 2 3 4 5 6 7 8 9" << endl;	/* We ask to user to make a choose. 		*/
	cin >> BoardReader; 														/* User enters a value.						*/
	cout << endl;																/* We push a new line.						*/

	switch(BoardReader)									/* We make a switch statement to print correct place.		*/
	{
		case '1': printTo(Card,1,0);					/* If user entered to 1 then we print to place of 1.		*/
		break;											/* And we break.											*/

		case '2': printTo(Card,1+12,0);					/* If user entered to 2 then we print to place of 2.		*/
		break;											/* And we break.											*/

		case '3': printTo(Card,1+12+12,0);				/* If user entered to 3 then we print to place of 3.		*/
		break;											/* And we break.											*/

		case '4': printTo(Card,1,0+6);					/* If user entered to 4 then we print to place of 4.		*/
		break;											/* And we break.											*/

		case '5': printTo(Card,1+12,0+6);				/* If user entered to 5 then we print to place of 5.		*/
		break;											/* And we break.											*/

		case '6': printTo(Card,1+12+12,0+6);			/* If user entered to 6 then we print to place of 6.		*/
		break;											/* And we break.											*/

		case '7': printTo(Card,1,0+6+6);				/* If user entered to 7 then we print to place of 7.		*/
		break;											/* And we break.											*/

		case '8': printTo(Card,1+12,0+6+6);				/* If user entered to 8 then we print to place of 8.		*/
		break;											/* And we break.											*/

		case '9': printTo(Card,1+12+12,0+6+6);			/* If user entered to 9 then we print to place of 9.		*/
		break;											/* And we break.											*/

		default: cout << "Unacceptable place you entered." << endl;		/* If user enters unacceptable place then we inform user and finish the statement.	*/
	}
}

void Tsuro::TurnLeftTheCard(int Card[6][4])			/* It turns left the card.					*/
{
	int tempCard[4];						/* It's just for to save card's first members.		*/

	tempCard[0] = Card[0][1];				/* We save first member of card.					*/
	tempCard[1] = Card[0][2];				/* We save second member of card.					*/
	Card[0][1] = Card[2][3];				/* We assign the left first member to left.			*/
	Card[0][2] = Card[3][3];				/* We assign the left second member to left.		*/
	Card[2][3] = Card[5][2];				/* We assign the left first member to left.			*/
	Card[3][3] = Card[5][1];				/* We assign the left second member to left.		*/
	Card[5][2] = Card[3][0];				/* We assign the left first member to left.			*/
	Card[5][1] = Card[2][0];				/* We assign the left second member to left.		*/
	Card[3][0] = tempCard[0];				/* We assign the saved first member to left.		*/
	Card[2][0] = tempCard[1];				/* We assign the saved second member to left.		*/

	tempCard[2] = Card[1][1];				/* We save third member of card.					*/
	tempCard[3] = Card[1][2];				/* We save fourth member of card.					*/
	Card[1][1] = Card[2][2];				/* We assign the left third member to left.			*/
	Card[1][2] = Card[3][2];				/* We assign the left fourth member to left.		*/
	Card[2][2] = Card[4][2];				/* We assign the left third member to left.			*/
	Card[3][2] = Card[4][1];				/* We assign the left fourth member to left.		*/
	Card[4][2] = Card[3][1];				/* We assign the left third member to left.			*/
	Card[4][1] = Card[2][1];				/* We assign the left fourth member to left.		*/
	Card[3][1] = tempCard[2];				/* We assign the saved third member to left.		*/
	Card[2][1] = tempCard[3];				/* We assign the saved fourth member to left.		*/
}

void Tsuro::TurnRightTheCard(int Card[6][4])		/* It turns right the card.					*/
{
	int tempCard[4];						/* It's just for to save card's first members.		*/

	tempCard[0] = Card[0][1];				/* We save first member of card.					*/
	tempCard[1] = Card[0][2];				/* We save second member of card.					*/
	Card[0][1] = Card[3][0];				/* We assign the left first member to right.		*/
	Card[0][2] = Card[2][0];				/* We assign the left second member to right.		*/
	Card[3][0] = Card[5][2];				/* We assign the left first member to right.		*/
	Card[2][0] = Card[5][1];				/* We assign the left second member to right.		*/
	Card[5][2] = Card[2][3];				/* We assign the left first member to right.		*/
	Card[5][1] = Card[3][3];				/* We assign the left second member to right.		*/
	Card[2][3] = tempCard[0];				/* We assign the saved first member to right.		*/
	Card[3][3] = tempCard[1];				/* We assign the saved second member to right.		*/

	tempCard[2] = Card[1][1];				/* We save third member of card.					*/
	tempCard[3] = Card[1][2];				/* We save fourth member of card.					*/
	Card[1][1] = Card[3][1];				/* We assign the left third member to right.		*/
	Card[1][2] = Card[2][1];				/* We assign the left fourth member to right.		*/
	Card[3][1] = Card[4][2];				/* We assign the left third member to right.		*/
	Card[2][1] = Card[4][1];				/* We assign the left fourth member to right.		*/
	Card[4][2] = Card[2][2];				/* We assign the left third member to right.		*/
	Card[4][1] = Card[3][2];				/* We assign the left fourth member to right.		*/
	Card[2][2] = tempCard[2];				/* We assign the saved third member to right.		*/
	Card[3][2] = tempCard[3];				/* We assign the saved fourth member to right.		*/
}

void Tsuro::RandomValueCreater()					/* It creates random numbers for indexes.			*/
{
	int random = 0;								/* It's our random value.							*/
	int temp = 1, i = 0, j = 0;					/* They are just counters and flag.					*/

	for (int i = 0; i < 8; ++i)					/* We make a loop for to initialize our arrays.		*/
	{
		RandomValues[i] = 0;					/* We initialize our random value array.			*/
		ReverseValues[i] = 0;					/* We initialize our reverse of random array.		*/
	}

	while( i < 8 )								/* We make a loop for size of our array.			*/
	{
		random = rand()%8+1;					/* We create a random value between 8 - 1.			*/

		j = 0;									/* We re-initialize our counter.					*/

		while( j < 8 )							/* We make a loop for checking same values.			*/
		{
			if ( RandomValues[j] == random )	/* If we have same value inside our array we check.	*/
			{
				break;							/* If we have same value then we break the loop.	*/
			}

			++j;								/* We count in our array.							*/

			if ( j == 8 )						/* We check if we are end of the array size.		*/
			{
				temp = 0;						/* If we are then we make our flag zero.			*/
			}
		}

		if ( temp == 0 )						/* We check if our flag is zero.					*/
		{
			RandomValues[i] = random;			/* If it is then we save our random value in array.	*/
			++i;								/* We count the random value.						*/
			temp = 1;							/* We make flag one again.							*/
		}			
	}

	for (int i = 7; i >= 0; --i)				/* We make a loop for to make reverse value array.	*/
	{
		ReverseValues[7-i] = RandomValues[i];	/* We save our reverse array of random array.		*/
	}
}

void Tsuro::firstCard(int Card[6][4]) const			/* It creates first card.							*/
{
	for (int i = 0; i < 6; ++i)						/* We make a loop for coloumns.						*/
	{
		if ( i == 2 )								/* We check if our index equals to 2.				*/
		{
			Card[i][0] = RandomValues[0];			/* We assign our first random value to card.		*/
			Card[i+1][0] = RandomValues[7];			/* We assign our second random value to card.		*/
			Card[i][1] = ReverseValues[0];			/* We assign our first reverse value to card.		*/
			Card[i+1][1] = ReverseValues[7];		/* We assign our second reverse value to card.		*/
			Card[i][2] = RandomValues[1];			/* We assign our third random value to card.		*/
			Card[i+1][2] = RandomValues[6];			/* We assign our fourth random value to card.		*/
			Card[i][3] = ReverseValues[1];			/* We assign our third reverse value to card.		*/
			Card[i+1][3] = ReverseValues[6];		/* We assign our fourth reverse value to card.		*/
		}
		else if ( i == 0 )							/* We check if our index equals to 0.				*/
		{
			Card[i][1] = RandomValues[2];			/* We assign our fifth random value to card.		*/
			Card[i+1][1] = RandomValues[5];			/* We assign our sixth random value to card.		*/
			Card[i][2] = ReverseValues[2];			/* We assign our fifth reverse value to card.		*/
			Card[i+1][2] = ReverseValues[5];		/* We assign our sixth reverse value to card.		*/
		}
		else if ( i == 4 )							/* We check if our index equals to 4.				*/
		{
			Card[i][1] = RandomValues[3];			/* We assign our seventh random value to card.		*/
			Card[i+1][1] = RandomValues[4];			/* We assign our eighth random value to card.		*/
			Card[i][2] = ReverseValues[3];			/* We assign our seventh reverse value to card.		*/
			Card[i+1][2] = ReverseValues[4];		/* We assign our eighth reverse value to card.		*/
		}
	}
}

void Tsuro::secondCard(int Card[6][4]) const		/* It creates second card.							*/
{
	for (int i = 0; i < 6; ++i)						/* We make a loop for coloumns.						*/
	{
		if ( i == 2 )								/* We check if our index equals to 2.				*/
		{
			Card[i][0] = RandomValues[0];			/* We assign our first random value to card.		*/
			Card[i][1] = ReverseValues[0];			/* We assign our first reverse value to card.		*/
			Card[i][2] = ReverseValues[7];			/* We assign our second reverse value to card.		*/
			Card[i][3] = RandomValues[7];			/* We assign our second random value to card.		*/

			Card[i+1][0] = RandomValues[1];			/* We assign our third random value to card.		*/
			Card[i+1][1] = ReverseValues[1];		/* We assign our third reverse value to card.		*/
			Card[i+1][2] = ReverseValues[6];		/* We assign our fourth reverse value to card.		*/
			Card[i+1][3] = RandomValues[6];			/* We assign our fourth random value to card.		*/
		}
		else if ( i == 0 )							/* We check if our index equals to 0.				*/
		{
			Card[i][1] = RandomValues[2];			/* We assign our fifth random value to card.		*/
			Card[i][2] = ReverseValues[2];			/* We assign our fifth reverse value to card.		*/
			Card[i+1][1] = RandomValues[5];			/* We assign our sixth random value to card.		*/
			Card[i+1][2] = ReverseValues[5];		/* We assign our sixth reverse value to card.		*/
		}
		else if ( i == 4 )							/* We check if our index equals to 4.				*/
		{
			Card[i][1] = RandomValues[3];			/* We assign our seventh random value to card.		*/
			Card[i+1][1] = RandomValues[4];			/* We assign our eighth random value to card.		*/
			Card[i][2] = ReverseValues[3];			/* We assign our seventh reverse value to card.		*/
			Card[i+1][2] = ReverseValues[4];		/* We assign our eighth reverse value to card.		*/
		}
	}
}

void Tsuro::thirdCard(int Card[6][4]) const			/* It creates third card.							*/
{
	for (int i = 0; i < 6; ++i)						/* We make a loop for coloumns.						*/
	{
		if ( i == 2 )								/* We check if our index equals to 2.				*/
		{
			Card[i][0] = RandomValues[0];			/* We assign our first random value to card.		*/
			Card[i][1] = ReverseValues[0];			/* We assign our first reverse value to card.		*/
			Card[i][2] = ReverseValues[7];			/* We assign our second reverse value to card.		*/
			Card[i][3] = RandomValues[7];			/* We assign our second random value to card.		*/

			Card[i+1][0] = RandomValues[1];			/* We assign our third random value to card.		*/
			Card[i+1][1] = ReverseValues[1];		/* We assign our third reverse value to card.		*/
			Card[i+1][2] = ReverseValues[6];		/* We assign our fourth reverse value to card.		*/
			Card[i+1][3] = RandomValues[6];			/* We assign our fourth random value to card.		*/
		}
		else if ( i == 0 )							/* We check if our index equals to 0.				*/
		{
			Card[i][1] = RandomValues[2];			/* We assign our fifth random value to card.		*/
			Card[i+1][1] = RandomValues[3];			/* We assign our seventh random value to card.		*/

			Card[i][2] = RandomValues[4];			/* We assign our eighth random value to card.		*/
			Card[i+1][2] = RandomValues[5];			/* We assign our sixth random value to card.		*/
		}
		else if ( i == 4 )							/* We check if our index equals to 4.				*/
		{
			Card[i][1] = ReverseValues[3];			/* We assign our seventh reverse value to card.		*/
			Card[i+1][1] = ReverseValues[2];		/* We assign our fifth reverse value to card.		*/

			Card[i][2] = ReverseValues[5];			/* We assign our sixth reverse value to card.		*/
			Card[i+1][2] = ReverseValues[4];		/* We assign our eighth reverse value to card.		*/
		}
	}
}

void Tsuro::fourthCard(int Card[6][4]) const		/* It creates fourth card.							*/
{
	for (int i = 0; i < 6; ++i)						/* We make a loop for coloumns.						*/
	{
		if ( i == 2 )								/* We check if our index equals to 2.				*/
		{
			Card[i][0] = RandomValues[0];			/* We assign our first random value to card.		*/
			Card[i][1] = ReverseValues[0];			/* We assign our first reverse value to card.		*/
			Card[i][2] = ReverseValues[7];			/* We assign our second reverse value to card.		*/
			Card[i][3] = RandomValues[7];			/* We assign our second random value to card.		*/

			Card[i+1][0] = RandomValues[1];			/* We assign our third random value to card.		*/
			Card[i+1][1] = ReverseValues[1];		/* We assign our third reverse value to card.		*/
			Card[i+1][2] = ReverseValues[6];		/* We assign our fourth reverse value to card.		*/
			Card[i+1][3] = RandomValues[6];			/* We assign our fourth random value to card.		*/
		}
		else if ( i == 0 )							/* We check if our index equals to 0.				*/
		{
			Card[i][1] = RandomValues[2];			/* We assign our fifth random value to card.		*/
			Card[i+1][1] = RandomValues[3];			/* We assign our seventh random value to card.		*/

			Card[i][2] = RandomValues[4];			/* We assign our eighth random value to card.		*/
			Card[i+1][2] = RandomValues[5];			/* We assign our sixth random value to card.		*/
		}
		else if ( i == 4 )							/* We check if our index equals to 4.				*/
		{
			Card[i][2] = ReverseValues[3];			/* We assign our seventh reverse value to card.		*/
			Card[i+1][2] = ReverseValues[2];		/* We assign our fifth reverse value to card.		*/

			Card[i][1] = ReverseValues[5];			/* We assign our sixth reverse value to card.		*/
			Card[i+1][1] = ReverseValues[4];		/* We assign our eighth reverse value to card.		*/
		}
	}
}

void Tsuro::fifthCard(int Card[6][4]) const			/* It creates fifth card.							*/
{
	for (int i = 0; i < 6; ++i)						/* We make a loop for coloumns.						*/
	{
		if ( i == 2 )								/* We check if our index equals to 2.				*/
		{
			Card[i][0] = RandomValues[0];			/* We assign our first random value to card.		*/
			Card[i][1] = ReverseValues[0];			/* We assign our first reverse value to card.		*/
			Card[i][2] = RandomValues[6];			/* We assign our fourth random value to card.		*/
			Card[i][3] = ReverseValues[6];			/* We assign our fourth reverse value to card.		*/

			Card[i+1][0] = ReverseValues[1];		/* We assign our third reverse value to card.		*/
			Card[i+1][1] = RandomValues[1];			/* We assign our third random value to card.		*/
			Card[i+1][2] = ReverseValues[7];		/* We assign our second reverse value to card.		*/
			Card[i+1][3] = RandomValues[7];			/* We assign our second random value to card.		*/
		}
		else if ( i == 0 )							/* We check if our index equals to 0.				*/
		{
			Card[i][1] = RandomValues[2];			/* We assign our fifth random value to card.		*/
			Card[i+1][1] = RandomValues[3];			/* We assign our seventh random value to card.		*/

			Card[i][2] = RandomValues[4];			/* We assign our eighth random value to card.		*/
			Card[i+1][2] = RandomValues[5];			/* We assign our sixth random value to card.		*/
		}
		else if ( i == 4 )							/* We check if our index equals to 4.				*/
		{
			Card[i][1] = ReverseValues[3];			/* We assign our seventh reverse value to card.		*/
			Card[i+1][1] = ReverseValues[2];		/* We assign our fifth reverse value to card.		*/

			Card[i][2] = ReverseValues[5];			/* We assign our sixth reverse value to card.		*/
			Card[i+1][2] = ReverseValues[4];		/* We assign our eighth reverse value to card.		*/
		}
	}
}

void Tsuro::sixthCard(int Card[6][4]) const			/* It creates sixth card.							*/
{
	for (int i = 0; i < 6; ++i)						/* We make a loop for coloumns.						*/
	{
		if ( i == 2 )								/* We check if our index equals to 2.				*/
		{
			Card[i][0] = RandomValues[0];			/* We assign our first random value to card.		*/
			Card[i][1] = ReverseValues[0];			/* We assign our first reverse value to card.		*/
			Card[i-1][1] = ReverseValues[7];		/* We assign our second reverse value to card.		*/
			Card[i-2][1] = RandomValues[7];			/* We assign our second random value to card.		*/

			Card[i][3] = RandomValues[1];			/* We assign our third random value to card.		*/
			Card[i][2] = ReverseValues[1];			/* We assign our third reverse value to card.		*/
			Card[i-1][2] = ReverseValues[6];		/* We assign our fourth reverse value to card.		*/
			Card[i-2][2] = RandomValues[6];			/* We assign our fourth random value to card.		*/
		}
		else if ( i == 3 )							/* We check if our index equals to 3.				*/
		{
			Card[i][0] = RandomValues[2];			/* We assign our fifth random value to card.		*/
			Card[i][1] = ReverseValues[2];			/* We assign our fifth reverse value to card.		*/
			Card[i+1][1] = ReverseValues[5];		/* We assign our sixth reverse value to card.		*/
			Card[i+2][1] = RandomValues[5];			/* We assign our sixth random value to card.		*/

			Card[i][3] = RandomValues[3];			/* We assign our seventh random value to card.		*/
			Card[i][2] = ReverseValues[3];			/* We assign our seventh reverse value to card.		*/
			Card[i+1][2] = ReverseValues[4];		/* We assign our eighth reverse value to card.		*/
			Card[i+2][2] = RandomValues[4];			/* We assign our eighth random value to card.		*/
		}
	}
}

void Tsuro::seventhCard(int Card[6][4]) const		/* It creates seventh card.							*/
{
	for (int i = 0; i < 6; ++i)						/* We make a loop for coloumns.						*/
	{
		if ( i == 2 )								/* We check if our index equals to 2.				*/
		{
			Card[i][0] = RandomValues[0];			/* We assign our first random value to card.		*/
			Card[i][1] = ReverseValues[0];			/* We assign our first reverse value to card.		*/
			Card[i-1][1] = ReverseValues[7];		/* We assign our second reverse value to card.		*/
			Card[i-2][1] = RandomValues[7];			/* We assign our second random value to card.		*/

			Card[i][3] = RandomValues[1];			/* We assign our third random value to card.		*/
			Card[i][2] = ReverseValues[1];			/* We assign our third reverse value to card.		*/
			Card[i+2][1] = ReverseValues[6];		/* We assign our fourth reverse value to card.		*/
			Card[i+3][1] = RandomValues[6];			/* We assign our fourth random value to card.		*/
		}
		else if ( i == 3 )							/* We check if our index equals to 3.				*/
		{
			Card[i][0] = RandomValues[2];			/* We assign our fifth random value to card.		*/
			Card[i][1] = ReverseValues[2];			/* We assign our fifth reverse value to card.		*/
			Card[i-3][2] = RandomValues[5];			/* We assign our sixth random value to card.		*/
			Card[i-2][2] = ReverseValues[5];		/* We assign our sixth reverse value to card.		*/

			Card[i][3] = RandomValues[3];			/* We assign our seventh random value to card.		*/
			Card[i][2] = ReverseValues[3];			/* We assign our seventh reverse value to card.		*/
			Card[i+1][2] = ReverseValues[4];		/* We assign our eighth reverse value to card.		*/
			Card[i+2][2] = RandomValues[4];			/* We assign our eighth random value to card.		*/
		}
	}
}

void Tsuro::eighthCard(int Card[6][4]) const		/* It creates eighth card.							*/
{
	for (int i = 0; i < 6; ++i)						/* We make a loop for coloumns.						*/
	{
		if ( i == 2 )								/* We check if our index equals to 2.				*/
		{
			Card[i][0] = RandomValues[0];			/* We assign our first random value to card.		*/
			Card[i][1] = ReverseValues[0];			/* We assign our first reverse value to card.		*/
			Card[i-1][1] = ReverseValues[7];		/* We assign our second reverse value to card.		*/
			Card[i-2][1] = RandomValues[7];			/* We assign our second random value to card.		*/

			Card[i+1][0] = RandomValues[1];			/* We assign our third random value to card.		*/
			Card[i+1][1] = ReverseValues[1];		/* We assign our third reverse value to card.		*/
			Card[i][2] = ReverseValues[6];			/* We assign our fourth reverse value to card.		*/
			Card[i][3] = RandomValues[6];			/* We assign our fourth random value to card.		*/
		}
		else if ( i == 3 )							/* We check if our index equals to 3.				*/
		{
			Card[i+1][1] = RandomValues[2];			/* We assign our fifth random value to card.		*/
			Card[i+2][1] = ReverseValues[2];		/* We assign our fifth reverse value to card.		*/
			Card[i-3][2] = ReverseValues[5];		/* We assign our sixth reverse value to card.		*/
			Card[i-2][2] = RandomValues[5];			/* We assign our sixth random value to card.		*/

			Card[i][3] = RandomValues[3];			/* We assign our seventh random value to card.		*/
			Card[i][2] = ReverseValues[3];			/* We assign our seventh reverse value to card.		*/
			Card[i+1][2] = ReverseValues[4];		/* We assign our eighth reverse value to card.		*/
			Card[i+2][2] = RandomValues[4];			/* We assign our eighth random value to card.		*/
		}
	}
}

void Tsuro::ninethCard(int Card[6][4]) const		/* It creates nineth card.							*/
{
	for (int i = 0; i < 6; ++i)						/* We make a loop for coloumns.						*/
	{
		if ( i == 2 )								/* We check if our index equals to 2.				*/
		{
			Card[i][0] = RandomValues[0];			/* We assign our first random value to card.		*/
			Card[i+1][0] = RandomValues[7];			/* We assign our second random value to card.		*/
			Card[i][1] = ReverseValues[0];			/* We assign our first reverse value to card.		*/
			Card[i+1][1] = ReverseValues[7];		/* We assign our second reverse value to card.		*/
			Card[i][2] = RandomValues[1];			/* We assign our third random value to card.		*/
			Card[i+1][2] = RandomValues[6];			/* We assign our fourth random value to card.		*/
			Card[i][3] = ReverseValues[1];			/* We assign our third reverse value to card.		*/
			Card[i+1][3] = ReverseValues[6];		/* We assign our fourth reverse value to card.		*/
		}
		else if ( i == 0 )							/* We check if our index equals to 0.				*/
		{
			Card[i][1] = RandomValues[2];			/* We assign our fifth random value to card.		*/
			Card[i+1][1] = RandomValues[3];			/* We assign our seventh random value to card.		*/

			Card[i][2] = RandomValues[4];			/* We assign our eighth random value to card.		*/
			Card[i+1][2] = RandomValues[5];			/* We assign our sixth random value to card.		*/
		}
		else if ( i == 4 )							/* We check if our index equals to 4.				*/
		{
			Card[i][2] = ReverseValues[3];			/* We assign our seventh reverse value to card.		*/
			Card[i+1][2] = ReverseValues[2];		/* We assign our fifth reverse value to card.		*/

			Card[i][1] = ReverseValues[5];			/* We assign our sixth reverse value to card.		*/
			Card[i+1][1] = ReverseValues[4];		/* We assign our eighth reverse value to card.		*/
		}
	}
}

void Tsuro::tenthCard(int Card[6][4]) const			/* It creates tenth card.							*/
{
	for (int i = 0; i < 6; ++i)						/* We make a loop for coloumns.						*/
	{
		if ( i == 2 )								/* We check if our index equals to 2.				*/
		{
			Card[i][0] = RandomValues[0];			/* We assign our first random value to card.		*/
			Card[i+1][0] = RandomValues[7];			/* We assign our second random value to card.		*/
			Card[i][1] = ReverseValues[0];			/* We assign our first reverse value to card.		*/
			Card[i+1][1] = ReverseValues[7];		/* We assign our second reverse value to card.		*/
			Card[i][2] = RandomValues[1];			/* We assign our third random value to card.		*/
			Card[i+1][2] = RandomValues[6];			/* We assign our fourth random value to card.		*/
			Card[i][3] = ReverseValues[1];			/* We assign our third reverse value to card.		*/
			Card[i+1][3] = ReverseValues[6];		/* We assign our fourth reverse value to card.		*/
		}
		else if ( i == 0 )							/* We check if our index equals to 0.				*/
		{
			Card[i][1] = RandomValues[2];			/* We assign our fifth random value to card.		*/
			Card[i+1][1] = RandomValues[3];			/* We assign our seventh random value to card.		*/

			Card[i][2] = RandomValues[4];			/* We assign our eighth random value to card.		*/
			Card[i+1][2] = RandomValues[5];			/* We assign our sixth random value to card.		*/
		}
		else if ( i == 4 )							/* We check if our index equals to 4.				*/
		{
			Card[i][1] = ReverseValues[3];			/* We assign our seventh reverse value to card.		*/
			Card[i+1][1] = ReverseValues[2];		/* We assign our fifth reverse value to card.		*/

			Card[i][2] = ReverseValues[5];			/* We assign our sixth reverse value to card.		*/
			Card[i+1][2] = ReverseValues[4];		/* We assign our eighth reverse value to card.		*/
		}
	}
}

void Tsuro::CardCreater(int Card[6][4])					/* It creates our different cards.				*/
{
	int k = 0;							/* It is just to make a random number.						*/

	k = rand() % 10 + 1;				/* We make a random number between one - ten.				*/

	switch(k)							/* We make switch for our random card.						*/
	{
		case 1: firstCard(Card);		/* If our random value equals to 1 then we create 1st card.	*/
		break;							/* Then we end the switch.									*/

		case 2: secondCard(Card);		/* If our random value equals to 2 then we create 2nd card.	*/
		break;							/* Then we end the switch.									*/

		case 3: thirdCard(Card);		/* If our random value equals to 3 then we create 3rd card.	*/
		break;							/* Then we end the switch.									*/

		case 4: fourthCard(Card);		/* If our random value equals to 4 then we create 4th card.	*/
		break;							/* Then we end the switch.									*/

		case 5: fifthCard(Card);		/* If our random value equals to 5 then we create 5th card.	*/
		break;							/* Then we end the switch.									*/

		case 6: sixthCard(Card);		/* If our random value equals to 6 then we create 6th card.	*/
		break;							/* Then we end the switch.									*/

		case 7: seventhCard(Card);		/* If our random value equals to 7 then we create 7th card.	*/
		break;							/* Then we end the switch.									*/

		case 8: eighthCard(Card);		/* If our random value equals to 8 then we create 8th card.	*/
		break;							/* Then we end the switch.									*/

		case 9: ninethCard(Card);		/* If our random value equals to 9 then we create 9th card.	*/
		break;							/* Then we end the switch.									*/

		case 10: tenthCard(Card);		/* If our random value equals to 10 then we create 10th card.*/
		break;							/* Then we end the switch.									*/
	}
}

void Tsuro::CardPrinter(const int Card[6][4]) const		/* It prints the card with its formal version.	*/
{
	for (int i = 0; i < 6; ++i)						/* We make a loop for columns of card.				*/ 
	{
		if ( i == 2 || i == 3 )						/* We check if our index of card equals to 2 or 3.	*/
		{
			for (int j = 0; j < 4; ++j)				/* If it is then we make a loop for row.			*/
			{
				cout << Card[i][j];					/* We print the card's member.						*/

				if ( j == 1 || j == 3 )				/* Then we check for push a space.					*/
				{
					cout << "  ";					/* We print the space.								*/
				}
				else 								/* If we have more spaces we check.					*/
				{
					cout << "   ";					/* We print double spaces.							*/
				}
			}

			cout << endl;							/* We finish the row.								*/
		}
		else if ( i == 1 || i == 4 )				/* We check if our index of card equals to 1 or 4.	*/
		{
			cout << ":";							/* If it is then we print our colon.				*/

			for (int j = 0; j < 4; ++j)				/* We make a loop for row.							*/
			{
				if ( j == 1 || j == 2 )				/* We check if our index is 1 or 2.					*/
				{
					cout << "  ";					/* If it is then we print a space.					*/
					cout << Card[i][j];				/* We print our card member.						*/
				}
				else 								/* If our indexes are not 1 or 2 we check.			*/
				{
					cout << " ";					/* Then we print space.								*/
				}
			}

			cout << "  :" << endl;					/* We print space and colon for end of the row.		*/
		}
		else if ( i == 0 || i == 5 )				/* We check if our index of card equals to 0 or 5.	*/
		{
			for (int j = 0; j < 4; ++j)				/* We make a loop for row.							*/
			{
				if ( j == 1 || j == 2 )				/* We check if our index is 1 or 2.					*/
				{
					if ( j == 2 )					/* We check if our index is 2.						*/
					{
						cout << "..";				/* Then we print our two dots.						*/
					}
					else							/* If our indexes are not 2 we check.				*/
					{
						cout << "....";				/* Then we print our four dots.						*/
					}

					cout << Card[i][j];				/* We print our card member.						*/
				}
			}

			cout << "...." << endl;					/* We print four dots end of the row.				*/
		}
	}
}

void Tsuro::CardInitialize(int Card[6][4]) const		/* It initialize our cards with zeros.			*/
{
	for (int i = 0; i < 6; ++i)					/* We create a loop for columns of card.	*/
	{
		for (int j = 0; j < 4; ++j)				/* We create a loop for rows of card.		*/
		{
			Card[i][j] = 0;						/* We initialize our card with zeros.		*/
		}
	}
}