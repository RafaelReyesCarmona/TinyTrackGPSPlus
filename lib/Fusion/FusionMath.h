/**
 * @file FusionMath.h
 * @author Seb Madgwick
 * @brief Math library.
 */

#ifndef FUSION_MATH_H
#define FUSION_MATH_H

//------------------------------------------------------------------------------
// Includes

#include <math.h> // M_PI, sqrtf, atan2f, asinf
#include <stdbool.h>
#include <stdint.h>

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief 3D vector.
 */
typedef union {
    float array[3];

    struct {
        float x;
        float y;
        float z;
    } axis;
} FusionVector;

/**
 * @brief 3D vector double precision.
 */
typedef union {
    double array[3];

    struct {
        double x;
        double y;
        double z;
    } axis;
} FusionVectorDouble;

/**
 * @brief Quaternion.
 */
typedef union {
    float array[4];

    struct {
        float w;
        float x;
        float y;
        float z;
    } element;
} FusionQuaternion;

/**
 * @brief 3x3 matrix in row-major order.
 * See http://en.wikipedia.org/wiki/Row-major_order
 */
typedef union {
    float array[3][3];

    struct {
        float xx;
        float xy;
        float xz;
        float yx;
        float yy;
        float yz;
        float zx;
        float zy;
        float zz;
    } element;
} FusionMatrix;

/**
 * @brief Euler angles.  Roll, pitch, and yaw correspond to rotations around
 * X, Y, and Z respectively.
 */
typedef union {
    float array[3];

    struct {
        float roll;
        float pitch;
        float yaw;
    } angle;
} FusionEuler;

/**
 * @brief Vector of zeros.
 */
#define FUSION_VECTOR_ZERO ((FusionVector){ .array = {0.0f, 0.0f, 0.0f} })

/**
 * @brief Vector of zeros.
 */
#define FUSION_VECTORDOUBLE_ZERO ((FusionVectorDouble){ .array = {0.0, 0.0, 0.0} })

/**
 * @brief Vector of ones.
 */
#define FUSION_VECTOR_ONES ((FusionVector){ .array = {1.0f, 1.0f, 1.0f} })

/**
 * @brief Identity quaternion.
 */
#define FUSION_IDENTITY_QUATERNION ((FusionQuaternion){ .array = {1.0f, 0.0f, 0.0f, 0.0f} })

/**
 * @brief Identity matrix.
 */
#define FUSION_IDENTITY_MATRIX ((FusionMatrix){ .array = {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}} })

/**
 * @brief Euler angles of zero.
 */
#define FUSION_EULER_ZERO ((FusionEuler){ .array = {0.0f, 0.0f, 0.0f} })

/**
 * @brief Pi. May not be defined in math.h.
 */
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

/**
 * @brief Include this definition or add as a preprocessor definition to use
 * normal square root operations.
 */
#define FUSION_USE_NORMAL_SQRT

//------------------------------------------------------------------------------
// Inline functions - Degrees and radians conversion

/**
 * @brief Converts degrees to radians.
 * @param degrees Degrees.
 * @return Radians.
 */
static inline float FusionDegreesToRadiansf(const float degrees) {
    return degrees * ((float) M_PI / 180.0f);
}

/**
 * @brief Converts degrees to radians.
 * @param degrees Degrees.
 * @return Radians.
 */
static inline double FusionDegreesToRadians(const double degrees) {
    return degrees * ( M_PI / 180.0);
}

/**
 * @brief Converts radians to degrees.
 * @param radians Radians.
 * @return Degrees.
 */
static inline float FusionRadiansToDegreesf(const float radians) {
    return radians * (180.0f / (float) M_PI);
}

/**
 * @brief Converts radians to degrees.
 * @param radians Radians.
 * @return Degrees.
 */
static inline double FusionRadiansToDegrees(const float radians) {
    return radians * (180.0 / M_PI);
}

//------------------------------------------------------------------------------
// Inline functions - Arc sine

/**
 * @brief Returns the arc sine of the value.
 * @param value Value.
 * @return Arc sine of the value.
 */
static inline float FusionAsin(const float value) {
    if (value <= -1.0f) {
        return (float) M_PI / -2.0f;
    }
    if (value >= 1.0f) {
        return (float) M_PI / 2.0f;
    }
    return asinf(value);
}

//------------------------------------------------------------------------------
// Inline functions - Fast inverse square root

#ifndef FUSION_USE_NORMAL_SQRT

/**
 * @brief Calculates the reciprocal of the square root.
 * See https://pizer.wordpress.com/2008/10/12/fast-inverse-square-root/
 * @param x Operand.
 * @return Reciprocal of the square root of x.
 */
static inline float FusionFastInverseSqrt(const float x) {

    typedef union {
        float f;
        int32_t i;
    } Union32;

    Union32 union32 = {.f = x};
    union32.i = 0x5F1F1412 - (union32.i >> 1);
    return union32.f * (1.69000231f - 0.714158168f * x * union32.f * union32.f);
}
// Test this code--------------------------------------------
static inline float inv_sqrt(const float x)
{ union { float f; uint32_t u; } y = {x};
y.u = 0x5F1FFF77ul - (y.u >> 1);
return 0.703974056f * y.f * (2.38919526f - x * y.f * y.f);
}
//-----------------------------------------------------------
/**
 * @brief Fast calculates the square root.
 * See https://pizer.wordpress.com/2008/10/12/fast-inverse-square-root/
 * @param x Operand.
 * @return Square root of x.
 */
static inline float FusionFastSqrt(const float x) {
    return 1.0f / inv_sqrt(x);
}
#endif

//------------------------------------------------------------------------------
// Inline functions - Vector operations

/**
 * @brief Returns true if the vector is zero.
 * @param vector Vector.
 * @return True if the vector is zero.
 */
static inline bool FusionVectorIsZero(const FusionVector vector) {
    return (vector.axis.x == 0.0f) && (vector.axis.y == 0.0f) && (vector.axis.z == 0.0f);
}

/**
 * @brief Returns the sum of two vectors.
 * @param vectorA Vector A.
 * @param vectorB Vector B.
 * @return Sum of two vectors.
 */
static inline FusionVector FusionVectorAdd(const FusionVector vectorA, const FusionVector vectorB) {
    const FusionVector result = {.axis = {
            .x = vectorA.axis.x + vectorB.axis.x,
            .y = vectorA.axis.y + vectorB.axis.y,
            .z = vectorA.axis.z + vectorB.axis.z,
    }};
    return result;
}

/**
 * @brief Returns vector B subtracted from vector A.
 * @param vectorA Vector A.
 * @param vectorB Vector B.
 * @return Vector B subtracted from vector A.
 */
static inline FusionVector FusionVectorSubtract(const FusionVector vectorA, const FusionVector vectorB) {
    const FusionVector result = {.axis = {
            .x = vectorA.axis.x - vectorB.axis.x,
            .y = vectorA.axis.y - vectorB.axis.y,
            .z = vectorA.axis.z - vectorB.axis.z,
    }};
    return result;
}

/**
 * @brief Returns the sum of the elements.
 * @param vector Vector.
 * @return Sum of the elements.
 */
static inline float FusionVectorSum(const FusionVector vector) {
    return vector.axis.x + vector.axis.y + vector.axis.z;
}

/**
 * @brief Returns the multiplication of a vector by a scalar.
 * @param vector Vector.
 * @param scalar Scalar.
 * @return Multiplication of a vector by a scalar.
 */
static inline FusionVector FusionVectorMultiplyScalar(const FusionVector vector, const float scalar) {
    const FusionVector result = {.axis = {
            .x = vector.axis.x * scalar,
            .y = vector.axis.y * scalar,
            .z = vector.axis.z * scalar,
    }};
    return result;
}

/**
 * @brief Returns the multiplication of a vector by a scalar.
 * @param vector Vector.
 * @param scalar Scalar.
 * @return Multiplication of a vector by a scalar.
 */
static inline FusionVector FusionVectorMultiplyScalarDouble(const FusionVectorDouble vector, const float scalar) {
    const FusionVector result = {.axis = {
            .x = (float)vector.axis.x * scalar,
            .y = (float)vector.axis.y * scalar,
            .z = (float)vector.axis.z * scalar,
    }};
    return result;
}

/**
 * @brief Calculates the Hadamard product (element-wise multiplication).
 * @param vectorA Vector A.
 * @param vectorB Vector B.
 * @return Hadamard product.
 */
static inline FusionVector FusionVectorHadamardProduct(const FusionVector vectorA, const FusionVector vectorB) {
    const FusionVector result = {.axis = {
            .x = vectorA.axis.x * vectorB.axis.x,
            .y = vectorA.axis.y * vectorB.axis.y,
            .z = vectorA.axis.z * vectorB.axis.z,
    }};
    return result;
}

/**
 * @brief Returns the cross product.
 * @param vectorA Vector A.
 * @param vectorB Vector B.
 * @return Cross product.
 */
static inline FusionVector FusionVectorCrossProduct(const FusionVector vectorA, const FusionVector vectorB) {
#define A vectorA.axis
#define B vectorB.axis
    const FusionVector result = {.axis = {
            .x = A.y * B.z - A.z * B.y,
            .y = A.z * B.x - A.x * B.z,
            .z = A.x * B.y - A.y * B.x,
    }};
    return result;
#undef A
#undef B
}

/**
 * @brief Returns the vector magnitude squared.
 * @param vector Vector.
 * @return Vector magnitude squared.
 */
static inline float FusionVectorMagnitudeSquared(const FusionVector vector) {
    return FusionVectorSum(FusionVectorHadamardProduct(vector, vector));
}

/**
 * @brief Returns the vector magnitude.
 * @param vector Vector.
 * @return Vector magnitude.
 */
static inline float FusionVectorMagnitude(const FusionVector vector) {
    return sqrtf(FusionVectorMagnitudeSquared(vector));
}

/**
 * @brief Returns the normalised vector.
 * @param vector Vector.
 * @return Normalised vector.
 */
static inline FusionVector FusionVectorNormalise(const FusionVector vector) {
#ifdef FUSION_USE_NORMAL_SQRT
    const float magnitudeReciprocal = 1.0f / sqrtf(FusionVectorMagnitudeSquared(vector));
#else
    const float magnitudeReciprocal = FusionFastInverseSqrt(FusionVectorMagnitudeSquared(vector));
#endif
    return FusionVectorMultiplyScalar(vector, magnitudeReciprocal);
}

//------------------------------------------------------------------------------
// Inline functions - Quaternion operations

/**
 * @brief Returns the sum of two quaternions.
 * @param quaternionA Quaternion A.
 * @param quaternionB Quaternion B.
 * @return Sum of two quaternions.
 */
static inline FusionQuaternion FusionQuaternionAdd(const FusionQuaternion quaternionA, const FusionQuaternion quaternionB) {
    const FusionQuaternion result = {.element = {
            .w = quaternionA.element.w + quaternionB.element.w,
            .x = quaternionA.element.x + quaternionB.element.x,
            .y = quaternionA.element.y + quaternionB.element.y,
            .z = quaternionA.element.z + quaternionB.element.z,
    }};
    return result;
}

/**
 * @brief Returns the multiplication of two quaternions.
 * @param quaternionA Quaternion A (to be post-multiplied).
 * @param quaternionB Quaternion B (to be pre-multiplied).
 * @return Multiplication of two quaternions.
 */
static inline FusionQuaternion FusionQuaternionMultiply(const FusionQuaternion quaternionA, const FusionQuaternion quaternionB) {
#define A quaternionA.element
#define B quaternionB.element
    const FusionQuaternion result = {.element = {
            .w = A.w * B.w - A.x * B.x - A.y * B.y - A.z * B.z,
            .x = A.w * B.x + A.x * B.w + A.y * B.z - A.z * B.y,
            .y = A.w * B.y - A.x * B.z + A.y * B.w + A.z * B.x,
            .z = A.w * B.z + A.x * B.y - A.y * B.x + A.z * B.w,
    }};
    return result;
#undef A
#undef B
}

/**
 * @brief Returns the multiplication of a quaternion with a vector.  This is a
 * normal quaternion multiplication where the vector is treated a
 * quaternion with a W element value of zero.  The quaternion is post-
 * multiplied by the vector.
 * @param quaternion Quaternion.
 * @param vector Vector.
 * @return Multiplication of a quaternion with a vector.
 */
static inline FusionQuaternion FusionQuaternionMultiplyVector(const FusionQuaternion quaternion, const FusionVector vector) {
#define Q quaternion.element
#define V vector.axis
    const FusionQuaternion result = {.element = {
            .w = -Q.x * V.x - Q.y * V.y - Q.z * V.z,
            .x = Q.w * V.x + Q.y * V.z - Q.z * V.y,
            .y = Q.w * V.y - Q.x * V.z + Q.z * V.x,
            .z = Q.w * V.z + Q.x * V.y - Q.y * V.x,
    }};
    return result;
#undef Q
#undef V
}

/**
 * @brief Returns the normalised quaternion.
 * @param quaternion Quaternion.
 * @return Normalised quaternion.
 */
static inline FusionQuaternion FusionQuaternionNormalise(const FusionQuaternion quaternion) {
#define Q quaternion.element
#ifdef FUSION_USE_NORMAL_SQRT
    const float magnitudeReciprocal = 1.0f / sqrtf(Q.w * Q.w + Q.x * Q.x + Q.y * Q.y + Q.z * Q.z);
#else
    const float magnitudeReciprocal = FusionFastInverseSqrt(Q.w * Q.w + Q.x * Q.x + Q.y * Q.y + Q.z * Q.z);
#endif
    const FusionQuaternion result = {.element = {
            .w = Q.w * magnitudeReciprocal,
            .x = Q.x * magnitudeReciprocal,
            .y = Q.y * magnitudeReciprocal,
            .z = Q.z * magnitudeReciprocal,
    }};
    return result;
#undef Q
}

//------------------------------------------------------------------------------
// Inline functions - Matrix operations

/**
 * @brief Returns the multiplication of a matrix with a vector.
 * @param matrix Matrix.
 * @param vector Vector.
 * @return Multiplication of a matrix with a vector.
 */
static inline FusionVector FusionMatrixMultiplyVector(const FusionMatrix matrix, const FusionVector vector) {
#define R matrix.element
    const FusionVector result = {.axis = {
            .x = R.xx * vector.axis.x + R.xy * vector.axis.y + R.xz * vector.axis.z,
            .y = R.yx * vector.axis.x + R.yy * vector.axis.y + R.yz * vector.axis.z,
            .z = R.zx * vector.axis.x + R.zy * vector.axis.y + R.zz * vector.axis.z,
    }};
    return result;
#undef R
}

/**
 * @brief Returns the multiplication of a matrix with a vector.
 * @param matrix Matrix.
 * @param vector Vector.
 * @return Multiplication of a matrix with a vector.
 */
static inline FusionVectorDouble FusionMatrixMultiplyVectorDouble(const FusionMatrix matrix, const FusionVector vector) {
#define R matrix.element
    const FusionVectorDouble result = {.axis = {
            .x = R.xx * vector.axis.x + R.xy * vector.axis.y + R.xz * vector.axis.z,
            .y = R.yx * vector.axis.x + R.yy * vector.axis.y + R.yz * vector.axis.z,
            .z = R.zx * vector.axis.x + R.zy * vector.axis.y + R.zz * vector.axis.z,
    }};
    return result;
#undef R
}

/**
 * @brief Returns the transpose of a matrix.
 * @param matrix Matrix.
 * @return Transpose of a matrix.
 */
static inline FusionMatrix FusionMatrixTranspose(const FusionMatrix matrix) {
#define R matrix.element
    const FusionMatrix result = { .element = {
            .xx = R.xx,
            .xy = R.yx,
            .xz = R.zx,
            .yx = R.xy,
            .yy = R.yy,
            .yz = R.zy,
            .zx = R.xz,
            .zy = R.yz, 
            .zz = R.zz,
    }};
    return result;
#undef R
}

/**
 * @brief Returns the inverse of a matrix.
 * @param matrix Matrix.
 * @return Inverse of a matrix.
 */
static inline FusionMatrix FusionMatrixInverse(const FusionMatrix matrix) {
#define R matrix.element
    const FusionMatrix adjunt_T = { .element = {
        .xx = (R.yy * R.zz)-(R.yz * R.zy),
        .xy = (R.xz * R.zy)-(R.xy * R.zz), //-((R.xy * R.zz) - (R.xz * R.zy)),
        .xz = (R.xy * R.yz)-(R.xz * R.yy),
        .yx = (R.yz * R.zx)-(R.yx * R.zz), //-((R.yx * R.zz) - (R.yz * R.zx)),
        .yy = (R.xx * R.zz)-(R.xz * R.zx),
        .yz = (R.xz * R.yx)-(R.xx * R.yz), //-((R.xx * R.yz) - (R.xz * R.yx)),
        .zx = (R.yx * R.zy)-(R.yy * R.zx),
        .zy = (R.xy * R.zx)-(R.xx * R.zy), //-((R.xx * R.zy) - (R.xy * R.zx)),
        .zz = (R.xx * R.yy)-(R.xy * R.yx),
    }};
    const double determinant = R.xx * adjunt_T.element.xx + R.xy * adjunt_T.element.yx + R.xz * adjunt_T.element.zx;
    const FusionMatrix inverse = { .element = {
        .xx = adjunt_T.element.xx / (float)determinant,
        .xy = adjunt_T.element.xy / (float)determinant,
        .xz = adjunt_T.element.xz / (float)determinant,
        .yx = adjunt_T.element.yx / (float)determinant,
        .yy = adjunt_T.element.yy / (float)determinant,
        .yz = adjunt_T.element.yz / (float)determinant,
        .zx = adjunt_T.element.zx / (float)determinant,
        .zy = adjunt_T.element.zy / (float)determinant,
        .zz = adjunt_T.element.zz / (float)determinant,
    }};
    return inverse;
#undef R
}

/**
 * @brief Returns the sum of twp matrixes.
 * @param A_matrix Matrix.
 * @param B_matrix Matrix.
 * @return Sum of two matrixes.
 */
static inline FusionMatrix FusionMatrixSum(const FusionMatrix A_matrix, const FusionMatrix B_matrix) {
#define A A_matrix.element
#define B A_matrix.element
    const FusionMatrix Sum = { .element = {
        .xx = A.xx + B.xx,
        .xy = A.xy + B.xy,
        .xz = A.xz + B.xz,
        .yx = A.yx + B.yx,
        .yy = A.yy + B.yy,
        .yz = A.yz + B.yz,
        .zx = A.zx + B.zx,
        .zy = A.zy + B.zy,
        .zz = A.zz + B.zz,
    }};
    return Sum;
#undef A
#undef B
}

/**
 * @brief Returns the subtract of two matrixes.
 * @param A_matrix Matrix.
 * @param B_matrix Matrix.
 * @return A - B matrix.
 */
static inline FusionMatrix FusionMatrixSubtract(const FusionMatrix A_matrix, const FusionMatrix B_matrix) {
#define A A_matrix.element
#define B A_matrix.element
    const FusionMatrix Sum = { .element = {
        .xx = A.xx - B.xx,
        .xy = A.xy - B.xy,
        .xz = A.xz - B.xz,
        .yx = A.yx - B.yx,
        .yy = A.yy - B.yy,
        .yz = A.yz - B.yz,
        .zx = A.zx - B.zx,
        .zy = A.zy - B.zy,
        .zz = A.zz - B.zz,
    }};
    return Sum;
#undef A
#undef B
}

/**
 * @brief Returns the sum of twp matrixes.
 * @param A_matrix Matrix.
 * @param B_matrix Matrix.
 * @return Sum of two matrixes.
 */
static inline FusionMatrix FusionMatrixMult(const FusionMatrix A_matrix, const FusionMatrix B_matrix) {
#define A A_matrix.element
#define B A_matrix.element
    const FusionMatrix Mult = { .element = {
        .xx = A.xx * B.xx + A.xy * B.yx + A.xz * B.zx,
        .xy = A.xx * B.xy + A.xy * B.yy + A.xz * B.zy,
        .xz = A.xx * B.xz + A.xy * B.yz + A.xz * B.zz,
        .yx = A.yx * B.xx + A.yy * B.yx + A.yz * B.zx,
        .yy = A.yx * B.xy + A.yy * B.yy + A.yz * B.zy,
        .yz = A.yx * B.xz + A.yy * B.yz + A.yz * B.zz,
        .zx = A.zx * B.xx + A.zy * B.yx + A.zz * B.zx,
        .zy = A.zx * B.xy + A.zy * B.yy + A.zz * B.zy,
        .zz = A.zx * B.xz + A.zy * B.yz + A.zz * B.zz,
    }};
    return Mult;
#undef A
#undef B
}

//------------------------------------------------------------------------------
// Inline functions - Conversion operations

/**
 * @brief Converts a quaternion to a rotation matrix.
 * @param quaternion Quaternion.
 * @return Rotation matrix.
 */
static inline FusionMatrix FusionQuaternionToMatrix(const FusionQuaternion quaternion) {
#define Q quaternion.element
    const float qwqw = Q.w * Q.w; // calculate common terms to avoid repeated operations
    const float qwqx = Q.w * Q.x;
    const float qwqy = Q.w * Q.y;
    const float qwqz = Q.w * Q.z;
    const float qxqy = Q.x * Q.y;
    const float qxqz = Q.x * Q.z;
    const float qyqz = Q.y * Q.z;
    const FusionMatrix matrix = {.element = {
            .xx = 2.0f * (qwqw - 0.5f + Q.x * Q.x),
            .xy = 2.0f * (qxqy - qwqz),
            .xz = 2.0f * (qxqz + qwqy),
            .yx = 2.0f * (qxqy + qwqz),
            .yy = 2.0f * (qwqw - 0.5f + Q.y * Q.y),
            .yz = 2.0f * (qyqz - qwqx),
            .zx = 2.0f * (qxqz - qwqy),
            .zy = 2.0f * (qyqz + qwqx),
            .zz = 2.0f * (qwqw - 0.5f + Q.z * Q.z),
    }};
    return matrix;
#undef Q
}

/**
 * @brief Converts a quaternion to ZYX Euler angles in degrees.
 * @param quaternion Quaternion.
 * @return Euler angles in degrees.
 */
static inline FusionEuler FusionQuaternionToEuler(const FusionQuaternion quaternion) {
#define Q quaternion.element
    const float halfMinusQySquared = 0.5f - Q.y * Q.y; // calculate common terms to avoid repeated operations
    const FusionEuler euler = {.angle = {
            .roll = FusionRadiansToDegreesf(atan2f(Q.w * Q.x + Q.y * Q.z, halfMinusQySquared - Q.x * Q.x)),
            .pitch = FusionRadiansToDegreesf(FusionAsin(2.0f * (Q.w * Q.y - Q.z * Q.x))),
            .yaw = FusionRadiansToDegreesf(atan2f(Q.w * Q.z + Q.x * Q.y, halfMinusQySquared - Q.z * Q.z)),
    }};
    return euler;
#undef Q
}

static inline FusionVector FusionQuaternionAngularVelocity(const FusionQuaternion q1, const FusionQuaternion q2, const float deltaTime) {
    FusionVector angular = { .axis = {
        .x = (q1.array[0]*q2.array[1] - q1.array[1]*q2.array[0] - q1.array[2]*q2.array[3] + q1.array[3]*q2.array[2]) * (2.0f / deltaTime),
        .y = (q1.array[0]*q2.array[2] + q1.array[1]*q2.array[3] - q1.array[2]*q2.array[0] - q1.array[3]*q2.array[1]) * (2.0f / deltaTime),
        .z = (q1.array[0]*q2.array[3] - q1.array[1]*q2.array[2] + q1.array[2]*q2.array[1] - q1.array[3]*q2.array[0]) * (2.0f / deltaTime)
    }};
    return angular;
}

#endif
//------------------------------------------------------------------------------
// End of file
