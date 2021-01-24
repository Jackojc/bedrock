#include <cstdio>

#include "bedrock.hpp"

int main() {
	std::printf("sizeof(u8) = %ld\n", sizeof(br::u8));
	std::printf("sizeof(i8) = %ld\n", sizeof(br::i8));

	std::printf("sizeof(u16) = %ld\n", sizeof(br::u16));
	std::printf("sizeof(i16) = %ld\n", sizeof(br::i16));

	std::printf("sizeof(u32) = %ld\n", sizeof(br::u32));
	std::printf("sizeof(i32) = %ld\n", sizeof(br::i32));

	std::printf("sizeof(u64) = %ld\n", sizeof(br::u64));
	std::printf("sizeof(i64) = %ld\n", sizeof(br::i64));

	std::printf("sizeof(f32) = %ld\n", sizeof(br::f32));
	std::printf("sizeof(f64) = %ld\n", sizeof(br::f64));
	std::printf("sizeof(f128) = %ld\n", sizeof(br::f128));

	return 0;
}
