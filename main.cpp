#include <iostream>
#include "lib/max6675.h"

#define CS 25
#define SCK 24
#define SO 23

int main() {
	MAX6675 m;
	m.begin(CS, SO, SCK);
	
	std::cout << m.convertToCelsius() << std::endl;
	return 0;
}