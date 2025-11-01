#include "ScalarConverter.hpp"

int	main(int argc, const char* argv[])

{
	int	i;

	i  = 0;
	while (++i < argc)
	{
		if (i < 2)
			std::cout << '\n';
		ScalarConverter::convert(argv[i]);
		if (i ^ argc - 1)
			std::cout << "___\n" << std::endl;
	}
	if (i ^ 1)
	{
		std::cout << '\n';
		return (0);
	}
	std::cout << "./Conversion_of_scalar_types <literal> ..." << std::endl;
	return (1);
}
