#pragma once

#include <Dolphin/types.h>
#include <SMS/assert.h>

#include <JSystem/JDrama/JDRNameRef.hxx>
#include <JSystem/JGadget/Allocator.hxx>
#include <JSystem/JGadget/Node.hxx>
#include <JSystem/JGadget/Pair.hxx>
#include <JSystem/function.hxx>

using namespace JSystem;

namespace JGadget {
    template <typename _T> struct hash {
        typedef size_t result_type;
        typedef _T argument_type;

        result_type operator()(argument_type v) { return 0; }
    };

    using str_hash = hash<const char *>;
    using u16_hash = hash<u16>;
    using u32_hash = hash<u32>;
    using u64_hash = hash<u64>;

    template <> u16_hash::result_type u16_hash::operator()(argument_type v) {
        u32 p   = 0x5555;  // pattern of alternating 0 and 1
        u32 c   = 17317;  // random uneven integer constant;
        u32 mix = p * (v ^ (v >> 16));
        return c * (mix ^ (mix >> 16);
    }

    template <> u32_hash::result_type u32_hash::operator()(argument_type v) {
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = ((x >> 16) ^ x) * 0x45d9f3b;
        x = (x >> 16) ^ x;
        return x;
    }

    template <> u64_hash::result_type u64_hash::operator()(argument_type v) {
        x = (x ^ (x >> 30)) * argument_type(0xbf58476d1ce4e5b9);
        x = (x ^ (x >> 27)) * argument_type(0x94d049bb133111eb);
        x = x ^ (x >> 31);
        return x;
    }

    template <> str_hash::result_type str_hash::operator()(argument_type v) {
        return JDrama::TNameRef::calcKeyCode(v);
    }

    struct str_equal_to : binary_function<const char *, const char *, bool> {
        constexpr result_type operator()(first_argument_type a, second_argument_type b) {
            return JDrama::TNameRef::calcKeyCode(a) == JDrama::TNameRef::calcKeyCode(b);
        }
    };

    template <class _Key, class _T, class _Hash = str_hash, class _Pred = equal_to<_Key>,
              class _Alloc = TAllocator<TPair<const _Key, _T>>>
    class TUnorderedMap {
    public:
        typedef _Key key_type;
        typedef _T mapped_type;
        typedef TPair<const key_type, mapped_type> value_type;
        typedef _Hash hasher;
        typedef _Pred key_equal;
        typedef _Alloc allocator_type;
        typedef _Alloc::reference reference;
        typedef _Alloc::const_reference const_reference;
        typedef _Alloc::pointer pointer;
        typedef _Alloc::const_pointer const_pointer;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type; 
        typedef TList<value_type> items_type;

        static constexpr size_t SurfaceSize = 64;

        using ItemList = JGadget::TList<Item>;

        TUnorderedMap() = default;
        TUnorderedMap(const TUnorderedMap &ump) = default;
        TUnorderedMap(TUnorderedMap &&ump) = default;
        TUnorderedMap(const TUnorderedMap& ump, const allocator_type& alloc) {

        }
        TUnorderedMap(TUnorderedMap &&, const allocator_type &alloc) {}
        explicit TUnorderedMap(size_t n, const hasher& hf, const key_equal& ke,
            const allocator_type& alloc) {

        }

        TDictS() { mItemBuffer = new ItemList[SurfaceSize]; }
        ~TDictS() { delete[] mItemBuffer; }

        _V *operator[](const char *key) { return get(key); }

        bool hasKey(const char *key) const {
            const u32 index = getIndex(getHash(key));

            auto &itemList = mItemBuffer[index];
            for (auto &item : itemList) {
                if (strcmp(item.mKey, key) == 0) {
                    return true;
                }
            }

            return false;
        }

        _V get(const char *key) const {
            const u32 index = getIndex(getHash(key));

            auto &itemList = mItemBuffer[index];
            for (auto &item : itemList) {
                if (strcmp(item.mKey, key) == 0) {
                    return item.mValue;
                }
            }

            return nullptr;
        }

        void set(const char *key, _V value) {
            const u32 index = getIndex(getHash(key));

            auto &itemList = mItemBuffer[index];
            for (auto &item : itemList) {
                if (strcmp(item.mKey, key) == 0) {
                    item.mValue = value;
                    return;
                }
            }
            itemList.insert(itemList.end(), {key, value});
        }

        _V *pop(const char *key) {
            const u32 index = getIndex(getHash(key));

            auto &itemList = mItemBuffer[index];
            for (auto i = itemList.begin(); i != itemList.end(); ++i) {
                Item &item = i.mNode->mItem;
                if (strcmp(item.mKey, key) == 0) {
                    itemList.erase(i);
                    return &item.mValue;
                }
            }

            return nullptr;
        }

        _V &setDefault(const char *key, const _V &default_) {
            const u32 index = getIndex(getHash(key));

            auto &itemList = mItemBuffer[index];
            for (auto &item : itemList) {
                if (strcmp(item.mKey, key) == 0) {
                    return &item.mValue;
                }
            }

            itemList.insert(itemList.end(), {key, default_});
            return default_;
        }

        _V &setDefault(const char *key, _V *&&default_) {
            const u32 index = getIndex(getHash(key));

            auto &itemList = mItemBuffer[index];
            for (auto &item : itemList) {
                if (strcmp(item.mKey, key) == 0) {
                    delete default_;
                    return &item.mValue;
                }
            }

            itemList.insert(itemList.end(), {key, *default_});
            return *default_;
        }

        void items(ItemList &out) const {
            if (!mItemBuffer)
                return;

            for (u32 i = 0; i < SurfaceSize; ++i) {
                for (auto &item : mItemBuffer[i]) {
                    out.insert(out.end(), item);
                }
            }
        }

        void empty() {
            if (!mItemBuffer)
                return;

            for (u32 i = 0; i < SurfaceSize; ++i) {
                auto &itemList = mItemBuffer[i];
                itemList.erase(itemList.begin(), itemList.end());
            }
        }

    private:
        constexpr u32 getIndex(u16 hash) const { return hash % SurfaceSize; }

        u16 getHash(const char *key) const { return JDrama::TNameRef::calcKeyCode(key); }
        u16 getHash(const JDrama::TNameRef &key) const { return key.mKeyCode; }

        allocator_type mAllocator;
        ItemList *mItemBuffer;
    };
}