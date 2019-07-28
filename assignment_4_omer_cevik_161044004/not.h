#ifndef NOT_H
#define NOT_H

class Not : public gates 		/* We create NOT gates.			*/
{
public:
	Not();
	const char* getNotName(int indGate, int ind1) const { return NotName[indGate][ind1]; }
	const char getNotName(int indGate, int ind1, int ind2) const { return NotName[indGate][ind1][ind2]; }
	const char setNotName(int indGate, int ind1, int ind2, char data) { NotName[indGate][ind1][ind2] = data; return NotName[indGate][ind1][ind2]; }
	const int getNotGateSize() const { return NotGateSize; }
	~Not();
	virtual void evaluate(int inp1, int inp2) override;

private:
	char*** NotName = NULL;
	int NotGateSize = 0;
};

#endif