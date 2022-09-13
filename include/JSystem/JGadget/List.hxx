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

    template <class _T, class _A = TAllocator<_T>> class TList {
        struct TNode_ {
            TNode_ *mNext;
            TNode_ *mPrev;
            _T mItem;

            TNode_(TNode_ *next, TNode_ *prev, _T item) : mNext(next), mPrev(prev), mItem(item) {}
            ~TNode_() {}
        };

        TNode_ *CreateNode_(TNode_ *next, TNode_ *prev, const _T &item) {
            return new (JKRHeap::sSystemHeap, 4) TNode_(next, prev, item);
        }

    public:
        class iterator {
        public:
            iterator(TNode_ *node) : mNode(node) {}
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

            TNode_ *operator->() const { return mNode; }
            TNode_ &operator*() { return *mNode; }

            TNode_ *mNode;
        };

        TList() : mAllocator(), mSize(0), mFirst(nullptr), mLast(nullptr) {
            mFirst = reinterpret_cast<TNode_ *>(&mFirst);
            mLast  = reinterpret_cast<TNode_ *>(&mFirst);
        }
        explicit TList(_A *allocator) { mAllocator = *allocator; }
        ~TList() { erase(begin(), end()); }

        iterator begin() { return {mFirst}; }
        iterator end() { return {reinterpret_cast<TNode_ *>(&mFirst)}; }

        iterator erase(iterator iter) {
            TNode_ *next = iter->mNext;
            TNode_ *prev = iter->mPrev;

            prev->mNext = next;
            next->mPrev = prev;
            delete iter.mNode;

            mSize -= 1;
            return iterator(next);
        }

        iterator erase(iterator start, iterator end) {
            iterator iter = start;
            while (iter != end) {
                iter = erase(iter);
            }
            return iterator(iter);
        }

        iterator insert(iterator iter, const _T &node) {
            TNode_ *current = iter.mNode;
            TNode_ *prev    = current->mPrev;

            TNode_ *newNode = CreateNode_(current, prev, node);
            if (!newNode)
                return end();

            /*OSReport("==== TList::insert (0x%X) ====\n\n"
                     "- List Size      (%lu)\n"
                     "- Start Node     (0x%X)\n"
                     "- End Node       (0x%X)\n"
                     "-----------------------\n"
                     "- New Node       (0x%X)\n"
                     "- Current Node   (0x%X)\n"
                     "- Previous Node  (0X%X)\n\n",
                     this, mSize, begin().mNode, end().mNode, newNode, current, prev);*/

            current->mPrev = newNode;
            prev->mNext    = newNode;
            mSize += 1;

            return iterator(newNode);
        }

        _A mAllocator;
        size_t mSize;
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

    class TList_pointer_void : public TList<void *> {
    public:
        void insert(iterator iterator, const void *&node);
    };

    template <typename _T> class TList_pointer : public TList_pointer_void {
        iterator end();
        iterator insert(iterator iterator, const _T &node);
    };

}  // namespace JGadget