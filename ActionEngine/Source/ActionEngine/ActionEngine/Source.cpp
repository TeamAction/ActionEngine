#include <iostream>
#include "Initialize.h"

int main()
{

	
	Initialize::IsOnlyInstance("MyGame");
	while (true)
	{
		std::cout << "Hello World" << std::endl;
	}

	return (0);
}
 