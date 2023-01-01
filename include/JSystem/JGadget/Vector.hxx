#pragma once

#include <Dolphin/types.h>
#include <Dolphin/math.h>

#include <SMS/assert.h>

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

    template <class _T, class _Alloc = TAllocator<_T>> class TVector {
    public:
        typedef typename _T value_type;
        typedef typename _Alloc allocator_type;
        typedef typename size_t size_type;
        typedef typename ptrdiff_t difference_type;
        typedef typename value_type &reference;
        typedef typename const value_type &const_reference;
        typedef typename _Alloc::pointer pointer;
        typedef typename _Alloc::const_pointer const_pointer;

        struct iterator {
            iterator(pointer node) : mCurrent(node) {}
            iterator(const iterator &iter) : mCurrent(iter.mCurrent) {}

            bool operator==(const iterator &rhs) const { return mCurrent == rhs.mCurrent; }
            bool operator!=(const iterator &rhs) const { return mCurrent != rhs.mCurrent; }

            iterator operator+(int i) {
                iterator temp{mCurrent};
                temp->mCurrent += i;
                return temp;
            }

            iterator &operator+=(int i) {
                mCurrent += i;
                return *this;
            }

            iterator &operator++() {
                ++mCurrent;
                return *this; 
            }

            iterator operator++(int) {
                iterator temp{mCurrent};
                ++mCurrent;
                return temp;
            }

            iterator operator-(int i) {
                iterator temp{mCurrent};
                temp->mCurrent -= i;
                return temp;
            }

            iterator &operator-=(int i) {
                mCurrent -= i;
                return *this;
            }

            iterator &operator--() {
                --mCurrent;
                return *this;
            }

            iterator operator--(int) {
                iterator temp{mCurrent};
                --mCurrent;
                return temp;
            }

            pointer operator->() const { return *mCurrent; }
            reference operator*() const { return *mCurrent; }

        private:
            pointer mCurrent;
        };

        explicit TVector(allocator_type allocator) { mAllocator = allocator; }
        ~TVector() { erase(begin(), end()); }

        TVector &operator=(const TVector &other) { 
            clear();
            for (auto &i : other) {
                insert(end(), i);
            }
            return *this;
        }

        reference operator[](size_type index) { return mStart[index]; }
        const_reference operator[](size_type index) const { return mStart[index]; }

        allocator_type get_allocator() const { return mAllocator; }

        reference at(size_type index) {
            if (index >= size()) {
                OSReport("Attempted to access OOB item (%lu) of Vector (size %lu)!", index, size());
                while (true) {
                    __asm volatile("");
                }
            }
            return mStart[index];
        }

        const_reference at(size_type index) const {
            if (index >= size()) {
                OSReport("Attempted to access OOB item (%lu) of Vector (size %lu)!", index, size());
                while (true) {
                    __asm volatile("");
                }
            }
            return mStart[index];
        }

        reference front() { return *mBegin; }
        const_reference front() const { return *mBegin; }

        reference back() { return *(mEnd - 1); }
        const_reference back() const { return *(mEnd - 1); }

        void assign(size_type count, const_reference value) {
            clear();
            insert(begin(), count, value);
        }

        void assign(size_type count, value_type &&value) {
            clear();
            insert(begin(), count, value);
        }

        bool empty() const { return mBegin == mEnd; }
        void clear() { erase(*begin(), *end()); }

        size_type capacity() { return mCapacity; }
        size_type size() { return mStart ? mEnd - mStart : 0; }

        iterator begin() { return {mStart}; }
        iterator end() { return {mEnd}; }

        iterator erase(iterator a) { return erase(*a, *(a + 1)); }
        iterator erase(iterator a, iterator b) { return erase(*a, *b); }
        iterator erase(pointer a, pointer b) {
            pointer e = copy(b, mEnd, a);
            for (pointer i = e; i != mEnd; ++i) {
                mAllocator.destroy(i);
                mAllocator.deallocate(i, 1);
            }
            mEnd = e;
            return a;
        }

        iterator insert(iterator at, value_type &&item) { return insert(*at, 1, item); }
        iterator insert(iterator at, const_reference item) { return insert(*at, 1, item); }
        iterator insert(iterator at, size_type count, const_reference item) {
            return insert(*at, count, item);
        }
        iterator insert(iterator at, size_type count, value_type &&item) {
            value_type tmp = item;
            return insert(*at, count, tmp);
        }
        iterator insert(pointer at, size_type count, const_reference item) {
            auto *ofs  = at - mStart;
            auto *data = InsertRaw(at, count);
            if (data != end()) {
                uninitialized_fill_n(data, count, item);
            }
            return mStart + ofs;
        }

        void push_back(const_reference item) { insert(end(), item); }
        void pop_back() { erase(end()); }

        void reserve(size_type capacity) {
            if (mCapacity >= capacity)
                return;

            pointer reservedBuf = mAllocator.allocate(capacity);
            if (!reservedBuf)
                return;

            pointer b          = mStart;
            pointer e          = mEnd;
            size_type size = e - b;

            auto resBufIter = reservedBuf;
            for (pointer i = b; i != e; ++i) {
                *resBufIter++ = *i;
            }

            DestroyElement_(b, e);

            mEnd      = reservedBuf + size;
            mStart    = reservedBuf;
            mCapacity = capacity;

            mAllocator.deallocate(b, 1);
        }

        void resize(size_type s) {
            const size_type currentSize = size();
            if (s == currentSize)
                return;

            if (s < currentSize) {
                erase(*begin() + s, *end());
            } else {
                insert(*end(), s - currentSize, value_type());
            }
        }

    private:
        void DestroyElement_(pointer a, pointer b) {
            for (; a != b; ++a) {
                mAllocator.destroy(a);
            }
        }

        pointer InsertRaw(pointer at, size_type count) {
            if (count == 0)
                return at;

            size_type vsize = size();
            size_type vcapacity = capacity();

            if (vcapacity < count + vsize) {
                size_type ncapacity = Max(_14 + _10, count + vsize);

                // Allocate the new buffer since we maxxed the capacity
                pointer nbuffer = mAllocator.allocate(ncapacity);
                if (!nbuffer)
                    return mEnd;

                // Copy construct the values before the insertion
                pointer nbiter = nbuffer;
                for (pointer i = mStart; i != at; ++i) {
                    mAllocator.construct(nbiter++, *i);
                }

                // Copy construct the values after the insertion
                pointer naiter = nbiter + count;
                for (pointer i = at; i != mEnd; ++i) {
                    mAllocator.construct(naiter++, *i);
                }

                // Destroy old buffer
                DestroyElement_(mStart, mEnd);

                pointer vbegin = mStart;

                mEnd      = nbuffer + count + vsize;
                mStart    = nbuffer;
                mCapacity = ncapacity;

                mAllocator.deallocate(vbegin, 1);
                return nbiter;
            }

            pointer ieiter = at + count;
            if (ieiter < mEnd) {
                // Copy construct the values after the end
                pointer newiter = mEnd;
                for (pointer i = mEnd - count; i != mEnd; ++i) {
                    mAllocator.construct(newiter++, *i);
                }

                // Copy new values into inserted space? (Makes no sense)
                pointer insertIter = mEnd;
                for (pointer i = mEnd - count; i > at; --i) {
                    *insertIter = *i;
                }

                for (pointer i = at; i != mEnd - count; ++i) {
                    mAllocator.destroy(*i);
                }
            } else {
                pointer insertIter = ieiter;
                for (pointer i = at; i != mEnd; ++i) {
                    mAllocator.construct(insertIter++, *i);
                }

                // Destroy old elements
                DestroyElement_(at, mEnd);
            }

            mEnd += count;
            return at;
        }

        allocator_type mAllocator;
        pointer mStart;
        pointer mEnd;
        size_type mCapacity;
        f32 _10;
        size_type _14;
    };

    class TVector_pointer_void : public TVector<void *> {
        TVector_pointer_void();
        ~TVector_pointer_void();

        iterator insert(void **a, void **b);
        void reserve(size_type capacity);
    };

}  // namespace JGadget