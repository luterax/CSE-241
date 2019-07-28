#ifndef AND_H
#define AND_H

class And : public gates 		/* We create AND gates.		*/
{
public:
	And();
	const char* getAndName(int indGate, int ind1) const { return AndName[indGate][ind1]; }
	const char getAndName(int indGate, int ind1, int ind2) const { return AndName[indGate][ind1][ind2]; }
	const char setAndName(int indGate, int ind1, int ind2, char data) { AndName[indGate][ind1][ind2] = data; return AndName[indGate][ind1][ind2]; }
	const int getAndGateSize() const { return AndGateSize; }
	~And();
	virtual void evaluate(int inp1, int inp2) override;

private:
	char*** AndName = NULL;
	int AndGateSize = 0;
};

#endif