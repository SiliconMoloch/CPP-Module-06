#include "ScalarConverter.hpp"
#include <cstdlib>
#include <cmath>
#define INT_MIN -2147483648
#define INT_MAX	2147483647

void	ScalarConverter::convert(std::string literal)

{
	if (literal.empty())
		return ;
	if (literal == "-inff" || literal == "+inff" || literal == "nanf" ||
        literal == "-inf" || literal == "+inf" || literal == "nan")
	{
		handleSpecialValues(literal);
		return ;
	}
	try
	{
		switch (detectType(literal))
		{
			case (CHAR):
				convertChar(literal[0]);
				break ;
			case (INT):
			{
				char		*end;
				long const	l = strtol(literal.c_str(), &end, 10);
				if (*end ^ '\0' || l < INT_MIN || l > INT_MAX)
					throw (std::exception());
				convertInt(static_cast<int>(l));
				break ;
			}
			case (FLOAT):
			{
				std::string const	withoutF = \
				(literal[literal.length()] - 1 ^ 'f') ?
				literal.substr(0, literal.length() - 1) : literal;
				char				*end;
				double const		d = strtod(withoutF.c_str(), &end);
				if (*end ^ '\0')
					throw (std::exception());
				convertFloat(static_cast<float>(d));
				break ;
			}
			case (DOUBLE):
				break ;
			case (INVALID):
				std::cout << "char: impossible" << std::endl;
				std::cout << "int: impossible" << std::endl;
				std::cout << "float: " << literal << "f" << std::endl;
				std::cout << "double: " << literal << std::endl;
				break ;
		}
		return ;
	}
	catch (...)
	{
		std::cout << "conversion failed" << std::endl;
	}
}

ScalarConverter::Type	ScalarConverter::detectType(const std::string& literal)

{
	if (literal.length() == 1 && !isdigit(literal[0]))
		return (CHAR);
	
	char	*end;
	if (literal[literal.length() - 1] == 'f')
	{
		std::string const	withoutF = literal.substr(0, literal.length() - 1);
		strtod(withoutF.c_str(), &end);
		if (!*end)
			return (FLOAT);
	}
	if (literal.find('.') == std::string::npos 
		&& literal.find('f') == std::string::npos)
	{
		long const	l = strtol(literal.c_str(), &end, 10);
		if (!*end && l >= INT_MIN && l <= INT_MAX)
			return (INT);
	}
	strtod(literal.c_str(), &end);
	if (!*end)
		return (DOUBLE);
	return (INVALID);
}

void	ScalarConverter::convertChar(char const c)

{
	std::cout << "char: '" << c << '\'' << std::endl;
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << static_cast<float>(c) << ".0f" <<  std::endl;
	std::cout << "float: " << static_cast<double>(c) << ".0" <<  std::endl;
}

void	ScalarConverter::convertInt(int const i)

{
	if (i < 0 || i > 127)
		std::cout << "char: impossible" << std::endl;
	else if (i < 32 || i > 126)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(i) << "'" << std::endl;
	std::cout << "int: " << i << std::endl;
	std::cout << "float: " << static_cast<float>(i) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(i) << ".0" << std::endl;
}

void	ScalarConverter::convertFloat(float const f)

{
	if (std::isnan(f) || std::isinf(f) || f < 0 || f > 127)
		std::cout << "char: impossible" << std::endl;
	else if (f < 32 || f > 126)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;

	if (std::isnan(f) || std::isinf(f) || f < INT_MIN /*|| f > INT_MAX*/)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(f) << std::endl;

	if (f == static_cast<int>(f))
		std::cout << "float: " << f << ".0f" << std::endl;
	else
		std::cout << "float: " << f << 'f' << std::endl;
}

void	ScalarConverter::handleSpecialValues(const std::string& literal)

{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	if (literal == "-inff" || literal == "+inff" || literal == "nanf")
	{
		std::cout << "float: " << literal << std::endl;
		std::cout << "double: " << 
			literal.substr(0, literal.length() - 1) << std::endl;
	}
	else
	{
		std::cout << "float: " << literal << "f" << std::endl;
		std::cout << "double: " << literal << std::endl;
	}
}



























ScalarConverter::ScalarConverter(void)

{

}

ScalarConverter::ScalarConverter(ScalarConverter const& copy)

{
	*this = copy;
}

ScalarConverter&	ScalarConverter::operator=(ScalarConverter const& to_assign)

{
	(void)to_assign;
	return (*this);
}

ScalarConverter::~ScalarConverter(void)

{

}
