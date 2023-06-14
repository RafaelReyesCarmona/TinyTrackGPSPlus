#include "vector_and_quaternion.h"

//--------------------------------------------------------------------------------
bool is_approx(float val_1, float val_2, float tol){
  return(abs(val_1-val_2)<tol);
}

//--------------------------------------------------------------------------------
Quaternion::Quaternion(float q0, float q1, float q2, float q3):
  q0{q0}, q1{q1}, q2{q2}, q3{q3}
  {}

Quaternion::Quaternion(Quaternion const & quat_in):
  q0{quat_in.q0}, q1{quat_in.q1}, q2{quat_in.q2}, q3{quat_in.q3}
  {}

Quaternion::Quaternion(void):
  q0{0}, q1{0}, q2{0}, q3{0}
  {}

void Quaternion::copy(Quaternion const & quat_in){
  q0 = quat_in.q0;
  q1 = quat_in.q1;
  q2 = quat_in.q2;
  q3 = quat_in.q3;
}

void Quaternion::conj(void){
  q0 =  q0;
  q1 = -q1;
  q2 = -q2;
  q3 = -q3;
}

float Quaternion::norm(void) const {
  float res = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);
  return res;
}

float Quaternion::norm_squared(void) const {
  float res = q0*q0 + q1*q1 + q2*q2 + q3*q3;
  return res;
}

bool Quaternion::is_normed(float tol) const {
  return ((this->norm_squared() - 1) < tol);
}

void Quaternion::set(float q0, float q1, float q2, float q3){
  this->q0 = q0;
  this->q1 = q1;
  this->q2 = q2;
  this->q3 = q3;
}

bool Quaternion::operator==(Quaternion const & quat_in){
  bool equal_content = (
    (abs(q0 - quat_in.q0) < tol) &&
    (abs(q1 - quat_in.q1) < tol) &&
    (abs(q2 - quat_in.q2) < tol)
  );
  return equal_content;
}

//--------------------------------------------------------------------------------
Vector::Vector(float v0, float v1, float v2):
  v0{v0}, v1{v1}, v2{v2}
  {}

Vector::Vector(Vector const & vect_in):
  v0{vect_in.v0}, v1{vect_in.v1}, v2{vect_in.v2}
  {}

Vector::Vector(void):
  v0{0}, v1{0}, v2{0}
  {}

void Vector::copy(Vector const & vect_in){
  v0 = vect_in.v0;
  v1 = vect_in.v1;
  v2 = vect_in.v2;
}

void Vector::add(Vector const & vect_in){
  v0 += vect_in.v0;
  v1 += vect_in.v1;
  v2 += vect_in.v2;
}

void Vector::scale(float const scale){
  v0 *= scale;
  v1 *= scale;
  v2 *= scale;
}

void Vector::set(float v0, float v1, float v2){
  this->v0 = v0;
  this->v1 = v1;
  this->v2 = v2;
}

float Vector::norm(void) const{
  return(sqrt(v0*v0 + v1*v1 + v2*v2));
}

float Vector::norm_squared(void) const{
  return(v0*v0 + v1*v1 + v2*v2);
}

bool Vector::is_normed(void) const{
  return(is_approx(this->norm_squared(), 1.0f));
}

bool Vector::operator==(Vector const & vect_in){
  bool equal_content = ( 
    (abs(v0 - vect_in.v0) < tol) &&
    (abs(v1 - vect_in.v1) < tol) &&
    (abs(v2 - vect_in.v2) < tol)
  );
  return equal_content;
}

//--------------------------------------------------------------------------------
void print(Quaternion const & quat_in, bool println){
  Serial.print(F("quat: scal = "));
  Serial.print(quat_to_scalar_part(quat_in));
  Serial.print(F(" | "));

  Vector vect_part {0, 0, 0};
  quat_to_vect_part(quat_in, vect_part);
  print(vect_part, false);

  if (println){
    Serial.println();
  }
}

void print(Vector const & vect_in, bool println){
  Serial.print(F("vect = [ "));
  Serial.print(vect_in.v0);
  Serial.print(F(", "));
  Serial.print(vect_in.v1);
  Serial.print(F(", "));
  Serial.print(vect_in.v2);
  Serial.print(F(" ]"));

  if (println){
    Serial.println();
  }
}

//--------------------------------------------------------------------------------
float vect_norm_square(Vector const & vect_in){
  float res = 
    vect_in.v0 * vect_in.v0 +
    vect_in.v1 * vect_in.v1 +
    vect_in.v2 * vect_in.v2;
  return res;
}

float vect_dot(Vector const & vect_1, Vector const & vect_2){
  float res = 
    vect_1.v0 * vect_2.v0 +
    vect_1.v1 * vect_2.v1 +
    vect_1.v2 * vect_2.v2;
  return res;
}

void vect_cross(Vector const & vect_1, Vector const & vect_2, Vector & vect_out){
  vect_out.v0 =  vect_1.v1 * vect_2.v2 - vect_1.v2 * vect_2.v1;
  vect_out.v1 = -vect_1.v0 * vect_2.v2 + vect_1.v2 * vect_2.v0;
  vect_out.v2 =  vect_1.v0 * vect_2.v1 - vect_1.v1 * vect_2.v0;
}

void vect_add(Vector const & vect_1, Vector const & vect_2, Vector & vect_out){
  vect_out.v0 = vect_1.v0 + vect_2.v0;
  vect_out.v1 = vect_1.v1 + vect_2.v1;
  vect_out.v2 = vect_1.v2 + vect_2.v2;
}

void vect_scale(Vector const & vect_in, float const scale, Vector & vect_out){
  vect_out.v0 = vect_in.v0 * scale;
  vect_out.v1 = vect_in.v1 * scale;
  vect_out.v2 = vect_in.v2 * scale;
}

//--------------------------------------------------------------------------------
void quat_conj(Quaternion const & quat_in, Quaternion & quat_out){
  quat_out.q0 =   quat_in.q0;
  quat_out.q1 = - quat_in.q1;
  quat_out.q2 = - quat_in.q2;
  quat_out.q3 = - quat_in.q3;
}

void quat_prod(Quaternion const & quat_1, Quaternion const & quat_2, Quaternion & quat_out){
    quat_out.q0 = quat_1.q0 * quat_2.q0 - quat_1.q1 * quat_2.q1 - quat_1.q2 * quat_2.q2 - quat_1.q3 * quat_2.q3;
    quat_out.q1 = quat_1.q0 * quat_2.q1 + quat_1.q1 * quat_2.q0 + quat_1.q2 * quat_2.q3 - quat_1.q3 * quat_2.q2;
    quat_out.q2 = quat_1.q0 * quat_2.q2 - quat_1.q1 * quat_2.q3 + quat_1.q2 * quat_2.q0 + quat_1.q3 * quat_2.q1;
    quat_out.q3 = quat_1.q0 * quat_2.q3 + quat_1.q1 * quat_2.q2 - quat_1.q2 * quat_2.q1 + quat_1.q3 * quat_2.q0;
}

//--------------------------------------------------------------------------------
void vect_to_quat(Vector const & vect_in, Quaternion & quat_out){
  quat_out.q0 = 0;
  quat_out.q1 = vect_in.v0;
  quat_out.q2 = vect_in.v1;
  quat_out.q3 = vect_in.v2;
}

bool quat_to_vect(Quaternion const & quat_in, Vector & vect_out, float tol){
  vect_out.v0 = quat_in.q1;
  vect_out.v1 = quat_in.q2;
  vect_out.v2 = quat_in.q3;

  if (abs(quat_in.q0) > tol){
    return false;
  }

  return true;
}

void quat_to_vect_part(Quaternion const & quat_in, Vector & vect_out){
  vect_out.v0 = quat_in.q1;
  vect_out.v1 = quat_in.q2;
  vect_out.v2 = quat_in.q3;
}

float quat_to_scalar_part(Quaternion const & quat_in){
  float res = quat_in.q0;
  return res;
}

bool rot_theta_normed_axis_to_rot_quat(float const rot_theta_rad, Vector const & normed_rot_axis, Quaternion & quat_out){
  float cos_theta = cos(rot_theta_rad);
  float sin_theta = sin(rot_theta_rad);
  quat_out.set(
    cos_theta,
    sin_theta * normed_rot_axis.v0, sin_theta * normed_rot_axis.v1, sin_theta * normed_rot_axis.v2
  );

  if (!normed_rot_axis.is_normed()){
    return false;
  }
  return true;
}

// using Rodriguez method: faster, see https://gamedev.stackexchange.com/questions/28395/rotating-vector3-by-a-quaternion
bool rotate_vect_by_quat_R(Vector const & vect_in, Quaternion const & quat_in, Vector & vect_out){
  Vector quat_vect_part{0, 0, 0};
  quat_to_vect_part(quat_in, quat_vect_part);

  float quat_scalar_part = quat_to_scalar_part(quat_in);

  // compute each term in our working vector
  Vector working_vector {0, 0, 0};

  // reset vect out
  vect_out.copy(working_vector);

  // part 1
  working_vector.copy(quat_vect_part);
  working_vector.scale(vect_dot(quat_vect_part, vect_in));
  working_vector.scale(2.0f);
  vect_add(working_vector, vect_out, vect_out);

  // part 2
  working_vector.copy(vect_in);
  working_vector.scale(quat_scalar_part*quat_scalar_part - vect_norm_square(quat_vect_part));
  vect_add(working_vector, vect_out, vect_out);

  // part 3
  vect_cross(quat_vect_part, vect_in, working_vector);
  working_vector.scale(2.0f * quat_scalar_part);
  vect_add(working_vector, vect_out, vect_out);

  if (!quat_in.is_normed()){
    return false;
  }

  return true;
}

// using plain quaternion method
bool rotate_vect_by_quat_Q(Vector const & vect_in, Quaternion const & quat_in, Vector & vect_out){
  Quaternion working_quaternion = Quaternion{0, 0, 0, 0};
  vect_to_quat(vect_in, working_quaternion);
  
  Quaternion input_conj_quaternion = Quaternion{quat_in};
  input_conj_quaternion.conj();

  quat_prod(quat_in, working_quaternion, working_quaternion);
  quat_prod(working_quaternion, input_conj_quaternion, working_quaternion);

  quat_to_vect(working_quaternion, vect_out);

  if (!quat_in.is_normed()){
    return false;
  }

  return true;
}

//--------------------------------------------------------------------------------

#undef __ASSERT_USE_STDERR

#include <assert.h>

// TODO: make this into proper tests
bool vect_quat_library_self_diagnostic(void){
  Serial.println(F("self diagnostic of the quaternions and vectors operations"));
  Serial.println(F("TODO: this should be made into proper tests"));

  // test vectors --------------------
  Vector v1 {1, 2, 3};
  Vector v2 {2, 4, 6};
  Vector v3 {2, 4, 6};
  Vector v4{};

  uassert(v2 == v3, "vect constr or == fails");
  uassert(v4 == Vector{0, 0, 0}, "vect constr or == fails");

  Serial.println(F("an example of vector print"));
  print(v1);

  v2.copy(v1);
  uassert(v2 == v1, "vect copy fails");

  v2.add(v1);
  uassert(v2 == v3, "vect add fails");

  v2.scale(0.5);
  uassert(v2 == v1, "vect scale fails");

  v1.set(2, 4, 6);
  uassert(v1 == v3, "vect set fails");

  uassert(is_approx(v3.norm(), sqrt(2*2 + 4*4 + 6*6)), "vect norm fails");

  uassert(is_approx(v3.norm_squared(), 2*2 + 4*4 + 6*6), "vect norm_squared fails");

  uassert(!v3.is_normed(), "vect is_normed fails");
  uassert(Vector{1.0, 0, 0}.is_normed(), "vect is_normed fails");

  // test quaternions --------------------
  Quaternion q1 {0, 0, 0, 0};
  Quaternion q2 {1, 2, 3, 4};
  Quaternion q3 {1, -2, -3, -4};
  Quaternion q4 {0.0, 1.0, 0.0, 0.0};

  Serial.println(F("an example of print quaternion"));
  print(q2);

  uassert(q1 == Quaternion{}, "quat constr or == fails");

  q1.copy(q2);
  uassert(q1 == q2, "quat copy fails");

  q1.conj();
  uassert(q1 == q3, "quat conj fails");

  uassert(abs(q2.norm() - sqrt(1*1 + 2*2 + 3*3 + 4*4)) < default_tol, "quat norm fails");

  uassert(is_approx(q2.norm_squared(), 1*1 + 2*2 + 3*3 + 4*4), "quat norm_squared fails");

  uassert(!q2.is_normed(), "quat is_normed fails");

  uassert(q4.is_normed(), "quat is_normed fails");

  q4.set(0.5, 0.5, 0.5, 0.5);
  uassert(q4 == Quaternion{0.5, 0.5, 0.5, 0.5});
  uassert(q4.is_normed(), "quat_is_normed fails");

  // test vector operations --------------------
  v1.set(1.0, 2.0, 3.0);
  uassert(is_approx(vect_norm_square(v1), 14.0), "vect_norm_square fails");

  v2.set(2.0, 3.0, 4.0);
  uassert(is_approx(vect_dot(v1, v2), 20), "vect_dot fails");

  v1.set(1, 0, 0);
  v2.set(1, 0, 0);
  v3.set(2, 3, 4);
  vect_cross(v1, v2, v3);
  uassert(v3 == Vector{}, "cross product 1 fails");
  
  v1.set(1, 0, 0);
  v2.set(0, 1, 0);
  vect_cross(v1, v2, v3);
  uassert(v3 == Vector{0, 0, 1}, "cross product 2 fails");

  v1.set(0, 1, 0);
  v2.set(1, 0, 0);
  vect_cross(v1, v2, v3);
  uassert(v3 == Vector{0, 0, -1}, "cross product 3 fails");

  v1.set(0, 1, 0);
  v2.set(0, 0, 1);
  vect_cross(v1, v2, v3);
  uassert(v3 == Vector{1, 0, 0}, "cross product 4 fails");

  v1.set(1, 0, 0);
  v2.set(0, 0, 1);
  vect_cross(v1, v2, v3);
  uassert(v3 == Vector{0, -1, 0}, "cross product 5 fails");

  v1.set(1, 0.1, 0.5);
  v2.set(2., 0.2, 1.5);
  vect_cross(v1, v2, v3);
  uassert(v3 == Vector{0.1*1.5-0.2*0.5, 0.5*2.0-1.0*1.5, 1*0.2-2*0.1}, "cross product 6 fails");

  v1.set(1, 2, 3);
  v2.set(4, 5, 6);
  vect_add(v1, v2, v3);
  uassert(v3 == Vector{5, 7, 9}, "vect add fails");

  vect_scale(v1, 0.5, v2);
  uassert(v2 == Vector{0.5, 1, 1.5}, "vect scale fails");

  // test quaternions and vectors operations --------------------
  bool return_flag;

  v1.set(1, 2, 3);
  q1.set(0, 0, 0, 0);
  vect_to_quat(v1, q1);
  uassert(q1 == Quaternion{0, 1, 2, 3}, "vect_to_quat fails");

  q1.set(0, 3, 4, 5);
  return_flag = quat_to_vect(q1, v1);
  uassert(((return_flag) && (v1 == Vector{3, 4, 5})), "quat_to_vect fails");

  q1.set(1, 4, 5, 6);
  return_flag = quat_to_vect(q1, v1);
  uassert(((!return_flag) && (v1 == Vector{4, 5, 6})), "quat_to_vect fails");

  q1.set(2.5, 1, 2, 3);
  quat_to_vect_part(q1, v1);
  uassert(v1 == Vector(1, 2, 3), "quat_to_vect_part fails");

  uassert(2.5 == quat_to_scalar_part(q1), "quat_to_scalar_part fails");

  bool flag_to_quat {false};

  float angle_45_as_rads = 45.0f * pi;
  float sqrt_1_over_3 = 0.5773502691896257f;
  v1.set(sqrt_1_over_3, sqrt_1_over_3, sqrt_1_over_3);
  flag_to_quat = rot_theta_normed_axis_to_rot_quat(angle_45_as_rads, v1, q1);
  uassert(
    (
      (flag_to_quat)
      &&
      (
        q1 == Quaternion(cos(angle_45_as_rads),
                         sin(angle_45_as_rads)*sqrt_1_over_3,
                         sin(angle_45_as_rads)*sqrt_1_over_3,
                         sin(angle_45_as_rads)*sqrt_1_over_3)
      )
    ),
    "rot_theta_normed_axis_to_rot_quat failed"
  );

  v1.set(sqrt_1_over_3, 0, sqrt_1_over_3);
  flag_to_quat = rot_theta_normed_axis_to_rot_quat(angle_45_as_rads, v1, q1);
  uassert(
    (
      (!flag_to_quat)
      &&
      (
        q1 == Quaternion(cos(angle_45_as_rads),
                         sin(angle_45_as_rads)*sqrt_1_over_3,
                         0,
                         sin(angle_45_as_rads)*sqrt_1_over_3)
      )
    ),
    "rot_theta_normed_axis_to_rot_quat failed"
  );

  //--------------------

  bool return_flag_rotate_R {false};
  bool return_flag_rotate_Q {false};

  // check identity with scaling --------------------
  v1.set(1, 0, 0);
  q1.set(1.5, 0, 0, 0);
  return_flag_rotate_R = rotate_vect_by_quat_R(v1, q1, v2);
  return_flag_rotate_Q = rotate_vect_by_quat_R(v1, q1, v3);
  uassert(((!return_flag_rotate_R) && (v2 == Vector{2.25, 0, 0})), "rotate_vect_by_quat_R 1 fails");
  uassert(((!return_flag_rotate_Q) && (v3 == Vector{2.25, 0, 0})), "rotate_vect_by_quat_Q 1 fails");

  v1.set(0, 1, 0);
  q1.set(1.5, 0, 0, 0);
  return_flag_rotate_R = rotate_vect_by_quat_R(v1, q1, v2);
  return_flag_rotate_Q = rotate_vect_by_quat_R(v1, q1, v3);
  uassert(((!return_flag_rotate_R) && (v2 == Vector{0, 2.25, 0})), "rotate_vect_by_quat_R 2 fails");
  uassert(((!return_flag_rotate_Q) && (v3 == Vector{0, 2.25, 0})), "rotate_vect_by_quat_Q 2 fails");

  v1.set(0, 0, 1);
  q1.set(1.5, 0, 0, 0);
  return_flag_rotate_R = rotate_vect_by_quat_R(v1, q1, v2);
  return_flag_rotate_Q = rotate_vect_by_quat_R(v1, q1, v3);
  uassert(((!return_flag_rotate_R) && (v2 == Vector{0, 0, 2.25})), "rotate_vect_by_quat_R 3 fails");
  uassert(((!return_flag_rotate_Q) && (v3 == Vector{0, 0, 2.25})), "rotate_vect_by_quat_Q 3 fails");

  // check identity --------------------
  v1.set(1, 0, 0);
  q1.set(1, 0, 0, 0);
  return_flag_rotate_R = rotate_vect_by_quat_R(v1, q1, v2);
  return_flag_rotate_Q = rotate_vect_by_quat_R(v1, q1, v3);
  uassert(((return_flag_rotate_R) && (v2 == Vector{1, 0, 0})), "rotate_vect_by_quat_R 4 fails");
  uassert(((return_flag_rotate_Q) && (v3 == Vector{1, 0, 0})), "rotate_vect_by_quat_Q 4 fails");

  v1.set(0, 1, 0);
  q1.set(1, 0, 0, 0);
  return_flag_rotate_R = rotate_vect_by_quat_R(v1, q1, v2);
  return_flag_rotate_Q = rotate_vect_by_quat_R(v1, q1, v3);
  uassert(((return_flag_rotate_R) && (v2 == Vector{0, 1, 0})), "rotate_vect_by_quat_R 4 fails");
  uassert(((return_flag_rotate_Q) && (v3 == Vector{0, 1, 0})), "rotate_vect_by_quat_Q 4 fails");

  v1.set(0, 0, 1);
  q1.set(1, 0, 0, 0);
  return_flag_rotate_R = rotate_vect_by_quat_R(v1, q1, v2);
  return_flag_rotate_Q = rotate_vect_by_quat_R(v1, q1, v3);
  uassert(((return_flag_rotate_R) && (v2 == Vector{0, 0, 1})), "rotate_vect_by_quat_R 4 fails");
  uassert(((return_flag_rotate_Q) && (v3 == Vector{0, 0, 1})), "rotate_vect_by_quat_Q 4 fails");

  // cos(45) = sin(45) = sqrt(2)/2
  float cs45 = sqrt(2.0f) / 2.0f;

  // check rotations of (1, 0, 0) --------------------
  v1.set(1, 0, 0);
  q1.set(cs45, cs45, 0, 0);
  return_flag_rotate_R = rotate_vect_by_quat_R(v1, q1, v2);
  return_flag_rotate_Q = rotate_vect_by_quat_R(v1, q1, v3);
  uassert(((return_flag_rotate_R) && (v2 == Vector{1, 0, 0})), "rotate_vect_by_quat_R 5 fails");
  uassert(((return_flag_rotate_Q) && (v3 == Vector{1, 0, 0})), "rotate_vect_by_quat_Q 5 fails");

  v1.set(1, 0, 0);
  q1.set(cs45, 0, cs45, 0);
  return_flag_rotate_R = rotate_vect_by_quat_R(v1, q1, v2);
  return_flag_rotate_Q = rotate_vect_by_quat_R(v1, q1, v3);
  uassert(((return_flag_rotate_R) && (v2 == Vector{0, 0, -1})), "rotate_vect_by_quat_R 6 fails");
  uassert(((return_flag_rotate_Q) && (v3 == Vector{0, 0, -1})), "rotate_vect_by_quat_Q 6 fails");

  v1.set(1, 0, 0);
  q1.set(cs45, 0, 0, cs45);
  return_flag_rotate_R = rotate_vect_by_quat_R(v1, q1, v2);
  return_flag_rotate_Q = rotate_vect_by_quat_R(v1, q1, v3);
  uassert(((return_flag_rotate_R) && (v2 == Vector{0, 1, 0})), "rotate_vect_by_quat_R 7 fails");
  uassert(((return_flag_rotate_Q) && (v3 == Vector{0, 1, 0})), "rotate_vect_by_quat_Q 7 fails");

  // check rotations of (0, 1, 0) --------------------
  v1.set(0, 1, 0);
  q1.set(cs45, cs45, 0, 0);
  return_flag_rotate_R = rotate_vect_by_quat_R(v1, q1, v2);
  return_flag_rotate_Q = rotate_vect_by_quat_R(v1, q1, v3);
  uassert(((return_flag_rotate_R) && (v2 == Vector{0, 0, 1})), "rotate_vect_by_quat_R 8 fails");
  uassert(((return_flag_rotate_Q) && (v3 == Vector{0, 0, 1})), "rotate_vect_by_quat_Q 8 fails");

  v1.set(0, 1, 0);
  q1.set(cs45, 0, cs45, 0);
  return_flag_rotate_R = rotate_vect_by_quat_R(v1, q1, v2);
  return_flag_rotate_Q = rotate_vect_by_quat_R(v1, q1, v3);
  uassert(((return_flag_rotate_R) && (v2 == Vector{0, 1, 0})), "rotate_vect_by_quat_R 9 fails");
  uassert(((return_flag_rotate_Q) && (v3 == Vector{0, 1, 0})), "rotate_vect_by_quat_Q 9 fails");

  v1.set(0, 1, 0);
  q1.set(cs45, 0, 0, cs45);
  return_flag_rotate_R = rotate_vect_by_quat_R(v1, q1, v2);
  return_flag_rotate_Q = rotate_vect_by_quat_R(v1, q1, v3);
  uassert(((return_flag_rotate_R) && (v2 == Vector{-1, 0, 0})), "rotate_vect_by_quat_R 10 fails");
  uassert(((return_flag_rotate_Q) && (v3 == Vector{-1, 0, 0})), "rotate_vect_by_quat_Q 10 fails");

  // check rotations of (0, 0, 1) --------------------
  v1.set(0, 0, 1);
  q1.set(cs45, cs45, 0, 0);
  return_flag_rotate_R = rotate_vect_by_quat_R(v1, q1, v2);
  return_flag_rotate_Q = rotate_vect_by_quat_R(v1, q1, v3);
  uassert(((return_flag_rotate_R) && (v2 == Vector{0, -1, 0})), "rotate_vect_by_quat_R 11 fails");
  uassert(((return_flag_rotate_Q) && (v3 == Vector{0, -1, 0})), "rotate_vect_by_quat_Q 11 fails");

  v1.set(0, 0, 1);
  q1.set(cs45, 0, cs45, 0);
  return_flag_rotate_R = rotate_vect_by_quat_R(v1, q1, v2);
  return_flag_rotate_Q = rotate_vect_by_quat_R(v1, q1, v3);
  uassert(((return_flag_rotate_R) && (v2 == Vector{1, 0, 0})), "rotate_vect_by_quat_R 12 fails");
  uassert(((return_flag_rotate_Q) && (v3 == Vector{1, 0, 0})), "rotate_vect_by_quat_Q 12 fails");

  v1.set(0, 0, 1);
  q1.set(cs45, 0, 0, cs45);
  return_flag_rotate_R = rotate_vect_by_quat_R(v1, q1, v2);
  return_flag_rotate_Q = rotate_vect_by_quat_R(v1, q1, v3);
  uassert(((return_flag_rotate_R) && (v2 == Vector{0, 0, 1})), "rotate_vect_by_quat_R 13 fails");
  uassert(((return_flag_rotate_Q) && (v3 == Vector{0, 0, 1})), "rotate_vect_by_quat_Q 13 fails");

  // check that agree on a few "random" rotations --------------------
  float rot_theta;

  // TODO: these are only partial tests; check that all ok with the boolean flags

  v1.set(0, 0, 1);
  rot_theta = 14.5f * pi / 180.0f;
  rot_theta_normed_axis_to_rot_quat(rot_theta, v1, q1);
  return_flag_rotate_R = rotate_vect_by_quat_R(v1, q1, v2);
  return_flag_rotate_Q = rotate_vect_by_quat_R(v1, q1, v3);
  uassert(v2 == v3, "rotate_vect_by_quat_R and return_flag_rotate_Q 1 do not agree");

  v1.set(0, 1, 0);
  rot_theta = 14.5f * pi / 180.0f;
  rot_theta_normed_axis_to_rot_quat(rot_theta, v1, q1);
  return_flag_rotate_R = rotate_vect_by_quat_R(v1, q1, v2);
  return_flag_rotate_Q = rotate_vect_by_quat_R(v1, q1, v3);
  uassert(v2 == v3, "rotate_vect_by_quat_R and return_flag_rotate_Q 1 do not agree");

  v1.set(0.5, 0.25, sqrt(1 - 0.5*0.5 - 0.25*0.25));
  rot_theta = 28.5f * pi / 180.0f;
  rot_theta_normed_axis_to_rot_quat(rot_theta, v1, q1);
  return_flag_rotate_R = rotate_vect_by_quat_R(v1, q1, v2);
  return_flag_rotate_Q = rotate_vect_by_quat_R(v1, q1, v3);
  uassert(v2 == v3, "rotate_vect_by_quat_R and return_flag_rotate_Q 1 do not agree");

  //--------------------------------------------------------------------------------

  Serial.println(F("diagnostic finished, vect and quat operations a success"));
  delay(500);

  return true;
}

