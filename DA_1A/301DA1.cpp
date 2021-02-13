#include <iostream>
#include <cmath>

using namespace std;

int main(){
	int quotient = 0;
	int divisor = 10000;
	int dividend = 75;
	int remainder = 0;
	
	quotient = divisor / dividend;
	remainder = divisor % dividend;
	
	cout << "10,000 / 75 = " ;
	cout << quotient ;
	cout << " with a remainder of ";
	cout << remainder << endl;
	
	return 0;
}