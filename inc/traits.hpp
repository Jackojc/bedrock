#pragma once
#ifndef BEDROCK_TRAITS_HPP
#define BEDROCK_TRAITS_HPP

// Common trait utilities.

#include "types.hpp"

namespace br {
	// Core trait helpers.
	namespace detail {
		// https://en.cppreference.com/w/cpp/types/integral_constant
		// Integral constants and true/false types.
		template <class T, T v>
		struct integral_constant {
			static constexpr T value = v;
			using value_type = T;
		};

		using true_type = integral_constant<bool, true>;
		using false_type = integral_constant<bool, false>;


		// is_same and is_same_v, compare two Ts.
		template <typename T, typename U>
		struct is_same: false_type {};

		template <typename T>
		struct is_same<T, T>: true_type {};

		template <typename T, typename U>
		inline constexpr bool is_same_v = is_same<T, U>::value;


		// See http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4502.pdf.
		template <typename...>
		using void_t = void;


		template <class Default, class AlwaysVoid, template<class...> class Op, class... Args>
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




		// Add rvalue ref to T.
		template <typename T>
		struct type_identity { using type = T; };

		template <typename T>
		auto try_add_rvalue_reference(int) -> type_identity<T&&>;

		template <typename T>
		auto try_add_rvalue_reference(...) -> type_identity<T>;

		template <typename T>
		struct add_rvalue_reference: decltype(try_add_rvalue_reference<T>(0)) {};


		// declval
		template <typename T>
		typename add_rvalue_reference<T>::type declval();
	}


	// Assert that all Ts are the same type.
	template <typename T, typename... Ts> constexpr void ensure_variadic_parity() {
		static_assert((detail::is_same_v<T, Ts> and ...), "Arguments are of differing types.");
	}





	// Allocator trait.
	namespace detail {
		// Check for functionality implemented by T. Poor man's concepts.
		template <typename T>
		using allocate_t = decltype(declval<T>().allocate(declval<br::size_t>(), declval<br::size_t>()));

		template <typename T>
		using release_t = decltype(declval<T>().release(declval<void*>()));


		template <typename T> using has_allocate = is_detected<allocate_t, T>;
		template <typename T> using has_release = is_detected<release_t, T>;
	}


	// Allocator trait.
	template <typename T>
	struct Allocator {
		Allocator() {
			static_assert(detail::has_allocate<T>::value, "T does not implement allocate.");
			static_assert(detail::has_release<T>::value, "T does not implement release.");
		}

		constexpr auto allocate_(br::size_t sz, br::size_t n) {
			return static_cast<T*>(this)->allocate(sz, n);
		}

		constexpr auto release_(void* ptr) {
			return static_cast<T*>(this)->release(ptr);
		}
	};



	// Check if a T is an allocator.
	namespace detail {
		template <typename T>
		auto is_allocator_impl(Allocator<T> const&) -> true_type;
		auto is_allocator_impl(...) -> false_type;
	}

	template <typename T>
	using is_allocator = decltype(detail::is_allocator_impl(detail::declval<T>()));

	template <typename T> constexpr bool is_allocator_v = is_allocator<T>::value;



	// Free function helpers.
	template <typename X, typename T>
	auto allocate(Allocator<T>& alloc, br::size_t n) {
		static_assert(is_allocator<T>::value, "T is not an Allocator.");
		static_assert(detail::has_allocate<T>::value, "T does not implement allocate.");

		return static_cast<X*>(alloc.allocate_(sizeof(X), n));
	}

	template <typename X, typename T>
	auto release(Allocator<T>& alloc, X* ptr) {
		static_assert(is_allocator<T>::value, "T is not an Allocator.");
		static_assert(detail::has_release<T>::value, "T does not implement release.");

		return alloc.release_(static_cast<void*>(ptr));
	}




	// Iterator trait.
	namespace detail {
		// Poor man's concepts.
		template <typename T> using next_t = decltype(declval<T>().next());
		template <typename T> using prev_t = decltype(declval<T>().prev());

		template <typename T> using cmp_eq_t = decltype(declval<T>() == declval<T>());
		template <typename T> using cmp_not_eq_t = decltype(declval<T>() != declval<T>());

		template <typename T> using deref_t = decltype(*declval<T>());


		template <typename T> using has_next = is_detected<prev_t, T>;
		template <typename T> using has_prev = is_detected<next_t, T>;

		template <typename T> using has_cmp_eq = is_detected<cmp_eq_t, T>;
		template <typename T> using has_cmp_not_eq = is_detected<cmp_not_eq_t, T>;

		template <typename T> using has_deref = is_detected<deref_t, T>;
	}


	// Bi-Directional Iterator trait.
	template <typename T>
	struct BiDirectionalIterator {
		BiDirectionalIterator() {
			static_assert(detail::has_next<T>::value, "T does not implement next.");
			static_assert(detail::has_prev<T>::value, "T does not implement prev.");

			static_assert(detail::has_cmp_eq<T>::value, "T does not implement operator==.");
			static_assert(detail::has_cmp_not_eq<T>::value, "T does not implement operator!=.");

			static_assert(detail::has_deref<T>::value, "T does not implement operator*.");
		}

		constexpr auto next_() {
			return static_cast<T*>(this)->next();
		}

		constexpr auto prev_() {
			return static_cast<T*>(this)->prev();
		}
	};


	// Free function comparitors for bi-directional iterators.
	template <typename T>
	bool operator==(const BiDirectionalIterator<T>& a, const BiDirectionalIterator<T>& b) {
		return static_cast<T>(a) == static_cast<T>(b);
	}

	template <typename T>
	bool operator!=(const BiDirectionalIterator<T>& a, const BiDirectionalIterator<T>& b) {
		return static_cast<T>(a) != static_cast<T>(b);
	}




	// Forward Iterator.
	template <typename T>
	struct ForwardIterator {
		ForwardIterator() {
			static_assert(detail::has_next<T>::value, "T does not implement next.");
		}

		auto next_() {
			static_assert(detail::has_next<T>::value, "T does not implement next.");
			return static_cast<T*>(this)->next();
		}
	};


	// Free function comparitors.
	template <typename T> bool operator==(const ForwardIterator<T>& a, const ForwardIterator<T>& b) {
		return static_cast<T>(a) == static_cast<T>(b);
	}

	template <typename T> bool operator!=(const ForwardIterator<T>& a, const ForwardIterator<T>& b) {
		return static_cast<T>(a) != static_cast<T>(b);
	}



	// Check if T is an iterator type.
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

	template <typename T> constexpr bool is_bidirectional_iterator_v = is_bidirectional_iterator<T>::value;
	template <typename T> constexpr bool is_forward_iterator_v = is_forward_iterator<T>::value;

	template <typename T>
	constexpr bool is_iterator = is_bidirectional_iterator_v<T> or is_forward_iterator_v<T>;


	// Free functions for operating on iterators.
	template <typename T>
	auto next(BiDirectionalIterator<T>& it) {
		static_assert(is_bidirectional_iterator<T>::value, "T is not a BiDirectionalIterator.");
		static_assert(detail::has_next<T>::value, "T does not implement next.");

		return it.next_();
	}

	template <typename T>
	auto prev(BiDirectionalIterator<T>& it) {
		static_assert(is_bidirectional_iterator<T>::value, "T is not a BiDirectionalIterator.");
		static_assert(detail::has_prev<T>::value, "T does not implement prev.");

		return it.prev_();
	}


	// ForwardIterator.
	template <typename T>
	auto next(ForwardIterator<T>& it) {
		static_assert(is_forward_iterator<T>::value, "T is not a ForwardIterator.");
		static_assert(detail::has_next<T>::value, "T does not implement next.");

		return it.next_();
	}




	// Variadic helpers.
	// accept any type of iterator which supports either next or prev.
	template <typename T1, typename T2, typename... Ts>
	void next(T1& first, T2& second, Ts&... args) {
		next(first);
		next(second);
		(next(args), ...);
	}

	template <typename T1, typename T2, typename... Ts>
	void prev(T1& first, T2& second, Ts&... args) {
		prev(first);
		prev(second);
		(prev(args), ...);
	}







	// Container trait.
	namespace detail {
		// Detect functionality in T. Poor man's concepts.
		template <typename T> using begin_t = decltype(declval<T>().begin());
		template <typename T> using end_t = decltype(declval<T>().end());

		template <typename T> using subscript_t = decltype(declval<T>()[declval<br::index_t>()]);


		template <typename T> using has_begin = is_detected<begin_t, T>;
		template <typename T> using has_end = is_detected<end_t, T>;

		template <typename T> using has_subscript = is_detected<subscript_t, T>;
	}


	// Base container trait.
	template <typename T>
	struct Container {
		Container() {
			static_assert(detail::has_begin<T>::value, "T does not implement begin.");
			static_assert(detail::has_end<T>::value, "T does not implement end.");
		}

		constexpr auto begin_() {
			return static_cast<T*>(this)->begin();
		}

		constexpr auto end_() {
			return static_cast<T*>(this)->end();
		}
	};


	// Check if T is a container.
	namespace detail {
		template <typename T>
		auto is_container_impl(Container<T> const&) -> true_type;
		auto is_container_impl(...) -> false_type;
	}

	template <typename T>
	using is_container = decltype(detail::is_container_impl(detail::declval<T>()));

	template <typename T> constexpr bool is_container_v = is_container<T>::value;



	// Free functions helpers.
	template <typename T> auto begin(Container<T>& c) {
		static_assert(is_container<T>::value, "T is not a Container.");
		static_assert(detail::has_begin<T>::value, "T does not implement begin.");

		return c.begin_();
	}

	template <typename T> auto end(Container<T>& c) {
		static_assert(is_container<T>::value, "T is not a Container.");
		static_assert(detail::has_end<T>::value, "T does not implement end.");

		return c.end_();
	}


	// Overload for static c-style arrays.
	template <typename T, br::size_t N> auto begin(T arr[N]) {
		return arr;
	}

	template <typename T, br::size_t N> auto end(T arr[N]) {
		return arr + (N + 1);
	}
}

#endif
