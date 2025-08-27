// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from indy_interfaces:msg/ServoRx.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__MSG__DETAIL__SERVO_RX__STRUCT_H_
#define INDY_INTERFACES__MSG__DETAIL__SERVO_RX__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/ServoRx in the package indy_interfaces.
typedef struct indy_interfaces__msg__ServoRx
{
  int32_t control_word;
  int32_t mode_op;
  int32_t target_pos;
  int32_t target_vel;
  int32_t target_tor;
} indy_interfaces__msg__ServoRx;

// Struct for a sequence of indy_interfaces__msg__ServoRx.
typedef struct indy_interfaces__msg__ServoRx__Sequence
{
  indy_interfaces__msg__ServoRx * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} indy_interfaces__msg__ServoRx__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INDY_INTERFACES__MSG__DETAIL__SERVO_RX__STRUCT_H_
