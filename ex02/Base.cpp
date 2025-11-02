#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <stdint.h>

Base*			generate(void);
static uint8_t	whichConcreteClass(void);

Base*	generate(void)

{
	enum Type {AType = 0, BType = 1, CType = 2};

	switch (whichConcreteClass())
	{
		case (AType):
			std::cout << "A was drawn and instantiated." << std::endl;;
			return (new (std::nothrow) A());
		case (BType):
			std::cout << "B was drawn and instantiated." << std::endl;
			return (new (std::nothrow) B());
		case (CType):
			std::cout << "C was drawn and instantiated." << std::endl;
			return (new (std::nothrow) C());
		default:
			return (NULL);
	}
}

#include <cstdlib>

static uint8_t	whichConcreteClass(void)

{
	srand((uint32_t)time(NULL));
	return (rand() % 3);
}

void	identify(Base* p)

{
	if (dynamic_cast<A*>(p) != NULL)
		std::cout << 'A' << std::endl;
	else if (dynamic_cast<B*>(p) != NULL)
		std::cout << 'B' << std::endl;
	else if (dynamic_cast<C*>(p) != NULL)
		std::cout << 'C' << std::endl;
}

void	identify(Base& p)

{
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << 'A' << std::endl;
		return ;
	}
	catch (std::exception& e) {}

	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << 'B' << std::endl;
		return ;
	}
	catch (std::exception& e) {}

	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << 'C' << std::endl;
		return ;
	}
	catch (std::exception& e) {}
}

Base::~Base(void) {}
