#include "Serializer.hpp"
#include <iostream>

int					main(int argc, char* const argv[]);
static void			print_(Data data);
static std::string	matching_ptrs(
	Data* const original_data, Data* const deserialized);

int	main(int argc, char* const argv[])

{
	int		i;
	Data	data;

	i = 0;
	while (++i < argc)
	{
		data.index = i;
		data.arg = argv[i]; 
		print_(data);
	}
	if (i ^ 1)
		return (0);
	std::cout << "./Serialization <data> ..." << std::endl;
	return (1);
}

static void	print_(Data data)

{
	std::cout << '\n';
	std::cout << data.index << ". " << data.arg << std::endl;

	uintptr_t const	serialized = Serializer::serialize(&data);
	Data* const		deserialized = Serializer::deserialize(serialized);
	std::cout << "serialize " << serialized << std::endl;
	std::cout << "deserialize " << deserialized << std::endl;
	std::cout << 
	"Do pointers match?" << matching_ptrs(deserialized, &data) << std::endl;
	std::cout << "_____" << std::endl;
}

static std::string	matching_ptrs(
	Data* const original_data, Data* const deserialized)

{
	return ((original_data == deserialized) ? " yes" : " no");
}
