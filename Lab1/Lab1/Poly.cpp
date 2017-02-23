#include "Poly.h"
/********************************************************************/
/*	DR PARSONS, IN CLASS, TOLD US TO IGNORE NEGATIVE EXPONENTS		*/
/*	EVEN THOUGH EXAMPLE OUTPUT SHOWS TO USE ABSOLUTE VALUES, SO IAM	*/
/*	GOING BY WHAT DR PARSONS SAID AND NOT EXAMPLE					*/
/********************************************************************/

/********************************************************************/
/*	Poly(): Default constructor, sets array size to 1. And Poly[0]	*/
/*	Coefficent  to zero. 0^0										*/
/********************************************************************/
Poly::Poly()
{
	//delete[] polyArray;
	polyArray = new int[1]();
	polyArray[0] = 0;
	arraySize = 0;
}

/********************************************************************/
/* Poly(Coeff, Expo): Constructor that creates an array size equal	*/
/*	to the exponent. Checks if expo is negative. If it is sets		*/
/*	Poly[0] equal to zero. 0^0										*/
/********************************************************************/
Poly::Poly(int coefficent, int exponent)
{
	/*	Negative exponent, begin with 0^0 */
	if (exponent < 0)
	{
		//std::cerr << "Negative Coefficent, ignoring";
		polyArray = new int[1]();
		polyArray[0] = 0;
		arraySize = 0;
	}
	else
	{
		arraySize = exponent + 1;
		polyArray = new int[arraySize]();
		polyArray[exponent] = coefficent;
	}
}

/********************************************************************/
/* Poly(coeff): Constructor in which no Exponent is given. Makes	*/
/*	coeff at Poly[0] equal to coefficent input						*/
/********************************************************************/
Poly::Poly(int coefficent)
{
	polyArray = new int[1]();
	arraySize = 1;
	polyArray[0] = coefficent;
}

/********************************************************************/
/*	Poly(Poly): Constructor using a Poly object as input. Makes deep*/
/*	copy of input Poly												*/
/********************************************************************/
Poly::Poly(const Poly& toCopy)
{
	arraySize = toCopy.getArraySize();
	polyArray = new int[arraySize]();

	for (int i = 0; i < arraySize; i++)
	{
		polyArray[i] = toCopy.getCoeff(i);
	}
}

/********************************************************************/
/* ~Poly: deletes the dynamic array on exit using delete[]			*/
/********************************************************************/
Poly::~Poly()
{
	delete[] polyArray;
}

/********************************************************************/
/*	operator+: uses the operator+= logic							*/
/********************************************************************/
Poly Poly::operator+(const Poly & addPoly) const
{
	Poly result = *this;
	result += addPoly;
	return result;
}

/********************************************************************/
/*	operator-: uses the operator-= logic							*/
/********************************************************************/
Poly Poly::operator-(const Poly &subPoly) const
{
	Poly result = *this;
	result -= subPoly;
	return result;
}

/********************************************************************/
/*	operator*: uses the operator*= logic							*/
/********************************************************************/
Poly Poly::operator*(const Poly &mulPoly) const
{
	Poly result = *this;
	result *= mulPoly;
	return result;
}

/********************************************************************/
/*	operator+=: checksArraysize, if smaller than input arraySize,	*/
/*	resizes. Iterates through the polyArray using the input			*/
/*	arraySize, adding along the way									*/
/********************************************************************/
Poly & Poly::operator+=(const Poly &addPoly)
{
	if (addPoly.getArraySize() > arraySize)
	{
		resize(addPoly.getArraySize());
	}

	for (int i = 0; i < addPoly.getArraySize(); i++)
	{
		polyArray[i] += addPoly.getCoeff(i);
	}

	return *this;
}

/********************************************************************/
/*	operator-=:  checks arraySize, if smaller than input Arraysize	*/
/*	resizes. Iterates through arraySize of input and subtracts along*/
/*	the way															*/
/********************************************************************/
Poly & Poly::operator-=(const Poly &subPoly)
{
	if (subPoly.getArraySize() > arraySize)
	{
		resize(subPoly.getArraySize());
	}

	for (int i = 0; i < subPoly.getArraySize(); i++)
	{
		polyArray[i] -= subPoly.getCoeff(i);
	}

	return *this;
}

/********************************************************************/
/*	operator*=: Resizes array to fit largest exponent which is this	*/
/*	arraySize + input arraySize. Then interates through both arrays	*/
/*	Multiplying every coefficent in *this with every coefficent in	*/
/*	input															*/
/********************************************************************/
Poly & Poly::operator*=(const Poly &mulPoly)
{
	/*	Resize to be this.largestExpo + input.largestExpo + 1*/
	resize(arraySize + (mulPoly.getArraySize()-1));

	int *tempArray = new int[arraySize]();
	
	/*	Multiply every nonzero index by every input-nonzero	*/
	for (int i = 0; i < mulPoly.getArraySize(); i++)
	{
		if (mulPoly.getCoeff(i) != 0)
		{
			for (int j = 0; j < arraySize; j++)
			{
				if (polyArray[j] != 0)
				{
					tempArray[i + j] += (polyArray[j] * mulPoly.getCoeff(i));
				}
			}
		}
	}
	delete[] polyArray;
	polyArray = tempArray;
	return *this;
}

/********************************************************************/
/*	operator==: checks if array sizes are equal, if true, iterates	*/
/*	through array, if at any point this and input don't equal, then	*/
/*	returns false													*/
/********************************************************************/
bool Poly::operator==(const Poly &comparePoly) const
{
	/*	Size mismatch, unequal*/
	if (getArraySize() != comparePoly.getArraySize())
	{
		return false;
	}
	else
	{
		for (int i = 0; i < getArraySize(); i++)
		{
			/*	Check every index	*/
			if (getCoeff(i) != comparePoly.getCoeff(i))
			{
				return false;
			}
		}
	}
	return true;
}

/********************************************************************/
/*	operator!=: returns the opposite of whatever operator== is		*/
/********************************************************************/
bool Poly::operator!=(const Poly &compare) const
{
	return !(*this == compare);
}

/********************************************************************/
/*	operator=: Overloaded assignment operator. Checks to see if Poly*/
/*	is being set equal to itself. Otherwise deep copy of array		*/
/********************************************************************/
Poly & Poly::operator=(const Poly &assignPoly)
{
	/*	Assigned to itself, ignore	*/
	if (*this == assignPoly)
	{
		return *this;
	}

	delete[] polyArray;
	arraySize = assignPoly.getArraySize();
	polyArray = new int[arraySize]();

	/*	Deep Copy	*/	
	for (int i = 0; i < arraySize; i++)
	{
		polyArray[i] = assignPoly.getCoeff(i);
	}
	return *this;
}

/********************************************************************/
/*	getCoeff: checks to see if requested exponent is inside array	*/
/*	and returns coefficient if it is.								*/
/********************************************************************/
int Poly::getCoeff(int find) const
{
	/* Check if outside Array Range*/
	if (find < 0 || find > arraySize)
	{
		return 0;
	}
	return polyArray[find];
}

/********************************************************************/
/*	setCoeff: Uses variable expo to determine spot in array to put	*/
/*	coeff, checks to see if expo is outside current array, resizes	*/
/*	accordingly														*/
/********************************************************************/
void Poly::setCoeff(int coeff, int expo)
{
	if (expo < 0)
	{
		//std::cerr << "Negative exponent, no change";
		return;
	}
	/*	Bigger then current biggest exponent */
	if (expo > (arraySize - 1))
	{
		resize(expo+1);
		polyArray[expo] = coeff;
	}
	/*	Within range, set new coefficent	*/
	else
	{
		polyArray[expo] = coeff;
	}
}

/********************************************************************/
/*	getArraySize: simply returns arraySize, which is dynamic arrays	*/
/*	current size.													*/
/********************************************************************/
int Poly::getArraySize() const
{
	return arraySize;
}

/********************************************************************/
/*	Resize: will resize the array according to NewSize, only grows	*/
/*	the array, never shrinks it										*/
/********************************************************************/
void Poly::resize(int newSize)
{
	/* Resize should only grow. Never shink */
	if (newSize < arraySize)
	{
		return;
	}

	int *tempArr;
	tempArr = new int[newSize]();

	for (int i = 0; i < arraySize; i++)
	{
		tempArr[i] = polyArray[i];
	}

	delete[] polyArray;
	polyArray = tempArr;
	arraySize = newSize;
}

/********************************************************************/
/*	operator<<:	Overloaded cout << operator. will look at exponent	*/
/*	and print x or x^ accordinngly									*/	
/********************************************************************/
std::ostream & operator<<(std::ostream &output, Poly &polyIn)
{
	/*	Empty Array, output 0	*/
	if (polyIn.getArraySize() == 0)
	{
		output << 0;
	}
	else
	{
		for (int i = polyIn.getArraySize()-1; i >= 0; i--)
		{
			/* Positive Coefficent	*/
			if (polyIn.getCoeff(i) > 0)
			{
				output << '+';
			}
			if (polyIn.getCoeff(i) != 0)
			{
				/* Poly[2+] - X^Y	*/
				if (i > 1)
				{
					output << polyIn.getCoeff(i) << "x^" << i;
				}
				else
				{
					/* Poly[1] - or X^1 */
					if (i == 1)
					{
						output << polyIn.getCoeff(i) << 'x';
					}
					/* Poly[0] - integer, no X variable */
					if (i == 0)
					{
						output << polyIn.getCoeff(i);
					}
				}

			}
		}
	}
	return output;
}

/********************************************************************/
/*	operator>>: Overloaded cin >>  operator that will loop until	*/ 
/*	-1, -1 is given as input													*/
/********************************************************************/
std::istream & operator>>(std::istream &input, Poly &polyIn)
{
	int tempCoeff;
	int tempExpo;
	
	while (true)
	{
		input >> tempCoeff >> tempExpo;
		if ((tempCoeff == -1) && (tempExpo == -1))
		{
			break;
		}
		
		polyIn.setCoeff(tempCoeff, tempExpo);
	}
	return input;
}