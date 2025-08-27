// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from indy_interfaces:msg/ServoDataArray.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__MSG__DETAIL__SERVO_DATA_ARRAY__STRUCT_H_
#define INDY_INTERFACES__MSG__DETAIL__SERVO_DATA_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'tx'
#include "indy_interfaces/msg/detail/servo_tx__struct.h"
// Member 'rx'
#include "indy_interfaces/msg/detail/servo_rx__struct.h"

/// Struct defined in msg/ServoDataArray in the package indy_interfaces.
typedef struct indy_interfaces__msg__ServoDataArray
{
  indy_interfaces__msg__ServoTx__Sequence tx;
  indy_interfaces__msg__ServoRx__Sequence rx;
} indy_interfaces__msg__ServoDataArray;

// Struct for a sequence of indy_interfaces__msg__ServoDataArray.
typedef struct indy_interfaces__msg__ServoDataArray__Sequence
{
  indy_interfaces__msg__ServoDataArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} indy_interfaces__msg__ServoDataArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INDY_INTERFACES__MSG__DETAIL__SERVO_DATA_ARRAY__STRUCT_H_
