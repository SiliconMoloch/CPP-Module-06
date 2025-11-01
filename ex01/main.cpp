#include "Serializer.hpp"
#include <iostream>
#include <cstring>

int					main(int argc, char* const argv[]);
static void			print_(Data* data);
static std::string	matching_ptrs(uintptr_t const serialized, 
					Data* const deserialized);

int	main(int argc, char* const argv[])

{
	int		i;
	Data*	data;

	i = 0;
	while (++i < argc)
	{
		data = new (std::nothrow) Data;
		if (!data)
			return (1);
		data->index = i;
		data->arg = new (std::nothrow) char[std::strlen(argv[i]) + 1];
		if (!data->arg)
		{
			delete (data);
			return (1);
		}
		std::strcpy(data->arg, argv[i]);
		print_(data);
		delete [](data->arg);
		delete (data);
	}
	if (i ^ 1)
		return (0);
	std::cout << "./Serialization <data> ..." << std::endl;
	return (1);
}

static void	print_(Data* data)

{
	std::cout << '\n';
	std::cout << data->index << ". " << data->arg << std::endl;

	uintptr_t const	serialized = Serializer::serialize(data);
	Data* const		deserialized = Serializer::deserialize(serialized);
	std::cout << "serialize " << serialized << std::endl;
	std::cout << "deserialize " << deserialized << std::endl;
	std::cout << "Do pointers match?" << matching_ptrs(serialized, data) << std::endl;
	std::cout << "_____" << std::endl;
}

#include <sstream>

static std::string	matching_ptrs(uintptr_t const serialized, 
	Data* const deserialized)

{
	std::stringstream	serialized_into_stream;
	serialized_into_stream << "0x" << std::hex << serialized;
	std::string const	serialized_string = serialized_into_stream.str();

	std::stringstream	deserialized_into_stream;
	deserialized_into_stream << deserialized;
	std::string const	deserialized_string = deserialized_into_stream.str();

	if (deserialized_string == serialized_string)
		return (" yes");
	return (" no");
}
