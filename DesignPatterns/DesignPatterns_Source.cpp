
#include <iostream>
#include "SingleResponsibility.h"
#include "OpenClosed.h"
#include "LiskovSubstitution.h"

int main()
{
	/* ---------- SOLID Patterns ----------- */
	/* Single Responsibility Principle*/
	SingleResponsibility singleResponsibility; 
	singleResponsibility.run(); 
	std::cout << std::endl; 

	/* Open-Closed Principle */
	OpenClosed openClosed; 
	openClosed.run(); 
	std::cout << std::endl; 

	/* Liskov Substitution Principle */
	LiskovSubstitution liskovSubstition; 
	liskovSubstition.run(); 
	std::cout << std::endl; 
	/* Interface Segregation Principle */

	/* Dependency Inversion Principle */

}