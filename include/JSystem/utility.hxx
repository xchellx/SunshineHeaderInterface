#pragma once

#include <JSystem/stddef.hxx>

namespace JSystem {
    template <class T> inline T &&forward(typename remove_reference<T>::type &t) noexcept {
        return static_cast<T &&>(t);
    }

    template <class T> inline T &&forward(typename remove_reference<T>::type &&t) noexcept {
        static_assert(!is_lvalue_reference<T>::value, "Can not forward an rvalue as an lvalue.");
        return static_cast<T &&>(t);
    }
}  // namespace JSystem