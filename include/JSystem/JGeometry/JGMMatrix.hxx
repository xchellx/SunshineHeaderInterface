#pragma once

#include <Dolphin/MTX.h>
#include <Dolphin/math.h>
#include <JSystem/JGeometry/JGMVec.hxx>
#include <JSystem/equivtype.hxx>

namespace JGeometry {

    template <typename T> struct SMatrix33 {
        T m[3][4];

        static SMatrix33 identity() {
            SMatrix33 mtx;

            mtx[0][0] = 1;
            mtx[0][1] = 0;
            mtx[0][2] = 0;
            mtx[1][0] = 0;
            mtx[1][1] = 1;
            mtx[1][2] = 0;
            mtx[2][0] = 0;
            mtx[2][1] = 0;
            mtx[2][2] = 1;

            return mtx;
        }

        SMatrix33() = default;

        operator Mtx33 *() const {
            static_assert(is_equal_type<T, f32>());
            return (Mtx33 *)&x;
        }
        operator const Mtx33 *() const {
            static_assert(is_equal_type<T, f32>());
            return (const Mtx33 *)&x;
        }

        T *&operator[](const int row) { return m[row]; }

        T at(u32 row, u32 column) { return m[row][column]; }
    };

    template <typename T> struct SMatrix34 {
        T m[3][4];

        static SMatrix34 identity() {
            SMatrix34 mtx;

            mtx[0][0] = 1;
            mtx[0][1] = 0;
            mtx[0][2] = 0;
            mtx[0][3] = 0;
            mtx[1][0] = 0;
            mtx[1][1] = 1;
            mtx[1][2] = 0;
            mtx[1][3] = 0;
            mtx[2][0] = 0;
            mtx[2][1] = 0;
            mtx[2][2] = 1;
            mtx[2][3] = 0;

            return mtx;
        }

        SMatrix34() = default;

        operator Mtx *() const {
            static_assert(is_equal_type<T, f32>());
            return (Mtx *)&x;
        }
        operator const Mtx *() const {
            static_assert(is_equal_type<T, f32>());
            return (const Mtx *)&x;
        }

        T *&operator[](const int idx) {
            return m[idx]; }

        T at(u32 row, u32 column) { return m[row][column]; }
    };

    template <typename T> struct SMatrix44 {
        T m[4][4];

        static SMatrix44 identity() {
            SMatrix44 mtx;

            mtx[0][0] = 1;
            mtx[0][1] = 0;
            mtx[0][2] = 0;
            mtx[0][3] = 0;
            mtx[1][0] = 0;
            mtx[1][1] = 1;
            mtx[1][2] = 0;
            mtx[1][3] = 0;
            mtx[2][0] = 0;
            mtx[2][1] = 0;
            mtx[2][2] = 1;
            mtx[2][3] = 0;
            mtx[3][0] = 0;
            mtx[3][1] = 0;
            mtx[3][2] = 0;
            mtx[3][3] = 1;

            return mtx;
        }

        SMatrix44() = default;

        operator Mtx44 *() const {
            static_assert(is_equal_type<T, f32>());
            return (Mtx44 *)&x;
        }
        operator const Mtx44 *() const {
            static_assert(is_equal_type<T, f32>());
            return (const Mtx44 *)&x;
        }

        T *&operator[](const int idx) { return m[idx]; }

        T at(u32 row, u32 column) { return m[row][column]; }
    };

    template <typename MatrixT> struct TMatrix33 {
        MatrixT mtx;

        TMatrix33() = default;
    };

    template <typename MatrixT> struct TMatrix34 {
        MatrixT mtx;

        TMatrix34() = default;
    };

    template <typename MatrixT> struct TMatrix44 {
        MatrixT mtx;

        TMatrix44() = default;
    };

    typedef SMatrix33<f32> SMtx33f;
    typedef SMatrix34<f32> SMtx34f;
    typedef SMatrix44<f32> SMtx44f;
    typedef TMatrix33<f32> TMtx33f;
    typedef TMatrix34<f32> TMtx34f;
    typedef TMatrix44<f32> TMtx44f;
}  // namespace JGeometry