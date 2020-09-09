// #include <iostream>

#include <file.hpp>
#include <io.hpp>
#include <memory.hpp>
#include <pool.hpp>
#include <result.hpp>
#include <slice.hpp>
#include <string.hpp>
#include <types.hpp>
#include <util.hpp>
#include <vector.hpp>
#include <array.hpp>
#include <clock.hpp>
#include <limits.hpp>
#include <assert.hpp>
#include <static_vector.hpp>
#include <alias.hpp>
#include <args.hpp>
#include <char.hpp>
#include <def.hpp>
#include <pred.hpp>
#include <rand.hpp>
#include <traits.hpp>
#include <exit.hpp>

#include <ctime>


// struct ArenaAllocator: br::Allocator<ArenaAllocator> {
// 	void release(void*) {

// 	}

// 	void* allocate(br::size_t , br::size_t ) {
// 		return nullptr;
// 	}
// };



int main() {
	// Allocators.
	// ArenaAllocator mem;
	// br::allocate<int>(mem, 10);
	// br::Pool p;


	// Random.
	br::Random rng = br::random_create(time(nullptr));

	for (int i = 0; i < 20; i++)
		std::printf("%llu ", br::random_range(rng, 0, 100));
	std::puts("\n");


	// Array.
	auto arr = br::arr_create(1, 2, 3);

	std::printf("arr size = %llu\n", br::size(arr));

	for (auto it = br::begin(arr); it != br::end(arr); br::next(it))
		std::printf("%d\n", *it);

	for (br::index_t i = 0; i != br::size(arr); ++i)
		std::printf("%d\n", br::at(arr, i));

	// br::print("hey");


	// BR_ASSERT(1 == 2, "wtf");

	return 0;
}
