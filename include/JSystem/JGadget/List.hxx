#pragma once

#include <Dolphin/OS.h>
#include <Dolphin/types.h>
#include <JKernel/JKRHeap.hxx>
#include <JSystem/JGadget/Allocator.hxx>
#include <JSystem/JGadget/Node.hxx>

namespace JGadget {

    namespace {
        template <typename _T> class TPRIsEqual_Pointer_ {
            _T *pointer;

        public:
            TPRIsEqual_Pointer_() = delete;
            TPRIsEqual_Pointer_(_T *p) : pointer(p) {}

            bool operator==(TPRIsEqual_Pointer_ &rhs) const { return pointer == rhs.pointer; }
            bool operator==(_T *rhs) const { return pointer == rhs; }
        };
    }  // namespace

    class TNodeLinkList {
    public:
        class iterator {
        public:
            iterator(TLinkListNode *node) : mCurrent(node) {}
            iterator(const iterator &iter) : mCurrent(iter.mCurrent) {}

            bool operator==(iterator &rhs) const { return mCurrent == rhs.mCurrent; }
            bool operator!=(iterator &rhs) const { return mCurrent != rhs.mCurrent; }
            TLinkListNode *operator->() const { return mCurrent; }

            TLinkListNode *mCurrent;
        };

        TLinkListNode *CreateNode_(TLinkListNode *prev, TLinkListNode *next, void **item);

        iterator begin() { return iterator(mStart.mCurrent); }
        iterator end();
        iterator Erase(iterator start, iterator end);
        iterator Insert(iterator iter);
        void Remove(TLinkListNode *node);
        template <typename _T> void Remove_if(_T _p, TNodeLinkList &list);

        size_t mSize;
        iterator mStart;
    };

    template <class _T, class _Alloc = TAllocator<_T>> class TList {
        struct TNode_ {
            TNode_ *mNext;
            TNode_ *mPrev;
            _T mItem;

            TNode_(TNode_ *next, TNode_ *prev, _T item) : mNext(next), mPrev(prev), mItem(item) {}
            ~TNode_() {}
        };

        TNode_ *CreateNode_(TNode_ *next, TNode_ *prev, const _T &item) {
            TNode_ *node = mAllocator.allocate(1);
            mAllocator.construct(node, next, prev, item);
            return node;
        }

    public:
        typedef _T value_type;
        typedef _Alloc allocator_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef _Alloc::pointer pointer;
        typedef _Alloc::const_pointer const_pointer;

        class iterator {
        public:
            iterator(TNode_ *node) : mNode(node) {}
            iterator(const TNode_ *node) : mNode(node) {}
            iterator(const iterator &iter) : mNode(iter.mNode) {}

            bool operator==(const iterator &rhs) const { return mNode == rhs.mNode; }
            bool operator!=(const iterator &rhs) const { return mNode != rhs.mNode; }

            iterator &operator++() {
                mNode = mNode->mNext;
                return *this;
            }
            iterator &operator--() {
                mNode = mNode->mPrev;
                return *this;
            }

            _T operator->() const { return mNode->mItem; }
            _T &operator*() { return mNode->mItem; }

            TNode_ *mNode;
        };

        TList() : mAllocator(), mSize(0), mFirst(nullptr), mLast(nullptr) {
            mFirst = reinterpret_cast<TNode_ *>(&mFirst);
            mLast  = reinterpret_cast<TNode_ *>(&mFirst);
        }
        TList(const TList &other) {
            mAllocator = other.mAllocator;
            for (auto &item : other) {
                insert(end(), item);
            }
        }
        explicit TList(allocator_type *allocator) { mAllocator = *allocator; }
        ~TList() { erase(begin(), end()); }

        iterator begin() { return {mFirst}; }
        iterator end() { return {reinterpret_cast<TNode_ *>(&mFirst)}; }

        size_t size() const { return mSize; }

        iterator erase(iterator iter) {
            TNode_ *next = iter.mNode->mNext;
            TNode_ *prev = iter.mNode->mPrev;

            prev->mNext = next;
            next->mPrev = prev;
            delete iter.mNode;

            mSize -= 1;
            return {next};
        }

        iterator erase(iterator start, iterator end) {
            iterator iter = start;
            while (iter != end) {
                iter = erase(iter);
            }
            return {iter};
        }

        iterator insert(iterator iter, const value_type &node) {
            TNode_ *current = iter.mNode;
            TNode_ *prev    = current->mPrev;

            TNode_ *newNode = CreateNode_(current, prev, node);
            if (!newNode)
                return mEnd;

            current->mPrev = newNode;
            prev->mNext    = newNode;
            mSize += 1;

            return {newNode};
        }

        iterator insert(iterator iter, value_type &&node) {
            TNode_ tmp = node;

            TNode_ *current = iter.mNode;
            TNode_ *prev    = current->mPrev;

            TNode_ *newNode = CreateNode_(current, prev, tmp);
            if (!newNode)
                return mEnd;

            current->mPrev = newNode;
            prev->mNext    = newNode;
            mSize += 1;

            return {newNode};
        }

        allocator_type mAllocator;
        size_type mSize;
        TNode_ *mFirst;
        TNode_ *mLast;
    };

    template <typename _T, size_t _S> class TLinkList {
    public:
        TLinkListNode *Element_getNode();
        _T *Element_getValue();
    };

    class TSingleNodeLinkList {
    public:
        class iterator {
        public:
            iterator(TSingleLinkListNode *node) : mNode(node) {}
            iterator(const iterator &iter) : mNode(iter.mNode) {}

            bool operator==(const iterator &rhs) const { return mNode == rhs.mNode; }
            bool operator!=(const iterator &rhs) const { return mNode != rhs.mNode; }

            iterator &operator++() {
                mNode = mNode->mNext;
                return *this;
            }

            TSingleLinkListNode *operator->() const { return mNode; }
            TSingleLinkListNode &operator*() { return *mNode; }

            TSingleLinkListNode *mNode;
        };

        void Initialize_();

        iterator Insert(iterator iter, TSingleLinkListNode *node);

        iterator Erase(iterator iter) {
            auto searchIter = begin();
            while (searchIter != end()) {
                TSingleLinkListNode *next = searchIter->mNext;
                if (next == iter.mNode) {
                    searchIter->mNext = iter->mNext;
                    delete iter.mNode;

                    mSize -= 1;
                    return iterator(searchIter->mNext);
                }
                ++searchIter;
            }
            return end();
        }

        iterator Erase(iterator start, iterator end) {
            iterator iter = start;
            while (iter != end) {
                iter = Erase(iter);
            }
            return iterator(iter);
        }

        iterator end();
        iterator begin() { return {mStart}; }

        size_t mSize;
        TSingleLinkListNode *mStart;
        TSingleLinkListNode *mEnd;
    };

    template <typename _T, size_t _S> class TSingleLinkList {
    public:
        class iterator {
        public:
            iterator(TSingleLinkListNode *node) : mCurrent(node) {}
            iterator(const iterator &iter) : mCurrent(iter.mCurrent) {}

            TSingleLinkListNode *mCurrent;
        };
        size_t mSize;
        TSingleLinkList mNode;
    };

    class TList_pointer_void : public TList<void *> {
    public:
        iterator insert(iterator iterator, void *const &node);
    };

    template <typename _T> class TList_pointer : public TList_pointer_void {
        iterator end();
        iterator insert(iterator iterator, const _T &node);
    };

}  // namespace JGadget