#pragma once

#include <Dolphin/types.h>
#include <JSystem/JGadget/Allocator.hxx>
#include <JSystem/JGadget/Node.hxx>

namespace JGadget {

    template <class _T, class _A = TAllocator<_T>> class TVector {
        class TNode_ {
            TNode_ *mPrev;
            TNode_ *mNext;
            void *mItem;
        };

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
            _T operator->() const { return mCurrent; }
            _T &operator*() const { return mCurrent; }

            _T *mCurrent;
        };

        TVector(_A allocator) { mAllocator = allocator; }

        TNode_ *CreateNode_(TNode_ *prev, TNode_ *next, _T *item);
        void DestroyElement_(_T *a, _T *b) {
            for (; a != b; ++a) {
            }
        }
        void InsertRaw(_T *a, u32);  // complete later

        iterator begin() { return { mStart }; }
        iterator end() { return { mEnd }; }
        iterator erase(_T *a, _T *b);        // complete later
        iterator insert(_T *a, u32, _T *b);  // complete later

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

        void insert(void **a, void **b);
        void reserve(size_t);
    };

}  // namespace JGadget