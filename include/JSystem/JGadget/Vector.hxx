#pragma once

#include <Dolphin/types.h>

#include <JSystem/JGadget/Allocator.hxx>
#include <JSystem/JGadget/Node.hxx>

namespace JGadget {

    template <typename _TP, typename _TS, typename _TV> void uninitialized_fill_n(_TP dst, _TS count, const _TV &data) {
        for (_TS i = 0; i < count; ++i) {
            *dst++ = data;
        }
    }

    template <typename _T> _T *copy(_T *begin, _T *end, _T *dst) {
        while (begin != end) {
            *dst++ = *begin++;
        }
        return dst;
    }

    template <class _T, class _A = TAllocator<_T>> class TVector {
    public:
        class iterator {
        public:
            iterator(TNode_ *node) : mCurrent(node) {}
            iterator(const iterator &iter) : mCurrent(iter.mCurrent) {}

            bool operator==(iterator &rhs) const { return mCurrent == rhs.mCurrent; }
            bool operator!=(iterator &rhs) const { return mCurrent != rhs.mCurrent; }
            iterator operator++() {
                ++mCurrent;
                return *this; 
            }
            iterator operator--() {
                --mCurrent;
                return *this;
            }
            _T operator->() const { return *mCurrent; }
            _T &operator*() const { return *mCurrent; }

            _T *mCurrent;
        };

        TVector(_A allocator) { mAllocator = allocator; }
        ~TVector() { erase(begin(), end()); }

        void DestroyElement_(_T *a, _T *b) {
            for (; a != b; ++a) {
            }
        }

        _T *InsertRaw(_T *at, size_t count);

        iterator begin() { return { mStart }; }
        iterator end() { return { mEnd }; }

        iterator erase(_T *a, _T *b) {
            _T *e = copy(b, mEnd, a);
            for (_T *i = e; i != mEnd; ++i) {
                delete i;
            }
            mEnd = e;
            return a;
        }

        iterator insert(_T *at, size_t count, _T *item) {
            auto *ofs  = at - mStart;
            auto *data = InsertRaw(at, count);
            if (data != end()) {
                uninitialized_fill_n(data, 1, item);
            }
            return mStart + ofs;
        }

        void reserve(size_t capacity) {
            if (mCapacity >= capacity)
                return;

            _T *reservedBuf = new _T[capacity];
            if (!reservedBuf)
                return;

            _T *b = mStart;
            _T *e = mEnd;
            size_t size = e - b;

            auto resBufIter = reservedBuf;
            for (_T *i = b; i != e; ++i) {
                *resBufIter++ = *i;
            }

            DestroyElement_(b, e);

            mEnd = reservedBuf + size;
            mStart = reservedBuf;
            mCapacity = capacity;

            delete[] b;
        }

        _A mAllocator;
        _T *mStart;
        _T *mEnd;
        size_t mCapacity;
        f32 _10;
        u32 _14;

    };

    class TVector_pointer_void : public TVector<void *> {
        TVector_pointer_void();
        ~TVector_pointer_void();

        iterator insert(void **a, void **b);
        void reserve(size_t capacity);
    };

}  // namespace JGadget