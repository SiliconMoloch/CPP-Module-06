#include "Base.hpp"

int	main(void)

{
	Base* const	p = generate();

	if (!p)
		return (1);
	identify(p);
	identify(*p);
	delete (p);
}
