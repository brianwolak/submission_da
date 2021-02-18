#include <iostream>
#include <cmath>

using namespace std;

int main(){
	int oddSUM = 0;
	int evenSUM = 0;
	
	for (int i = 33; i<146; i++){
		if (i%2 ==0)
			oddSUM=oddSUM + i;
		else
			evenSUM = evenSUM + i;
	}
	cout << "Adding the 112 ODD and EVEN numbers between 33 and 145" << endl;
	cout << "ODD sum =" ;
	cout << oddSUM << endl;
	cout << "EVEN sum = ";
	cout << evenSUM << endl;
	
	return 0;
}