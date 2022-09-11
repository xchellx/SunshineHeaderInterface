#pragma once

#include <Dolphin/types.h>
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

    template <class _T, class _A = TAllocator<_T>> class TList {
        struct TNode_ {
            TNode_ *mNext;
            TNode_ *mPrev;
            _T mItem;

            ~TNode_(){};
        };

        TNode_ *CreateNode_(TNode_ *next, TNode_ *prev, const _T &item) {
            TNode_ *node = new TNode_();
            if (!node)
                return nullptr;
            node->mNext = next;
            node->mPrev = prev;
            node->mItem = item;
            return node;
        }

    public:
        class iterator {
        public:
            iterator(TNode_ *node) : mCurrent(node) {}
            iterator(const iterator &iter) : mCurrent(iter.mCurrent) {}

            bool operator==(const iterator &rhs) const { return mCurrent == rhs.mCurrent; }
            TNode_ *operator->() const { return mCurrent; }
            iterator operator++() { return iterator(mCurrent->mNext); }
            iterator operator--() { return iterator(mCurrent->mPrev); }
            TNode_ *operator*() { return mCurrent; }

            TNode_ *mCurrent;
            TNode_ *_04;
        };

        TList() : mAllocator(), mSize(0), mBegin(nullptr), mEnd(nullptr) {
            mBegin = reinterpret_cast<TNode_ *>(&mEnd);
            mEnd   = reinterpret_cast<TNode_ *>(&mEnd);
        }
        explicit TList(_A *allocator) { mAllocator = *allocator; }

        iterator begin() { return iterator(mBegin); }
        iterator end() { return iterator(mEnd->mNext); }

        iterator erase(iterator iter) {
            TNode_ *prev = iter->mPrev;
            TNode_ *next = iter->mNext;

            next->mPrev = prev;
            prev->mNext = next;
            delete iter.mCurrent;

            mSize -= 1;
            return iterator(prev);
        }

        iterator erase(iterator start, iterator end) {
            iterator iter = start;
            while (iter != end) {
                iter = erase(iter);
            }
            return iterator(iter);
        }

        iterator insert(iterator iter, const _T &node) {
            TNode_ *current = iter.mCurrent;
            TNode_ *prev    = current->mPrev;

            TNode_ *newNode = CreateNode_(iter.mCurrent, iter.mCurrent, node);
            if (!newNode)
                return end();

            current->mPrev = newNode;
            prev->mNext    = newNode;
            mSize += 1;

            return iterator(current);
        }

        _A mAllocator;
        size_t mSize;
        TNode_ *mEnd;
        TNode_ *mBegin;
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
            iterator(TSingleLinkListNode **nodelist);
            TSingleLinkListNode **mNodeList;
        };

        void Initialize();
        iterator Insert(iterator iter, TSingleLinkListNode *node);
        iterator end();

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

    using void_item = void *;
    class TList_pointer_void : public TAllocator<void_item> {
    public:
        void insert(TList<void_item, TAllocator>::iterator iterator, const void_item &node);
    };

    template <typename _T> class TList_pointer : public TList_pointer_void {
        class TNode_ {
        public:
            TNode_ *mPrev;
            TNode_ *mNext;
            void *mItem;
        };

    public:
        class iterator {
        public:
            iterator(_T *node) : mCurrent(node) {}
            iterator(const iterator &iter) : mCurrent(iter.mCurrent) {}

            _T *mCurrent;
        };

        iterator end();

        iterator insert(TList_pointer<_T>::iterator iterator, _T const &node);

        size_t mSize;
        TNode_ *mStart;
        TNode_ *mEnd;
    };

}  // namespace JGadget