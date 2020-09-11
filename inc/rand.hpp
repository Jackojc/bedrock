#pragma once
#ifndef BEDROCK_RAND_HPP
#define BEDROCK_RAND_HPP

// Random number generation.

// Sources:
// http://prng.di.unimi.it/xoshiro256plusplus.c
// http://prng.di.unimi.it/
// https://en.wikipedia.org/wiki/Xorshift#xoshiro_and_xoroshiro
// http://www.adammil.net/blog/v134_Efficiently_generating_random_numbers_without_bias.html
// https://www.pcg-random.org/posts/bounded-rands.html
// https://github.com/imneme/bounded-rands/blob/master/bounded64.cpp#L213

#include "type.hpp"

namespace br {
	namespace detail {
		inline br::u64 splitmix64(br::u64 seed) {
			seed = (seed ^ (seed >> 30)) * 0xBF58476D1CE4E5B9;
			seed = (seed ^ (seed >> 27)) * 0x94D049BB133111EB;
			return seed ^ (seed >> 31);
		}


		inline br::u64 rotl(br::u64 x, br::i32 k) {
			return (x << k) | (x >> (64 - k));
		}
	}


	struct Random {
		br::u64 state[4];
	};


	br::Random random_create(br::u64 seed) {
		br::Random state;

		seed = detail::splitmix64(seed);
		state.state[0] = seed;

		seed = detail::splitmix64(seed);
		state.state[1] = seed;

		seed = detail::splitmix64(seed);
		state.state[2] = seed;

		seed = detail::splitmix64(seed);
		state.state[3] = seed;

		return state;
	}


	br::u64 random_next(br::Random& rng) {
		auto& s = rng.state;

		const br::u64 result = detail::rotl(s[0] + s[3], 23) + s[0];
		const br::u64 t = s[1] << 17;

		s[2] ^= s[0];
		s[3] ^= s[1];
		s[1] ^= s[2];
		s[0] ^= s[3];

		s[2] ^= t;
		s[3] = detail::rotl(s[3], 45);

		return result;
	}


	br::u64 random_range(Random& rng, br::u64 min, br::u64 max) {
		br::u64 range = max - min + 1;
		br::u64 x, r;

		do {
			x = br::random_next(rng);
			r = x;

			if (r >= range) {
				r -= range;

				if (r >= range)
					r %= range;
			}

		} while (x - r > -range);

		return r + min;
	}
}

#endif
