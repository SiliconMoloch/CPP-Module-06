#include "Base.hpp"
#include <iostream>
#include <stdint.h>

Base*			generate(void);
static uint8_t	whichConcreteClass(void);

Base*	generate(void)

{
	std::cout << (int)whichConcreteClass();
	//switch (whichConcreteClass())
	return (NULL);
}

#include <cstdlib>
#include <ctime>

static uint8_t	whichConcreteClass(void)

{
	srand((unsigned)time(NULL));
	return (rand() % 3);
}
