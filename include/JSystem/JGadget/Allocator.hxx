#pragma once

#include <Dolphin/types.h>
#include <JSystem/stddef.hxx>

namespace JGadget {
    template <typename T> class TAllocator {
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef const T *const_pointer;
        typedef const T &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        template <class U> struct rebind { typedef TAllocator<U> other; };

        TAllocator() = default;

        pointer address(reference _x) const { return JSystem::addressof(_x); }
        const_pointer address(const_reference _x) const noexcept { return JSystem::addressof(_x); }

        pointer allocate(size_type _n, const void * = 0) {
            if (_n > max_size())
                return nullptr;
            return static_cast<T>(::operator new(_n * sizeof(T)));
        }

        void deallocate(pointer _p, size_type) { ::operator delete(_p); }

        size_type max_size() const { return size_t(-1) / sizeof(T); }
        
        void construct(pointer _p, const T &_val) { ::new ((void *)_p) T(_val); }

        template <typename... _Args> void construct(pointer _p, _Args &&..._args) {
            ::operator new((void *)_p) T(JSystem::forward<_Args>(_args)...);
        }
        
        void destroy(pointer _p) { _p->~T(); }

    private:
        u8 _00;
    };

    template <typename T> inline bool operator==(const TAllocator<T>&, const TAllocator<T>&) {
        return true;
    }

    template <typename T> inline bool operator!=(const TAllocator<T> &, const TAllocator<T> &) {
        return true;
    }
}  // namespace JGadget