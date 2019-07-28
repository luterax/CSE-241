/*
											CSE 241 Homework Assignment 4

												OMER_CEVIK_161044004

					# 			  	  In that programme ve create logical gates.						 #
					# 					And we calculate logical problems.							  	 # 

																											*/
#include <iostream>			/* We use cout etc.					*/
#include <cstring>			/* We use strcmp.					*/
using namespace std;		/* We use cout etc.					*/
#include "gates.h"			/* It's our base class.				*/
#include "input.h"			/* It's our input derived class.	*/
#include "output.h"			/* It's our output derived class.	*/
#include "not.h"			/* It's our not derived class.		*/
#include "or.h"				/* It's our or derived class.		*/
#include "and.h"			/* It's our and derived class.		*/
#include "ff.h"				/* It's our flipflop derived class.	*/
#include "decoder.h"		/* It's our decoder derived class.	*/

int main()					/* It's our main function.			*/
{
	int l = 0, m = 0, r = 0, p = 0, s = 0, inputFound = 0;	/* They are our gate and input counters.	*/

	input I;	/* It creates Input variables.		*/
	And A;		/* It creates And variables.		*/
	Or O;		/* It creates Or variables.			*/
	Not N;		/* It creates Not variables.		*/
	decoder D;	/* It creates Decoder variables.	*/
	output OUT;	/* It creates Output variables.		*/
	ff F;		/* It creates Flipflop variables.	*/

	for (int ind = 0; ind < I.getInputColumnSize(); ++ind)					/* In here we create a loop to evaluate the result for all inputs.			*/
	{
		for (int i = 0; i < I.getGateSize(); ++i)							/* We create a loop for gates to evaluate the result.						*/
		{
			if ( I.getGate(i)[0] == 'A' )									/* That if evaluates AND gate.												*/
			{
				for (int j = 0; j < I.getInputSize(); ++j)
				{
					for (int k = 1; k < 3; ++k)
					{
						if ( strcmp(I.getInputName(j),A.getAndName(l,k)) == 0 )
						{
							++inputFound;

							if ( inputFound == 1 )
							{
								A.setInp1(I.getInput(ind,j));
							}
							else if ( inputFound == 2 )
							{
								A.setInp2(I.getInput(ind,j));
								A.evaluate(A.getInp1(),A.getInp2());
							}
						}
					}
				}

				if ( inputFound == 0 || inputFound == 1 )
				{
					for (int a = 0; a < A.getAndGateSize(); ++a)
					{
						for (int k = 1; k < 3; ++k)
						{
							if ( strcmp( A.getAndName(l,k),A.getAndName(a,0)) == 0 )
							{
								++inputFound;

								if ( inputFound == 1 )
								{
									A.setInp1(A.getOutput());
								}
								else if ( inputFound == 2 )
								{
									A.setInp2(A.getOutput());
									A.evaluate(A.getInp1(),A.getInp2());
									inputFound = 0;
								}
							}
						}
					}

					for (int a = 0; a < O.getOrGateSize(); ++a)
					{
						for (int k = 1; k < 3; ++k)
						{
							if ( strcmp( A.getAndName(l,k),O.getOrName(a,0)) == 0 )
							{
								++inputFound;

								if ( inputFound == 1 )
								{
									A.setInp1(O.getOutput());
								}
								else if ( inputFound == 2 )
								{
									A.setInp2(O.getOutput());
									A.evaluate(A.getInp1(),A.getInp2());
									inputFound = 0;
								}
							}
						}
					}

					for (int a = 0; a < N.getNotGateSize(); ++a)
					{
						for (int k = 1; k < 3; ++k)
						{
							if ( strcmp( A.getAndName(l,k),N.getNotName(a,0)) == 0 )
							{
								++inputFound;

								if ( inputFound == 1 )
								{
									A.setInp1(N.getOutput());
								}
								else if ( inputFound == 2 )
								{
									A.setInp2(N.getOutput());
									A.evaluate(A.getInp1(),A.getInp2());
									inputFound = 0;
								}
							}
						}
					}

					for (int a = 0; a < F.getFfGateSize(); ++a)
					{
						for (int k = 1; k < 3; ++k)
						{
							if ( strcmp( A.getAndName(l,k),F.getFfName(a,0)) == 0 )
							{
								++inputFound;

								if ( inputFound == 1 )
								{
									A.setInp1(F.getOutput());
								}
								else if ( inputFound == 2 )
								{
									A.setInp2(F.getOutput());
									A.evaluate(A.getInp1(),A.getInp2());
									inputFound = 0;
								}
							}
						}
					}

					for (int a = 0; a < D.getDecGateSize(); ++a)
					{
						for (int k = 0; k < 4; ++k)
						{
							for (int t = 1; t < 3; ++t)
							{
								if ( strcmp( A.getAndName(l,t),D.getDecName(a,k)) == 0 )
								{
									++inputFound;

									if ( inputFound == 1 )
									{
										if ( k == 0 )
										{
											A.setInp1(D.getDec1());
										}
										else if ( k == 1 )
										{
											A.setInp1(D.getDec2());
										}
										else if ( k == 2 )
										{
											A.setInp1(D.getDec3());
										}
										else
										{
											A.setInp1(D.getDec4());
										}
									}
									else if ( inputFound == 2 )
									{
										if ( k == 0 )
										{
											A.setInp2(D.getDec1());
										}
										else if ( k == 1 )
										{
											A.setInp2(D.getDec2());
										}
										else if ( k == 2 )
										{
											A.setInp2(D.getDec3());
										}
										else
										{
											A.setInp2(D.getDec4());
										}
										A.evaluate(A.getInp1(),A.getInp2());
										inputFound = 0;
									}
								}
							}
						}
					}

					for (int j = 0; j < OUT.getOutputSize(); ++j)
					{
						if ( strcmp( A.getAndName(l,0),OUT.getOutputName(j)) == 0 )
						{
							++inputFound;
							OUT.setOutputResult(j,A.getOutput());
						}
					}
				}
				inputFound = 0;
				++l;
			}
			else if ( I.getGate(i)[0] == 'O' && I.getGate(i)[1] == 'R' )	/* That if evaluates OR gate.												*/
			{
				for (int j = 0; j < I.getInputSize(); ++j)
				{
					for (int k = 1; k < 3; ++k)
					{
						if ( strcmp(I.getInputName(j),O.getOrName(m,k)) == 0 )
						{
							++inputFound;

							if ( inputFound == 1 )
							{
								O.setInp1(I.getInput(ind,j));
							}
							else if ( inputFound == 2 )
							{
								O.setInp2(I.getInput(ind,j));
								O.evaluate(O.getInp1(),O.getInp2());
							}
						}
					}
				}

				if ( inputFound == 0 || inputFound == 1 )
				{
					for (int a = 0; a < A.getAndGateSize(); ++a)
					{
						for (int k = 1; k < 3; ++k)
						{
							if ( strcmp( O.getOrName(m,k),A.getAndName(a,0)) == 0 )
							{
								++inputFound;
								if ( inputFound == 1 )
								{
									O.setInp1(A.getOutput());
								}
								else if ( inputFound == 2 )
								{
									O.setInp2(A.getOutput());
									O.evaluate(O.getInp1(),O.getInp2());
									inputFound = 0;
								}
							}
						}
					}

					for (int a = 0; a < O.getOrGateSize(); ++a)
					{
						for (int k = 1; k < 3; ++k)
						{
							if ( strcmp( O.getOrName(m,k),O.getOrName(a,0)) == 0 )
							{
								++inputFound;

								if ( inputFound == 1 )
								{
									O.setInp1(O.getOutput());
								}
								else if ( inputFound == 2 )
								{
									O.setInp2(O.getOutput());
									O.evaluate(O.getInp1(),O.getInp2());
									inputFound = 0;
								}
							}
						}
					}

					for (int a = 0; a < N.getNotGateSize(); ++a)
					{
						for (int k = 1; k < 3; ++k)
						{
							if ( strcmp( O.getOrName(m,k),N.getNotName(a,0)) == 0 )
							{
								++inputFound;

								if ( inputFound == 1 )
								{
									O.setInp1(N.getOutput());
								}
								else if ( inputFound == 2 )
								{
									O.setInp2(N.getOutput());
									O.evaluate(O.getInp1(),O.getInp2());
									inputFound = 0;
								}
							}
						}
					}

					for (int a = 0; a < F.getFfGateSize(); ++a)
					{
						for (int k = 1; k < 3; ++k)
						{
							if ( strcmp( O.getOrName(m,k),F.getFfName(a,0)) == 0 )
							{
								++inputFound;

								if ( inputFound == 1 )
								{
									O.setInp1(F.getOutput());
								}
								else if ( inputFound == 2 )
								{
									O.setInp2(F.getOutput());
									O.evaluate(O.getInp1(),O.getInp2());
									inputFound = 0;
								}
							}
						}
					}

					for (int a = 0; a < D.getDecGateSize(); ++a)
					{
						for (int k = 0; k < 4; ++k)
						{
							for (int t = 1; t < 3; ++t)
							{
								if ( strcmp( O.getOrName(m,t),D.getDecName(a,k)) == 0 )
								{
									++inputFound;

									if ( inputFound == 1 )
									{
										if ( k == 0 )
										{
											O.setInp1(D.getDec1());
										}
										else if ( k == 1 )
										{
											O.setInp1(D.getDec2());
										}
										else if ( k == 2 )
										{
											O.setInp1(D.getDec3());
										}
										else
										{
											O.setInp1(D.getDec4());
										}
									}
									else if ( inputFound == 2 )
									{
										if ( k == 0 )
										{
											O.setInp2(D.getDec1());
										}
										else if ( k == 1 )
										{
											O.setInp2(D.getDec2());
										}
										else if ( k == 2 )
										{
											O.setInp2(D.getDec3());
										}
										else
										{
											O.setInp2(D.getDec4());
										}
										O.evaluate(O.getInp1(),O.getInp2());
										inputFound = 0;
									}
								}
							}
						}
					}

					for (int j = 0; j < OUT.getOutputSize(); ++j)
					{
						if ( strcmp( O.getOrName(m,0),OUT.getOutputName(j)) == 0 )
						{
							++inputFound;
							OUT.setOutputResult(j,O.getOutput());
						}
					}
				}
				inputFound = 0;	
				++m;
			}
			else if ( I.getGate(i)[0] == 'N' )								/* That if evaluates NOT gate.												*/
			{
				for (int j = 0; j < I.getInputSize(); ++j)
				{
					if ( strcmp(I.getInputName(j),N.getNotName(r,1)) == 0 )
					{
						++inputFound;
						N.setInp1(I.getInput(ind,j));
						N.setInp2(I.getInput(ind,j));
						N.evaluate(N.getInp1(),N.getInp2());
					}
				}

				if ( inputFound == 0 )
				{
					for (int a = 0; a < A.getAndGateSize(); ++a)
					{
						if ( strcmp( N.getNotName(r,1),A.getAndName(a,0)) == 0 )
						{
							N.setInp1(A.getOutput());
							N.setInp2(A.getOutput());
							N.evaluate(N.getInp1(),N.getInp2());
							++inputFound;
						}
					}

					for (int a = 0; a < O.getOrGateSize(); ++a)
					{
						if ( strcmp( N.getNotName(r,1),O.getOrName(a,0)) == 0 )
						{
							N.setInp1(O.getOutput());
							N.setInp2(O.getOutput());
							N.evaluate(N.getInp1(),N.getInp2());
							++inputFound;
						}
					}

					for (int a = 0; a < N.getNotGateSize(); ++a)
					{
						if ( strcmp( N.getNotName(r,1),N.getNotName(a,0)) == 0 )
						{
							N.setInp1(N.getOutput());
							N.setInp2(N.getOutput());
							N.evaluate(N.getInp1(),N.getInp2());
							++inputFound;
						}
					}

					for (int a = 0; a < F.getFfGateSize(); ++a)
					{
						if ( strcmp( N.getNotName(r,1),F.getFfName(a,0)) == 0 )
						{
							N.setInp1(F.getOutput());
							N.setInp2(F.getOutput());
							N.evaluate(N.getInp1(),N.getInp2());
							++inputFound;
						}
					}

					for (int a = 0; a < D.getDecGateSize(); ++a)
					{
						for (int k = 0; k < 4; ++k)
						{
							if ( strcmp( N.getNotName(r,1),D.getDecName(a,k)) == 0 )
							{
								if ( k == 0 )
								{
									N.setInp1(D.getDec1());
									N.setInp2(D.getDec1());
								}
								else if ( k == 1 )
								{
									N.setInp1(D.getDec2());
									N.setInp2(D.getDec2());
								}
								else if ( k == 2 )
								{
									N.setInp1(D.getDec3());
									N.setInp2(D.getDec3());
								}
								else
								{
									N.setInp1(D.getDec4());
									N.setInp2(D.getDec4());
								}
								
								N.evaluate(N.getInp1(),N.getInp2());
								++inputFound;
							}
						}
					}

					for (int j = 0; j < OUT.getOutputSize(); ++j)
					{
						if ( strcmp( N.getNotName(r,0),OUT.getOutputName(j)) == 0 )
						{
							++inputFound;
							OUT.setOutputResult(j,N.getOutput());
						}
					}
				}
				inputFound = 0;	
				++r;
			}
			else if ( I.getGate(i)[0] == 'F' )								/* That if evaluates FLIPFLOP gate.											*/
			{
				for (int j = 0; j < I.getInputSize(); ++j)
				{
					if ( strcmp(I.getInputName(j),F.getFfName(p,1)) == 0 )
					{
						++inputFound;
						F.setInp1(I.getInput(ind,j));
						F.setInp2(I.getInput(ind,j));
						F.evaluate(F.getInp1(),F.getInp2());
					}
				}
				if ( inputFound == 0 )
				{
					for (int a = 0; a < A.getAndGateSize(); ++a)
					{
						if ( strcmp( F.getFfName(p,1),A.getAndName(a,0)) == 0 )
						{
							F.setInp1(A.getOutput());
							F.setInp2(A.getOutput());
							F.evaluate(F.getInp1(),F.getInp2());
							++inputFound;
						}
					}

					for (int a = 0; a < O.getOrGateSize(); ++a)
					{
						if ( strcmp( F.getFfName(p,1),O.getOrName(a,0)) == 0 )
						{
							F.setInp1(O.getOutput());
							F.setInp2(O.getOutput());
							F.evaluate(F.getInp1(),F.getInp2());
							++inputFound;
						}
					}

					for (int a = 0; a < N.getNotGateSize(); ++a)
					{
						if ( strcmp( F.getFfName(p,1),N.getNotName(a,0)) == 0 )
						{
							F.setInp1(N.getOutput());
							F.setInp2(N.getOutput());
							F.evaluate(F.getInp1(),F.getInp2());
							++inputFound;
						}
					}

					for (int a = 0; a < F.getFfGateSize(); ++a)
					{
						if ( strcmp( F.getFfName(p,1),F.getFfName(a,0)) == 0 )
						{
							F.setInp1(F.getOutput());
							F.setInp2(F.getOutput());
							F.evaluate(F.getInp1(),F.getInp2());
							++inputFound;
						}
					}

					for (int a = 0; a < D.getDecGateSize(); ++a)
					{
						for (int k = 0; k < 4; ++k)
						{
							if ( strcmp( F.getFfName(p,1),D.getDecName(a,k)) == 0 )
							{
								if ( k == 0 )
								{
									F.setInp1(D.getDec1());
									F.setInp2(D.getDec1());
								}
								else if ( k == 1 )
								{
									F.setInp1(D.getDec2());
									F.setInp2(D.getDec2());
								}
								else if ( k == 2 )
								{
									F.setInp1(D.getDec3());
									F.setInp2(D.getDec3());
								}
								else
								{
									F.setInp1(D.getDec4());
									F.setInp2(D.getDec4());
								}
								
								F.evaluate(F.getInp1(),F.getInp2());
								++inputFound;
							}
						}
					}

					for (int j = 0; j < OUT.getOutputSize(); ++j)
					{
						if ( strcmp( F.getFfName(p,0),OUT.getOutputName(j)) == 0 )
						{
							++inputFound;
							OUT.setOutputResult(j,F.getOutput());
						}
					}
				}
				inputFound = 0;	
				++p;
			}
			else if ( I.getGate(i)[0] == 'D' )								/* That if evaluates DECODER gate.											*/
			{
				for (int j = 0; j < I.getInputSize(); ++j)
				{
					for (int k = 4; k < 6; ++k)
					{
						if ( strcmp(I.getInputName(j),D.getDecName(s,k)) == 0 )
						{
							++inputFound;

							if ( inputFound == 1 )
							{
								D.setInp1(I.getInput(ind,j));
							}
							else if ( inputFound == 2 )
							{
								D.setInp2(I.getInput(ind,j));
								D.evaluate(D.getInp1(),D.getInp2());
							}
						}
					}
				}

				if ( inputFound == 0 || inputFound == 1 )
				{
					for (int a = 0; a < A.getAndGateSize(); ++a)
					{
						for (int k = 4; k < 6; ++k)
						{
							if ( strcmp( D.getDecName(s,k),A.getAndName(a,0)) == 0 )
							{
								++inputFound;
								if ( inputFound == 1 )
								{
									D.setInp1(A.getOutput());
								}
								else if ( inputFound == 2 )
								{
									D.setInp2(A.getOutput());
									D.evaluate(D.getInp1(),D.getInp2());
									inputFound = 0;
								}
							}
						}
					}

					for (int a = 0; a < O.getOrGateSize(); ++a)
					{
						for (int k = 4; k < 6; ++k)
						{
							if ( strcmp( D.getDecName(s,k),O.getOrName(a,0)) == 0 )
							{
								++inputFound;

								if ( inputFound == 1 )
								{
									D.setInp1(O.getOutput());
								}
								else if ( inputFound == 2 )
								{
									D.setInp2(O.getOutput());
									D.evaluate(D.getInp1(),D.getInp2());
									inputFound = 0;
								}
							}
						}
					}

					for (int a = 0; a < N.getNotGateSize(); ++a)
					{
						for (int k = 4; k < 6; ++k)
						{
							if ( strcmp( D.getDecName(s,k),N.getNotName(a,0)) == 0 )
							{
								++inputFound;

								if ( inputFound == 1 )
								{
									D.setInp1(N.getOutput());
								}
								else if ( inputFound == 2 )
								{
									D.setInp2(N.getOutput());
									D.evaluate(D.getInp1(),D.getInp2());
									inputFound = 0;
								}
							}
						}
					}

					for (int a = 0; a < F.getFfGateSize(); ++a)
					{
						for (int k = 4; k < 6; ++k)
						{
							if ( strcmp( D.getDecName(s,k),F.getFfName(a,0)) == 0 )
							{
								++inputFound;

								if ( inputFound == 1 )
								{
									D.setInp1(F.getOutput());
								}
								else if ( inputFound == 2 )
								{
									D.setInp2(F.getOutput());
									D.evaluate(D.getInp1(),D.getInp2());
									inputFound = 0;
								}
							}
						}
					}

					for (int a = 0; a < D.getDecGateSize(); ++a)
					{
						for (int k = 0; k < 4; ++k)
						{
							for (int t = 4; t < 6; ++t)
							{
								if ( strcmp( D.getDecName(s,t),D.getDecName(a,k)) == 0 )
								{
									++inputFound;

									if ( inputFound == 1 )
									{
										if ( k == 0 )
										{
											D.setInp1(D.getDec1());
										}
										else if ( k == 1 )
										{
											D.setInp1(D.getDec2());
										}
										else if ( k == 2 )
										{
											D.setInp1(D.getDec3());
										}
										else
										{
											D.setInp1(D.getDec4());
										}
									}
									else if ( inputFound == 2 )
									{
										if ( k == 0 )
										{
											D.setInp2(D.getDec1());
										}
										else if ( k == 1 )
										{
											D.setInp2(D.getDec2());
										}
										else if ( k == 2 )
										{
											D.setInp2(D.getDec3());
										}
										else
										{
											D.setInp2(D.getDec4());
										}
										D.evaluate(D.getInp1(),D.getInp2());
										inputFound = 0;
									}
								}
							}
						}
					}

					for (int j = 0; j < OUT.getOutputSize(); ++j)
					{
						for (int k = 0; k < 4; ++k)
						{
							if ( strcmp( D.getDecName(s,k),OUT.getOutputName(j)) == 0 )
							{
								++inputFound;
								if ( k == 0 )
								{
									OUT.setOutputResult(j,D.getDec1());
								}
								else if ( k == 1 )
								{
									OUT.setOutputResult(j,D.getDec2());
								}
								else if ( k == 2 )
								{
									OUT.setOutputResult(j,D.getDec2());
								}
								else if ( k == 3 )
								{
									OUT.setOutputResult(j,D.getDec3());
								}
							}
						}
					}
				}
				inputFound = 0;	
				++s;
			}
		}

		for (int i = 0; i < I.getGateSize(); ++i)							/* In here we make a loop to find the results.								*/
		{
			if ( I.getGate(i)[0] == 'O' && I.getGate(i)[1] == 'U' )
			{
				for (int j = 0; j < I.getInputSize(); ++j)
				{
					for (int k = 0; k < OUT.getOutputSize(); ++k)
					{
						if ( strcmp(OUT.getOutputName(k),I.getInputName(j)) == 0 )
						{
							OUT.setOutputResult(k,I.getInput(ind,j));
						}
					}
				}

				for (int j = 0; j < A.getAndGateSize(); ++j)
				{
					for (int k = 0; k < OUT.getOutputSize(); ++k)
					{
						if ( strcmp(OUT.getOutputName(k),A.getAndName(j,0)) == 0 )
						{
							OUT.setOutputResult(k,A.getOutput());
						}
					}
				}


				for (int j = 0; j < O.getOrGateSize(); ++j)
				{
					for (int k = 0; k < OUT.getOutputSize(); ++k)
					{
						if ( strcmp(OUT.getOutputName(k),O.getOrName(j,0)) == 0 )
						{
							OUT.setOutputResult(k,O.getOutput());
						}
					}
				}

				for (int j = 0; j < N.getNotGateSize(); ++j)
				{
					for (int k = 0; k < OUT.getOutputSize(); ++k)
					{
						if ( strcmp(OUT.getOutputName(k),N.getNotName(j,0)) == 0 )
						{
							OUT.setOutputResult(k,N.getOutput());
						}
					}
				}

				for (int j = 0; j < F.getFfGateSize(); ++j)
				{
					for (int k = 0; k < OUT.getOutputSize(); ++k)
					{
						if ( strcmp(OUT.getOutputName(k),F.getFfName(j,0)) == 0 )
						{
							OUT.setOutputResult(k,F.getOutput());
						}
					}
				}


				for (int j = 0; j < D.getDecGateSize(); ++j)
				{
					for (int l = 0; l < 4; ++l)
					{
						for (int k = 0; k < OUT.getOutputSize(); ++k)
						{
							if ( strcmp(OUT.getOutputName(k),D.getDecName(j,l)) == 0 )
							{
								if ( l == 0 )
								{
									OUT.setOutputResult(k,D.getDec1());
								}
								else if ( l == 1 )
								{
									OUT.setOutputResult(k,D.getDec2());
								}
								else if ( l == 2 )
								{
									OUT.setOutputResult(k,D.getDec3());
								}
								else if ( l == 3 )
								{
									OUT.setOutputResult(k,D.getDec4());
								}
							}
						}
					}
				}
			}
		}

		for (int i = 0; i < OUT.getOutputSize(); ++i)						/* In here we make a loop to print the results.								*/
		{
			cout << OUT.getOutputResult(i) << " "; 
		}
		cout << endl;

		inputFound = 0;						/* We re-initialize for other inputs.	*/ 
		l = 0;								/* We re-initialize for other inputs.	*/
		p = 0;								/* We re-initialize for other inputs.	*/
		r = 0;								/* We re-initialize for other inputs.	*/
		s = 0;								/* We re-initialize for other inputs.	*/
		m = 0;								/* We re-initialize for other inputs.	*/
	}

	return 0;	/* Ending programme truely.			*/
}