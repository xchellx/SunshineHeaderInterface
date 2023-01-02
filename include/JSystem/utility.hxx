#pragma once

#include <JSystem/type_traits.hxx>

namespace JSystem {

    template <typename _Tp, typename _Ts, typename _Tv>
    void uninitialized_fill_n(_Tp dst, _Ts count, const _Tv &data) {
        for (_Ts i = 0; i < count; ++i) {
            *dst++ = data;
        }
    }

    template <typename _T> _T *copy(_T *begin, _T *end, _T *dst) {
        while (begin != end) {
            *dst++ = *begin++;
        }
        return dst;
    }

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