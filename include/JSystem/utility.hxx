#pragma once

#include <JSystem/stddef.hxx>

namespace JSystem {
    template <typename _Tp> inline _Tp *addressof(_Tp &__r) _GLIBCXX_NOEXCEPT {
        return reinterpret_cast<_Tp *>(
            &const_cast<char &>(reinterpret_cast<const volatile char &>(__r)));
    }

    template <class _T> inline _T &&forward(typename remove_reference<_T>::type &t) noexcept {
        return static_cast<_T &&>(t);
    }

    template <class _T> inline _T &&forward(typename remove_reference<_T>::type &&t) noexcept {
        static_assert(!is_lvalue_reference<_T>::value, "Can not forward an rvalue as an lvalue.");
        return static_cast<_T &&>(t);
    }
}  // namespace JSystem