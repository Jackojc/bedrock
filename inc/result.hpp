#ifndef BEDROCK_RESULT_HPP
#define BEDROCK_RESULT_HPP

// ...

namespace br {
	struct GenericError {};

	template <typename T, typename E = GenericError>
	struct Result {
		bool has_err;

		union {
			T value;
			E error;
		};
	};


	template <typename T, typename E>
	constexpr bool result_has_error(const Result<T, E>& r) {
		return r.has_err;
	}

	// todo:
	// - value_or
	// - has_value
	// -
}

#endif

