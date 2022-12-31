#pragma once

#include <Dolphin/types.h>

#include <JSystem/stddef.hxx>

namespace JGadget {
	template <class T1, class T2> struct TPair {
        typedef T1 first_type;
        typedef T2 second_type;

		constexpr TPair() = default;
        TPair(const TPair &p) = default;
        TPair(TPair &&p) = default;
        TPair(const first_type &a, const second_type &b)
            : first(a), second(b) {}

        TPair &operator=(const TPair& p) {
            first = p.first;
            second = p.second;
        }

		first_type first;
        second_type second;
	};
}