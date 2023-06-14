#ifndef QUATERNION_TOOLS
#define QUATERNION_TOOLS

#ifdef ARDUINO
  #include "Arduino.h"
#else
  #include "math.h"
  using namespace std;
#endif

#include "assert_tools.h"

//--------------------------------------------------------------------------------
constexpr float default_tol = 1.0e-4;
constexpr float pi = 3.141592653589793f;

bool is_approx(float val_1, float val_2, float tol=default_tol);

//------------------------------------------------------------------------
// Quaternion and Vector functions
// follow the note by J.Rabault, "A brief summary about quaternion use for describing rotations in 3D space", 2017.
// use additional formula:
// Rodriguez formula: https://gamedev.stackexchange.com/questions/28395/rotating-vector3-by-a-quaternion

//--------------------------------------------------------------------------------
class Vector{
  public:
    // constructor
    Vector(float v0, float v1, float v2);
    Vector(Vector const & vect_in);
    Vector(void);

    void copy(Vector const & vect_in);
    void add(Vector const & vect_in);
    void scale(float const scale);
    void set(float v0, float v1, float v2);
    float norm(void) const;
    float norm_squared(void) const;
    bool is_normed(void) const;
    bool operator==(Vector const & vect_in);

    // data members
    float v0;  // i component
    float v1;  // j component
    float v2;  // k component

    float tol = default_tol;
};

//--------------------------------------------------------------------------------
class Quaternion{
  public:
    // constructor
    Quaternion(float q0, float q1, float q2, float q3);
    Quaternion(Quaternion const & quat_in);
    Quaternion(void);

    void copy(Quaternion const & quat_in);
    void conj(void);
    float norm(void) const;
    float norm_squared(void) const;
    bool is_normed(float tol=default_tol) const;
    void set (float q0, float q1, float q2, float q3);
    bool operator==(Quaternion const & quat_in);
    
    // data members
    float q0;  // real component
    float q1;  // i component
    float q2;  // j component
    float q3;  // k component

    float tol = default_tol;
};

//--------------------------------------------------------------------------------
void print(Vector const & vect_in, bool println=true);
void print(Quaternion const & quat_in, bool println=true);

//--------------------------------------------------------------------------------
float vect_norm_square(Vector const & vect_in);
float vect_dot(Vector const & vect_1, Vector const & vect_2);
void vect_cross(Vector const & vect_1, Vector const & vect_2, Vector & vect_out);
void vect_add(Vector const & vect_1, Vector const & vect_2, Vector & vect_out);
void vect_scale(Vector const & vect_in, float const scale, Vector & vect_out);

//--------------------------------------------------------------------------------
void quat_conj(Quaternion const & quat_in, Quaternion & quat_out);
void quat_prod(Quaternion const & quat_1, Quaternion const & quat_2, Quaternion & quat_out);

//--------------------------------------------------------------------------------
void vect_to_quat(Vector const & vect_in, Quaternion & quat_out);
bool quat_to_vect(Quaternion const & quat_in, Vector & vect_out, float tol=default_tol);
void quat_to_vect_part(Quaternion const & quat_in, Vector & vect_out);
float quat_to_scalar_part(Quaternion const & quat_in);
bool rot_theta_normed_axis_to_rot_quat(float const rot_theta_rad, Vector const & normed_rot_axis, Quaternion & quat_out);
bool rotate_vect_by_quat_R(Vector const & vect_in, Quaternion const & quat_in, Vector & vect_out);  // using the Rodriguez formula: much faster
// TODO: put a depreciation warning
bool rotate_vect_by_quat_Q(Vector const & vect_in, Quaternion const & quat_in, Vector & vect_out);  // using the quaternions formula: slower

//--------------------------------------------------------------------------------
// TODO: move into some proper tests
bool vect_quat_library_self_diagnostic(void);

#endif

// TODO: change all function names expecting normed quats and vector to _normed_
// TODO: extend tests, fix missing tests on boolean flags
// TODO: make into an own library
// TODO: inspect API
