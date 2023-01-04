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

    template <typename _Tp> inline _GLIBCXX17_CONSTEXPR _Tp *addressof(_Tp &__r) _GLIBCXX_NOEXCEPT {
        return reinterpret_cast<_Tp *>(
            &const_cast<char &>(reinterpret_cast<const volatile char &>(__r)));
    }
    template <typename _Tp> const _Tp *addressof(const _Tp &&) = delete;

    template <class _Tp> inline constexpr _Tp &&forward(typename remove_reference<_Tp>::type &t) noexcept {
        return static_cast<_Tp &&>(t);
    }

    template <class _Tp>
    inline constexpr _Tp &&forward(typename remove_reference<_Tp>::type &&t) noexcept {
        static_assert(!is_lvalue_reference<_Tp>::value, "Can not forward an rvalue as an lvalue.");
        return static_cast<_Tp &&>(t);
    }

    template <typename _Tp>
    constexpr typename remove_reference<_Tp>::type &&move(_Tp &&t) noexcept {
        return static_cast<typename remove_reference<_Tp>::type &&>(t);
    }
    template <typename _Tp>
    struct __move_if_noexcept_cond : public __and_<__not_<is_nothrow_move_constructible<_Tp>>,
                                                   is_copy_constructible<_Tp>>::type {};

    template <typename _Tp>
    constexpr typename conditional<__move_if_noexcept_cond<_Tp>::value, const _Tp &, _Tp &&>::type
    move_if_noexcept(_Tp &__x) noexcept {
        return JSystem::move(__x);
    }

    // C++11 version of std::exchange for internal use.
    template <typename _Tp, typename _Up = _Tp> inline _Tp __exchange(_Tp &__obj, _Up &&__new_val) {
        _Tp __old_val = JSystem::move(__obj);
        __obj         = JSystem::forward<_Up>(__new_val);
        return __old_val;
    }
    /// @} group utilities
#define _GLIBCXX_MOVE(__val)         std::move(__val)
#define _GLIBCXX_FORWARD(_Tp, __val) std::forward<_Tp>(__val)
#else
#define _GLIBCXX_MOVE(__val)         (__val)
#define _GLIBCXX_FORWARD(_Tp, __val) (__val)
#endif

    template <typename _Tp>
    inline
#if __cplusplus >= 201103L
        typename enable_if<__and_<__not_<__is_tuple_like<_Tp>>, is_move_constructible<_Tp>,
                                  is_move_assignable<_Tp>>::value>::type
        swap(_Tp &__a, _Tp &__b) noexcept(
            __and_<is_nothrow_move_constructible<_Tp>, is_nothrow_move_assignable<_Tp>>::value)
#else
        void
        swap(_Tp &__a, _Tp &__b)
#endif
    {
        _Tp __tmp = _GLIBCXX_MOVE(__a);
        __a       = _GLIBCXX_MOVE(__b);
        __b       = _GLIBCXX_MOVE(__tmp);
    }
    // _GLIBCXX_RESOLVE_LIB_DEFECTS
    // DR 809. std::swap should be overloaded for array types.
    /// Swap the contents of two arrays.
    template <typename _Tp, size_t _Nm>
    inline
#if __cplusplus >= 201103L
        typename enable_if<__is_swappable<_Tp>::value>::type
        swap(_Tp (&__a)[_Nm], _Tp (&__b)[_Nm]) noexcept(__is_nothrow_swappable<_Tp>::value)
#else
        void
        swap(_Tp (&__a)[_Nm], _Tp (&__b)[_Nm])
#endif
    {
        for (size_t __n = 0; __n < _Nm; ++__n)
            swap(__a[__n], __b[__n]);
    }

}  // namespace JSystem