#include <iostream>
using namespace std;
class Poly
{

	friend std::ostream& operator<<(std::ostream&, Poly&);
	friend std::istream& operator>>(std::istream&, Poly&);
public:
	Poly();
	Poly(int, int);
	Poly(int);
	Poly(const Poly&);
	~Poly();

	Poly operator+(const Poly&) const;
	Poly operator-(const Poly&) const;
	Poly operator*(const Poly&) const;

	Poly& operator+=(const Poly&);
	Poly& operator-=(const Poly&);
	Poly& operator*=(const Poly&);

	bool operator==(const Poly&) const;
	bool operator!=(const Poly&) const;

	Poly& operator=(const Poly&);

	int getCoeff(int) const;
	void setCoeff(int, int);
	
	int getArraySize() const;

private:
	void resize(int);

	int arraySize;
	int *polyArray;
};

