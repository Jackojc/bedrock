#include <iostream>

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


int main() {
	br::Random rng = br::random_create(2382274);

	for (int i = 0; i < 5; i++) {
		std::cout << br::random_range(rng, 0, 5) << '\n';
	}

	return 0;
}
