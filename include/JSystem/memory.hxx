#pragma once

#include <JSystem/bits/c++config.h>
#include <JSystem/utility.hxx>

namespace JSystem {
#if __cplusplus >= 201103L
    template <typename _Tp> inline _GLIBCXX17_CONSTEXPR _Tp *addressof(_Tp &__r) _GLIBCXX_NOEXCEPT {
        return reinterpret_cast<_Tp *>(
            &const_cast<char &>(reinterpret_cast<const volatile char &>(__r)));
    }
    template <typename _Tp> const _Tp *addressof(const _Tp &&) = delete;
#endif

    template <class _ForwardIt, class _NoThrowForwardIt>
    _ForwardIt uninitialized_copy(_ForwardIt first, _ForwardIt last, _NoThrowForwardIt d_first) {
        for (; first != last; ++d_first, (void) ++first) {
#if __cplusplus > 201703L
            ::new (const_cast<void *>(
                static_cast<const volatile void *>(JSystem::addressof(*d_first)))) _T(*first);
#elif __cplusplus >= 201103L
            ::new (static_cast<void *>(JSystem::addressof(*d_first)) _T(*first);
#else
            ::new (static_cast<void *>(&*d_first) _T(*first);
#endif
        }
        return first;
    }

#if __cplusplus >= 201103L
    template <class _ForwardIt, class _Size, class _NoThrowForwardIt>
    _ForwardIt uninitialized_copy_n(_ForwardIt first, _Size count, _NoThrowForwardIt d_first) {
        for (; n--; ++d_first, (void)++first) {
#if __cplusplus > 201703L
            ::new (const_cast<void *>(
                static_cast<const volatile void *>(JSystem::addressof(*d_first)))) _T(*first);
#else
            ::new (static_cast<void *>(JSystem::addressof(*d_first)) _T(*first);
#endif
        }
        return first;
    }
#endif

    template <class _ForwardIt, class _Size, class _T>
    _ForwardIt uninitialized_fill(_ForwardIt first, _ForwardIt last, const _T &data) {
        for (; first != last; ++first) {
#if __cplusplus > 201703L
            ::new (const_cast<void *>(
                static_cast<const volatile void *>(JSystem::addressof(*first)))) _T(data);
#elif __cplusplus >= 201103L
            ::new (static_cast<void *>(JSystem::addressof(*first)) _T(data);
#else
            ::new (static_cast<void *>(&*first) _T(data);
#endif
        }
        return first;
    }

#if __cplusplus >= 201103L
    template <class _ForwardIt, class _Size, class _T>
    _ForwardIt uninitialized_fill_n(_ForwardIt first, _Size count, const _T &data) {
        for (; count--; ++first) {
#if __cplusplus > 201703L
            ::new (const_cast<void *>(
                static_cast<const volatile void *>(JSystem::addressof(*first)))) _T(data);
#else
            ::new (static_cast<void *>(JSystem::addressof(*first)) _T(data);
#endif
        }
        return first;
    }
#else

    template <class _ForwardIt, class _Size, class _T>
    void uninitialized_fill_n(_ForwardIt first, _Size count, const _T &data) {
        for (; count--; ++first) {
            ::new (static_cast<void *>(&*first)) _T(data);
        }
    }
#endif

#if __cplusplus >= 201703L
        template <class _ForwardIt, class _NoThrowForwardIt>
    _ForwardIt uninitialized_move(_ForwardIt first, _ForwardIt last, _NoThrowForwardIt d_first) {
        for (; first != last; ++d_first, (void)++first) {
#if __cplusplus > 201703L
            ::new (const_cast<void *>(static_cast<const volatile void *>(
                JSystem::addressof(*d_first)))) _T(JSystem::move(*first));
#else
            ::new (static_cast<void *>(JSystem::addressof(*d_first)) _T(JSystem::move(*first));
#endif
        }
        return first;
    }

    template <class _ForwardIt, class _Size, class _NoThrowForwardIt>
    _ForwardIt uninitialized_move_n(_ForwardIt first, _Size count, _NoThrowForwardIt d_first) {
        for (; n--; ++d_first, (void)++first) {
#if __cplusplus > 201703L
            ::new (const_cast<void *>(
                static_cast<const volatile void *>(JSystem::addressof(*d_first)))) _T(JSystem::move(*first));
#else
            ::new (static_cast<void *>(JSystem::addressof(*d_first)) _T(JSystem::move(*first));
#endif
        }
        return first;
    }
    
    template <class _ForwardIt>
    _ForwardIt uninitialized_default_construct(_ForwardIt first, _ForwardIt last) {
        for (; first != last; ++first) {
#if __cplusplus > 201703L
            ::new (const_cast<void *>(
                static_cast<const volatile void *>(JSystem::addressof(*d_first)))) _T;
#else
            ::new (static_cast<void *>(JSystem::addressof(*d_first)) _T;
#endif
        }
        return first;
    }

    template <class _ForwardIt, class _Size>
    _ForwardIt uninitialized_default_construct_n(_ForwardIt first, _Size count) {
        for (; n--; ++first) {
#if __cplusplus > 201703L
            ::new (const_cast<void *>(
                static_cast<const volatile void *>(JSystem::addressof(*d_first)))) _T;
#else
            ::new (static_cast<void *>(JSystem::addressof(*d_first)) _T;
#endif
        }
        return first;
    }

    template <class _ForwardIt>
    _ForwardIt uninitialized_value_construct(_ForwardIt first, _ForwardIt last) {
        for (; first != last; ++first) {
#if __cplusplus > 201703L
            ::new (const_cast<void *>(
                static_cast<const volatile void *>(JSystem::addressof(*d_first)))) _T;
#else
            ::new (static_cast<void *>(JSystem::addressof(*d_first)) _T;
#endif
        }
        return first;
    }

    template <class _ForwardIt, class _Size>
    _ForwardIt uninitialized_value_construct_n(_ForwardIt first, _Size count) {
        for (; n--; ++first) {
#if __cplusplus > 201703L
            ::new (const_cast<void *>(
                static_cast<const volatile void *>(JSystem::addressof(*d_first)))) _T();
#else
            ::new (static_cast<void *>(JSystem::addressof(*d_first)) _T();
#endif
        }
        return first;
    }
#endif
}