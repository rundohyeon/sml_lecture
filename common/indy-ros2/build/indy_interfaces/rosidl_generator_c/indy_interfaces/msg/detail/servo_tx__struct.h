// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from indy_interfaces:msg/ServoTx.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__MSG__DETAIL__SERVO_TX__STRUCT_H_
#define INDY_INTERFACES__MSG__DETAIL__SERVO_TX__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'status_word'
// Member 'mode_op_disp'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/ServoTx in the package indy_interfaces.
typedef struct indy_interfaces__msg__ServoTx
{
  rosidl_runtime_c__String status_word;
  rosidl_runtime_c__String mode_op_disp;
  int32_t actual_pos;
  int32_t actual_vel;
  int32_t actual_tor;
} indy_interfaces__msg__ServoTx;

// Struct for a sequence of indy_interfaces__msg__ServoTx.
typedef struct indy_interfaces__msg__ServoTx__Sequence
{
  indy_interfaces__msg__ServoTx * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} indy_interfaces__msg__ServoTx__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INDY_INTERFACES__MSG__DETAIL__SERVO_TX__STRUCT_H_
