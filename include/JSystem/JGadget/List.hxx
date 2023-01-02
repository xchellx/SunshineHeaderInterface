#pragma once

#include <Dolphin/OS.h>
#include <Dolphin/types.h>

#include <JSystem/initializer_list.hxx>
#include <JSystem/JGadget/Allocator.hxx>
#include <JSystem/JGadget/Node.hxx>
#include <JSystem/JKernel/JKRHeap.hxx>

namespace JGadget {

    namespace {
        template <typename _T> class TPRIsEqual_Pointer_ {
            _T *pointer;

        public:
            TPRIsEqual_Pointer_() = delete;
            TPRIsEqual_Pointer_(_T *p) : pointer(p) {}

            bool operator()(const TPRIsEqual_Pointer_ &rhs) const { return pointer == rhs.pointer; }
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
    public:
        typedef _T value_type;
        typedef _Alloc allocator_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef typename _Alloc::pointer pointer;
        typedef typename _Alloc::const_pointer const_pointer;

    private:
        struct TNode_ {
            TNode_ *mNext;
            TNode_ *mPrev;
            value_type mItem;

            TNode_(TNode_ *next, TNode_ *prev, const value_type &item)
                : mNext(next), mPrev(prev), mItem(item) {}
#if __cplusplus >= 201103L
            TNode_(TNode_ *next, TNode_ *prev, value_type &&item)
                : mNext(next), mPrev(prev), mItem(item) {}
#endif
            ~TNode_() {}
        };

        TNode_ *CreateNode_(TNode_ *next, TNode_ *prev, const value_type &item) {
            return new TNode_(next, prev, item);
        }

    public:
        struct iterator {
            friend class TList;

            iterator(TNode_ *node) : mNode(node) {}
            iterator(const iterator &iter) = default;
            iterator(iterator &&iter) = default;

            bool operator==(const iterator &rhs) const { return mNode == rhs.mNode; }
            bool operator!=(const iterator &rhs) const { return mNode != rhs.mNode; }

            iterator operator+(int i) {
                iterator temp{mNode};
                for (size_t k = 0; k < i; ++k) {
                    temp->mNode = temp->mNode->mNext;  // Undefined behavior if past end
                }
                return temp;
            }

            iterator &operator+=(int i) {
                for (size_t k = 0; k < i; ++k) {
                    mNode = mNode->mNext;  // Undefined behavior if past end
                }
                return *this;
            }

            iterator &operator++() {
                mNode = mNode->mNext;
                return *this;
            }

            iterator operator++(int) {
                iterator temp{mNode};
                mNode = mNode->mNext;
                return temp;
            }

            iterator operator-(int i) {
                iterator temp{mNode};
                for (size_t k = 0; k < i; ++k) {
                    temp->mNode = temp->mNode->mPrev;  // Undefined behavior if past begin
                }
                return temp;
            }

            iterator &operator-=(int i) {
                for (size_t k = 0; k < i; ++k) {
                    mNode = mNode->mPrev;  // Undefined behavior if past begin
                }
                return *this;
            }

            iterator &operator--() {
                mNode = mNode->mPrev;
                return *this;
            }

            iterator operator--(int) {
                iterator temp{mNode};
                mNode = mNode->mPrev;
                return temp;
            }

            _T *operator->() const { return &mNode->mItem; }
            _T &operator*() { return mNode->mItem; }

        private:
            TNode_ *mNode;
        };

        struct const_iterator {
            friend class TList;

            explicit const_iterator(const TNode_ *node) : mNode(node) {}
            const_iterator(const const_iterator &iter) = default;
            const_iterator(const_iterator &&iter) = default;

            bool operator==(const const_iterator &rhs) const { return mNode == rhs.mNode; }
            bool operator!=(const const_iterator &rhs) const { return mNode != rhs.mNode; }

            const_iterator operator+(int i) {
                const_iterator temp{mNode};
                for (size_t k = 0; k < i; ++k) {
                    temp->mNode = temp->mNode->mNext;  // Undefined behavior if past end
                }
                return temp;
            }

            const_iterator &operator+=(int i) {
                for (size_t k = 0; k < i; ++k) {
                    mNode = mNode->mNext;  // Undefined behavior if past end
                }
                return *this;
            }

            const_iterator &operator++() {
                mNode = mNode->mNext;
                return *this;
            }

            const_iterator operator++(int) {
                const_iterator temp{mNode};
                mNode = mNode->mNext;
                return temp;
            }

            const_iterator operator-(int i) {
                const_iterator temp{mNode};
                for (size_t k = 0; k < i; ++k) {
                    temp->mNode = temp->mNode->mPrev;  // Undefined behavior if past begin
                }
                return temp;
            }

            const_iterator &operator-=(int i) {
                for (size_t k = 0; k < i; ++k) {
                    mNode = mNode->mPrev;  // Undefined behavior if past begin
                }
                return *this;
            }

            const_iterator &operator--() {
                mNode = mNode->mPrev;
                return *this;
            }

            const_iterator operator--(int) {
                iterator temp{mNode};
                mNode = mNode->mPrev;
                return temp;
            }

            const _T *operator->() const { return &mNode->mItem; }
            const _T &operator*() { return mNode->mItem; }

        private:
            const TNode_ *mNode;
        };

        TList() : mAllocator(), mSize(0), mBegin(nullptr), mEnd(nullptr) {
            mBegin = reinterpret_cast<TNode_ *>(&mBegin);
            mEnd  = reinterpret_cast<TNode_ *>(&mBegin);
        }

        explicit TList(const allocator_type &allocator)
            : mAllocator(allocator), mSize(0), mBegin(nullptr), mEnd(nullptr) {
            mBegin = reinterpret_cast<TNode_ *>(&mBegin);
            mEnd   = reinterpret_cast<TNode_ *>(&mBegin);
        }

#if __cplusplus >= 201103L
        TList(size_type count, const value_type &value,
              const allocator_type &allocator = allocator_type())
            : mAllocator(allocator), mSize(0), mBegin(nullptr), mEnd(nullptr) {
            mBegin = reinterpret_cast<TNode_ *>(&mBegin);
            mEnd   = reinterpret_cast<TNode_ *>(&mBegin);
            insert(end(), count, value);
        }
#else
        explicit TList(size_type count, const value_type &value = value_type(),
                       const allocator_type &allocator = allocator_type())
            : mAllocator(allocator), mSize(0), mBegin(nullptr), mEnd(nullptr) {
            mBegin = reinterpret_cast<TNode_ *>(&mBegin);
            mEnd = reinterpret_cast<TNode_ *>(&mBegin);
            insert(end(), count, value);
        }
#endif

#if __cplusplus >= 201402L
        explicit TList(size_type count, const allocator_type &allocator = allocator_type())
            : mAllocator(allocator), mSize(0), mBegin(nullptr), mEnd(nullptr) {
            mBegin = reinterpret_cast<TNode_ *>(&mBegin);
            mEnd   = reinterpret_cast<TNode_ *>(&mBegin);
            insert(end(), count, value_type());
        }
#else
        explicit TList(size_type count) : mAllocator(), mSize(0), mBegin(nullptr), mEnd(nullptr) {
            mBegin = reinterpret_cast<TNode_ *>(&mBegin);
            mEnd = reinterpret_cast<TNode_ *>(&mBegin);
            insert(end(), count, value_type());
        }
#endif

        TList(const TList &other)
            : mAllocator(other.mAllocator), mSize(0), mBegin(nullptr), mEnd(nullptr) {
            mBegin = reinterpret_cast<TNode_ *>(&mBegin);
            mEnd   = reinterpret_cast<TNode_ *>(&mBegin);
            for (auto i : other) {
                insert(end(), i);
            }
        }

#if __cplusplus >= 201103L
        TList(const TList &other, const allocator_type &allocator)
            : mAllocator(allocator), mSize(0), mBegin(nullptr), mEnd(nullptr) {
            mBegin = reinterpret_cast<TNode_ *>(&mBegin);
            mEnd   = reinterpret_cast<TNode_ *>(&mBegin);
            for (auto &item : other) {
                insert(end(), item);
            }
        }
        
        TList(TList &&other)
            : mAllocator(other.mAllocator), mSize(0), mBegin(nullptr), mEnd(nullptr) {
            mBegin = reinterpret_cast<TNode_ *>(&mBegin);
            mEnd   = reinterpret_cast<TNode_ *>(&mBegin);
            for (auto &item : other) {
                insert(end(), item);
            }
        }

        TList(TList &&other, const allocator_type &allocator)
            : mAllocator(allocator), mSize(0), mBegin(nullptr), mEnd(nullptr) {
            mBegin = reinterpret_cast<TNode_ *>(&mBegin);
            mEnd   = reinterpret_cast<TNode_ *>(&mBegin);
            for (auto &item : other) {
                insert(end(), item);
            }
        }

        TList(JSystem::initializer_list<value_type> list,
              const allocator_type &allocator = allocator_type())
            : mAllocator(allocator), mSize(0), mBegin(nullptr), mEnd(nullptr) {
            mBegin = reinterpret_cast<TNode_ *>(&mBegin);
            mEnd   = reinterpret_cast<TNode_ *>(&mBegin);
            for (auto &i : list) {
                insert(end(), i);
            }
        }
#endif

        ~TList() { clear(); }

        TList &operator=(const TList &other) {
            clear();
            for (auto i : other) {
                insert(end(), i);
            }
            return *this;
        }

        _GLIBCXX20_CONSTEXPR allocator_type get_allocator() const { return mAllocator; }

        reference front() { return *begin(); }
        const_reference front() const { return *begin(); }

        reference back() {
            iterator tmp = end();
            --tmp;
            return *tmp;
        }
        const_reference back() const {
            iterator tmp = end();
            --tmp;
            return *tmp;
        }

        _GLIBCXX20_CONSTEXPR void assign(size_type count, const_reference value) {
            clear();
            insert(begin(), count, value);
        }

#if __cplusplus >= 201103L
        _GLIBCXX20_CONSTEXPR void assign(JSystem::initializer_list<value_type> list) {
            clear();
            for (auto &i : list) {
                insert(end(), i);
            }
        }
#endif

        _GLIBCXX_NODISCARD bool empty() const _GLIBCXX_NOEXCEPT {
            return mBegin == mEnd && mSize == 0;
        }
        void clear() _GLIBCXX_NOEXCEPT { erase(begin(), end()); }

        size_type max_size() const _GLIBCXX_NOEXCEPT {
            return difference_type(-1) / sizeof(difference_type);
        }
        size_t size() const _GLIBCXX_NOEXCEPT { return mSize; }

        iterator begin() _GLIBCXX_NOEXCEPT { return {mBegin}; }
        const_iterator begin() const _GLIBCXX_NOEXCEPT { return {mBegin}; }
        iterator end() _GLIBCXX_NOEXCEPT {
            return {reinterpret_cast<TNode_ *>(&mBegin)}; }
        const_iterator end() const _GLIBCXX_NOEXCEPT {
            return {reinterpret_cast<TNode_ *>(&mBegin)};
        }

#if __cplusplus >= 201103L
        const_iterator cbegin() const _GLIBCXX_NOEXCEPT { return {mBegin}; }
        const_iterator cend() const _GLIBCXX_NOEXCEPT {
            return {reinterpret_cast<TNode_ *>(&mBegin)};
        }
#endif

        iterator erase(iterator iter) {
            TNode_ *next = iter.mNode->mNext;
            TNode_ *prev = iter.mNode->mPrev;

            prev->mNext = next;
            next->mPrev = prev;

            mAllocator.destroy(&iter.mNode->mItem);
            delete iter.mNode;

            mSize -= 1;
            return {next};
        }

        iterator erase(const_iterator start, const_iterator end) {
            iterator iter = start;
            while (iter != end) {
                iter = erase(iter);
            }
            return iter;
        }

        iterator insert(const_iterator at, const value_type &node) {
            TNode_ *current = at.mNode;
            TNode_ *prev    = current->mPrev;

            TNode_ *newNode = CreateNode_(current, prev, node);
            if (!newNode)
                return mEnd;

            current->mPrev = newNode;
            prev->mNext    = newNode;
            mSize += 1;

            return {newNode};
        }

        iterator insert(const_iterator at, value_type &&node) {
            value_type tmp = node;

            TNode_ *current = at.mNode;
            TNode_ *prev    = current->mPrev;

            TNode_ *newNode = CreateNode_(current, prev, tmp);
            if (!newNode)
                return mEnd;

            current->mPrev = newNode;
            prev->mNext    = newNode;
            mSize += 1;

            return {newNode};
        }

        iterator insert(const_iterator at, size_type count, const value_type &node) {
            for (size_t i = 0; i < count; ++i) {
                at = insert(at, node);
            }
            return at;
        }

        iterator insert(const_iterator at, size_type count, value_type &&node) {
            value_type tmp = node;
            for (size_t i = 0; i < count; ++i) {
                at = insert(at, tmp);
            }
            return at;
        }

#if __cplusplus >= 201103L
        iterator insert(const_iterator at, JSystem::initializer_list<value_type> list) {
            for (auto &i : list) {
                at = insert(at, i);
            }
            return at;
        }

        template <class... _Args> iterator emplace(const_iterator at, _Args &&...args) {
            value_type tmp;

#if __cplusplus <= 201703L
            mAllocator.construct(tmp, JSystem::forward<_Args>(args)...);
#else
            mAllocator.construct_at(tmp, JSystem::forward<_Args>(args)...);
#endif

            return insert(at, tmp);
        }
#endif

#if __cplusplus >= 201703L
        template <class... _Args> reference emplace_back(_Args &&...args) {
            return *emplace(end(), JSystem::forward<_Args>(args)...);
        }
        template <class... _Args> reference emplace_front(_Args &&...args) {
            return *emplace(begin(), JSystem::forward<_Args>(args)...);
        }
#else
        template <class... _Args> void emplace_back(_Args &&...args) {
            emplace(end(), JSystem::forward<_Args>(args)...);
        }
        template <class... _Args> void emplace_front(_Args &&...args) {
            emplace(begin(), JSystem::forward<_Args>(args)...);
        }
#endif

        void pop_back() {
            if (empty())
                return;
            erase(--end());
        }

        void pop_front() {
            if (empty())
                return;
            erase(begin());
        }

        void push_back() {
            if (empty())
                return;
            erase(--end());
        }

        void push_back(const value_type &value) { insert(end(), value); }
        void push_front(const value_type &value) { insert(begin(), value); }

#if __cplusplus >= 201103L
        void push_back(value_type &&value) { insert(end(), value); }
        void push_front(value_type &&value) { insert(begin(), value); }
#endif

        void resize(size_type s) { resize(s, value_type()); }

#if __cplusplus >= 201103L
        void resize(size_type s, const value_type &value) {
            const size_type currentSize = size();
            if (s == currentSize)
                return;

            if (s < currentSize) {
                erase(begin() + s, end());
            } else {
                insert(end(), s - currentSize, value);
            }
        }
#else
        void resize(size_type s, value_type value = value_type()) {
            const size_type currentSize = size();
            if (s == currentSize)
                return;

            if (s < currentSize) {
                erase(begin() + s, *end());
            } else {
                insert(end(), s - currentSize, value);
            }
        }
#endif

#if __cplusplus > 201703L
        size_type remove(const value_type &value) {
            size_type removed = 0;
            for (auto i = begin(); i != end(); ++i) {
                if (*i == value) {
                    i = erase(i);
                    removed += 1;
                }
            }
            return removed;
        }

        template <class _UnaryPredicate> size_type remove_if(_UnaryPredicate p) {
            size_type removed = 0;
            for (auto i = begin(); i != end(); ++i) {
                if (p(*i)) {
                    i = erase(i);
                    removed += 1;
                }
            }
            return removed;
        }
#else
        void remove(const value_type &value) {
            for (auto i = begin(); i != end(); ++i) {
                if (*i == value) {
                    i = erase(i);
                    removed += 1;
                }
            }
        }

        template <class _UnaryPredicate> void remove_if(_UnaryPredicate p) {
            for (auto i = begin(); i != end(); ++i) {
                if (p(*i)) {
                    i = erase(i);
                    removed += 1;
                }
            }
        }

        void splice(const_iterator at, TList &other) {
            iterator i = --other.end();
            while (true) {
                splice(at, other, i);

                if (i == other.begin())
                    break;

                --i;
            }
        }

        void splice(const_iterator at, TList &other, const_iterator sp) {
            TNode_ *current = at.mNode;
            TNode_ *prev = current->mPrev;

            TNode_ *transfer = sp.mNode;
            transfer->mNext = current;
            transfer->mPrev = prev;

            if (!transfer)
                return;

            current->mPrev = newNode;
            prev->mNext = newNode;

            mSize += 1;
            other.mSize -= 1;
        }

        void splice(const_iterator at, TList &other, const_iterator first, const_iterator last) {
            while (first != last) {
                splice(at, other, first++);
            }
        }
#endif

        allocator_type mAllocator;
        size_type mSize;
        TNode_ *mBegin;
        TNode_ *mEnd;
    };

    template <class _T, class _Alloc>
    bool operator==(const TList<_T, _Alloc> &lhs, const TList<_T, _Alloc> &rhs) {
        if (lhs.size() != rhs.size())
            return false;

        auto i = lhs.begin();
        auto j = rhs.begin();
        while (i != lhs.end() && j != rhs.end()) {
            if (i != j)
                return false;
            ++i;
            ++j;
        }

        return true;
    }

#if __cplusplus <= 201703L
    template <class _T, class _Alloc>
    bool operator!=(const TList<_T, _Alloc> &lhs, const TList<_T, _Alloc> &rhs) {
        if (lhs.size() != rhs.size())
            return true;

        auto i = lhs.begin();
        auto j = rhs.begin();
        while (i != lhs.end() && j != rhs.end()) {
            if (i != j)
                return true;
            ++i;
            ++j;
        }

        return false;
    }
#endif

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