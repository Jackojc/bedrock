#ifndef BEDROCK_FORWARD_HPP
#define BEDROCK_FORWARD_HPP

// ...

namespace br {
	template <typename T>
	struct identity {
		typedef T type;
	};


	template <typename T>
	T&& forward(typename identity<T>::type&& param) {
		return static_cast<typename identity<T>::type&&>(param);
	}
}

#endif



