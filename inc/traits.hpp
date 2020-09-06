#ifndef BEDROCK_TRAITS_HPP
#define BEDROCK_TRAITS_HPP

// Common trait utilities.

#include "types.hpp"

namespace br {
	namespace detail {
		// https://en.cppreference.com/w/cpp/types/integral_constant
		template <class T, T v>
		struct integral_constant {
			static constexpr T value = v;
			using value_type = T;
		};

		using true_type = integral_constant<bool, true>;
		using false_type = integral_constant<bool, false>;


		// See http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4502.pdf.
		template <typename...>
		using void_t = void;


		template <class Default, class AlwaysVoid,
		          template<class...> class Op, class... Args>
		struct detector {
		  using value_t = false_type;
		  using type = Default;
		};

		template <class Default, template<class...> class Op, class... Args>
		struct detector<Default, void_t<Op<Args...>>, Op, Args...> {
		  using value_t = true_type;
		  using type = Op<Args...>;
		};

		struct nonesuch {
		    nonesuch() = delete;
		    ~nonesuch() = delete;
		    nonesuch(nonesuch const&) = delete;
		    void operator=(nonesuch const&) = delete;
		};

		template <template<class...> class Op, class... Args>
		using is_detected = typename detector<nonesuch, void, Op, Args...>::value_t;

		template <template<class...> class Op, class... Args>
		using detected_t = typename detector<nonesuch, void, Op, Args...>::type;

		template <class Default, template<class...> class Op, class... Args>
		using detected_or = detector<Default, void, Op, Args...>;


		template <typename T>
		struct type_identity { using type = T; };

		template <typename T>
		auto try_add_rvalue_reference(int) -> type_identity<T&&>;

		template <typename T>
		auto try_add_rvalue_reference(...) -> type_identity<T>;

		template <typename T>
		struct add_rvalue_reference: decltype(try_add_rvalue_reference<T>(0)) {};


		template <typename T>
		typename add_rvalue_reference<T>::type declval();
	}



	// Allocator trait.
	namespace detail {
		template <typename T>
		using allocate_t = decltype(declval<T>().allocate(declval<br::size_t>(), declval<br::size_t>()));

		template <typename T>
		using release_t = decltype(declval<T>().release(declval<void*>()));


		template <typename T> using has_allocate = is_detected<allocate_t, T>;
		template <typename T> using has_release = is_detected<release_t, T>;
	}

	#define ASSERT_HAS_ALLOCATE() \
		do { static_assert(detail::has_allocate<T>::value, "T does not implement allocate."); } while (0)

	#define ASSERT_HAS_RELEASE() \
		do { static_assert(detail::has_release<T>::value, "T does not implement release."); } while (0)

	template <typename T>
	struct Allocator {
		Allocator() {
			ASSERT_HAS_ALLOCATE();
			ASSERT_HAS_RELEASE();
		}

		auto allocate_(br::size_t sz, br::size_t n) {
			return static_cast<T*>(this)->allocate(sz, n);
		}

		auto release_(void* ptr) {
			return static_cast<T*>(this)->release(ptr);
		}
	};

	namespace detail {
		template <typename T>
		auto is_allocator_impl(Allocator<T> const&) -> true_type;
		auto is_allocator_impl(...) -> false_type;

	}

	template <typename T>
	using is_allocator = decltype(detail::is_allocator_impl(detail::declval<T>()));

	template <typename X, typename T>
	auto allocate(Allocator<T>& alloc, br::size_t n) {
		static_assert(is_allocator<T>::value, "T is not an Allocator.");
		ASSERT_HAS_ALLOCATE();
		return alloc.allocate_(sizeof(X), n);
	}

	template <typename X, typename T>
	auto release(Allocator<T>& alloc, X* ptr) {
		static_assert(is_allocator<T>::value, "T is not an Allocator.");
		ASSERT_HAS_RELEASE();
		return alloc.release_(static_cast<void*>(ptr));
	}

	#undef ASSERT_HAS_ALLOCATE
	#undef ASSERT_HAS_RELEASE




	// Iterator trait.
	namespace detail {
		template <typename T> using advance_t = decltype(declval<T>().advance());
		template <typename T> using reverse_t = decltype(declval<T>().reverse());

		template <typename T> using has_advance = is_detected<reverse_t, T>;
		template <typename T> using has_reverse = is_detected<advance_t, T>;
	}

	#define ASSERT_HAS_ADVANCE() \
		do { static_assert(detail::has_advance<T>::value, "T does not implement advance."); } while (0)

	#define ASSERT_HAS_REVERSE() \
		do { static_assert(detail::has_reverse<T>::value, "T does not implement reverse."); } while (0)

	template <typename T>
	struct BiDirectionalIterator {
		BiDirectionalIterator() {
			ASSERT_HAS_ADVANCE();
			ASSERT_HAS_REVERSE();
		}

		auto advance_() {
			return static_cast<T*>(this)->advance();
		}

		auto reverse_() {
			return static_cast<T*>(this)->reverse();
		}
	};

	template <typename T>
	struct ForwardIterator {
		ForwardIterator() {
			static_assert(detail::has_advance<T>::value, "T does not implement advance.");
		}

		auto advance_() {
			ASSERT_HAS_ADVANCE();
			return static_cast<T*>(this)->advance();
		}

		auto reverse_() {
			ASSERT_HAS_REVERSE();
			return static_cast<T*>(this)->reverse();
		}
	};

	namespace detail {
		template <typename T>
		auto is_bidirectional_iterator_impl(BiDirectionalIterator<T> const&) -> true_type;
		auto is_bidirectional_iterator_impl(...) -> false_type;

		template <typename T>
		auto is_forward_iterator_impl(ForwardIterator<T> const&) -> true_type;
		auto is_forward_iterator_impl(...) -> false_type;
	}

	template <typename T>
	using is_bidirectional_iterator = decltype(detail::is_bidirectional_iterator_impl(detail::declval<T>()));

	template <typename T>
	using is_forward_iterator = decltype(detail::is_forward_iterator_impl(detail::declval<T>()));

	// BiDirectionalIterator.
	template <typename T>
	auto advance(BiDirectionalIterator<T>& it) {
		static_assert(is_bidirectional_iterator<T>::value, "T is not a BiDirectionalIterator.");
		ASSERT_HAS_ADVANCE();
		return it.advance_();
	}

	template <typename T>
	auto reverse(BiDirectionalIterator<T>& it) {
		static_assert(is_bidirectional_iterator<T>::value, "T is not a BiDirectionalIterator.");
		ASSERT_HAS_REVERSE();
		return it.reverse_();
	}

	// ForwardIterator.
	template <typename T>
	auto advance(ForwardIterator<T>& it) {
		static_assert(is_forward_iterator<T>::value, "T is not a ForwardIterator.");
		ASSERT_HAS_ADVANCE();
		return it.advance_();
	}

	template <typename T>
	auto reverse(ForwardIterator<T>& it) {
		static_assert(is_forward_iterator<T>::value, "T is not a ForwardIterator.");
		ASSERT_HAS_REVERSE();
		return it.reverse_();
	}

	#undef ASSERT_HAS_ADVANCE
	#undef ASSERT_HAS_REVERSE



	// Container trait.
	namespace detail {
		template <typename T> using start_t = decltype(declval<T>().start());
		template <typename T> using end_t = decltype(declval<T>().end());

		template <typename T> using has_start = is_detected<start_t, T>;
		template <typename T> using has_end = is_detected<end_t, T>;
	}

	#define ASSERT_HAS_BEGIN() \
		do { static_assert(detail::has_start<T>::value, "T does not implement start."); } while (0)

	#define ASSERT_HAS_END() \
		do { static_assert(detail::has_end<T>::value, "T does not implement end."); } while (0)

	template <typename T>
	struct Container {
		Container() {
			ASSERT_HAS_BEGIN();
			ASSERT_HAS_END();
		}

		auto start_() {
			return static_cast<T*>(this)->start();
		}

		auto end_() {
			return static_cast<T*>(this)->end();
		}
	};

	namespace detail {
		template <typename T>
		auto is_container_impl(Container<T> const&) -> true_type;
		auto is_container_impl(...) -> false_type;
	}

	template <typename T>
	using is_container = decltype(detail::is_container_impl(detail::declval<T>()));

	template <typename T> auto start(Container<T>& c) {
		static_assert(is_container<T>::value, "T is not a Container.");
		ASSERT_HAS_BEGIN();
		return c.start_();
	}

	template <typename T> auto end(Container<T>& c) {
		static_assert(is_container<T>::value, "T is not a Container.");
		ASSERT_HAS_END();
		return c.end_();
	}

	#undef ASSERT_HAS_BEGIN
	#undef ASSERT_HAS_END
}

#endif
