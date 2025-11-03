// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from indy_interfaces:msg/ServoRx.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__MSG__DETAIL__SERVO_RX__FUNCTIONS_H_
#define INDY_INTERFACES__MSG__DETAIL__SERVO_RX__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "indy_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "indy_interfaces/msg/detail/servo_rx__struct.h"

/// Initialize msg/ServoRx message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * indy_interfaces__msg__ServoRx
 * )) before or use
 * indy_interfaces__msg__ServoRx__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
bool
indy_interfaces__msg__ServoRx__init(indy_interfaces__msg__ServoRx * msg);

/// Finalize msg/ServoRx message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
void
indy_interfaces__msg__ServoRx__fini(indy_interfaces__msg__ServoRx * msg);

/// Create msg/ServoRx message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * indy_interfaces__msg__ServoRx__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
indy_interfaces__msg__ServoRx *
indy_interfaces__msg__ServoRx__create();

/// Destroy msg/ServoRx message.
/**
 * It calls
 * indy_interfaces__msg__ServoRx__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
void
indy_interfaces__msg__ServoRx__destroy(indy_interfaces__msg__ServoRx * msg);

/// Check for msg/ServoRx message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
bool
indy_interfaces__msg__ServoRx__are_equal(const indy_interfaces__msg__ServoRx * lhs, const indy_interfaces__msg__ServoRx * rhs);

/// Copy a msg/ServoRx message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
bool
indy_interfaces__msg__ServoRx__copy(
  const indy_interfaces__msg__ServoRx * input,
  indy_interfaces__msg__ServoRx * output);

/// Initialize array of msg/ServoRx messages.
/**
 * It allocates the memory for the number of elements and calls
 * indy_interfaces__msg__ServoRx__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
bool
indy_interfaces__msg__ServoRx__Sequence__init(indy_interfaces__msg__ServoRx__Sequence * array, size_t size);

/// Finalize array of msg/ServoRx messages.
/**
 * It calls
 * indy_interfaces__msg__ServoRx__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
void
indy_interfaces__msg__ServoRx__Sequence__fini(indy_interfaces__msg__ServoRx__Sequence * array);

/// Create array of msg/ServoRx messages.
/**
 * It allocates the memory for the array and calls
 * indy_interfaces__msg__ServoRx__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
indy_interfaces__msg__ServoRx__Sequence *
indy_interfaces__msg__ServoRx__Sequence__create(size_t size);

/// Destroy array of msg/ServoRx messages.
/**
 * It calls
 * indy_interfaces__msg__ServoRx__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
void
indy_interfaces__msg__ServoRx__Sequence__destroy(indy_interfaces__msg__ServoRx__Sequence * array);

/// Check for msg/ServoRx message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
bool
indy_interfaces__msg__ServoRx__Sequence__are_equal(const indy_interfaces__msg__ServoRx__Sequence * lhs, const indy_interfaces__msg__ServoRx__Sequence * rhs);

/// Copy an array of msg/ServoRx messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
bool
indy_interfaces__msg__ServoRx__Sequence__copy(
  const indy_interfaces__msg__ServoRx__Sequence * input,
  indy_interfaces__msg__ServoRx__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // INDY_INTERFACES__MSG__DETAIL__SERVO_RX__FUNCTIONS_H_
