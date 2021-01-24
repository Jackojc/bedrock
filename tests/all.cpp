// #include <iostream>

#include <file.hpp>
#include <io.hpp>
#include <memory.hpp>
#include <allocator.hpp>
#include <result.hpp>
#include <string.hpp>
#include <type.hpp>
#include <util.hpp>
#include <vector.hpp>
#include <array.hpp>
#include <clock.hpp>
#include <limit.hpp>
#include <assert.hpp>
#include <static_vector.hpp>
#include <alias.hpp>
#include <arg.hpp>
#include <char.hpp>
#include <def.hpp>
#include <pred.hpp>
#include <rand.hpp>
#include <trait.hpp>
#include <exit.hpp>

#include <ctime>


int main() {
	// Allocators.
	br::Pool p = br::pool_create(sizeof(int) * 10);

	int* a = br::allocate<int>(p);
	int* b = br::allocate<int>(p);
	int* c = br::allocate<int>(p);

	*c = 1;
	*b = 2;
	*a = 3;

	std::printf("%p = %d\n", (void*)a, *a);
	std::printf("%p = %d\n", (void*)b, *b);
	std::printf("%p = %d\n", (void*)c, *c);


	// Random.
	br::Random rng = br::random_create(time(nullptr));

	for (int i = 0; i < 20; i++)
		std::printf("%llu ", br::random_range(rng, 0, 100));
	std::puts("\n");


	// Array.
	auto arr = br::arr_create(1, 2, 3);

	std::printf("arr size = %llu\n", br::size(arr));

	auto [begin, end] = br::range(arr);

	for (auto it = begin; it != end; ++it)
		std::printf("%d ", *it);
	std::puts("");


	auto arr2 = br::arr_create<int, 10>();
	br::fill(arr2, 2);


	for (auto x: arr2)
		std::printf("%d ", x);
	std::puts("");



	// String
	auto str = br::str_create(p, "hello π!");

	std::printf("size  = %llu\n", br::size(str));
	std::printf("bytes = %llu\n", br::bytes(str));




	// BR_ASSERT(1 == 2, "wtf");

	br::str_destroy(p, str);
	br::pool_destroy(p);

	return 0;
}
