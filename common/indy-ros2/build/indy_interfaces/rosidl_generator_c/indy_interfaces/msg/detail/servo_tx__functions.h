// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from indy_interfaces:msg/ServoTx.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__MSG__DETAIL__SERVO_TX__FUNCTIONS_H_
#define INDY_INTERFACES__MSG__DETAIL__SERVO_TX__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "indy_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "indy_interfaces/msg/detail/servo_tx__struct.h"

/// Initialize msg/ServoTx message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * indy_interfaces__msg__ServoTx
 * )) before or use
 * indy_interfaces__msg__ServoTx__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
bool
indy_interfaces__msg__ServoTx__init(indy_interfaces__msg__ServoTx * msg);

/// Finalize msg/ServoTx message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
void
indy_interfaces__msg__ServoTx__fini(indy_interfaces__msg__ServoTx * msg);

/// Create msg/ServoTx message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * indy_interfaces__msg__ServoTx__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
indy_interfaces__msg__ServoTx *
indy_interfaces__msg__ServoTx__create();

/// Destroy msg/ServoTx message.
/**
 * It calls
 * indy_interfaces__msg__ServoTx__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
void
indy_interfaces__msg__ServoTx__destroy(indy_interfaces__msg__ServoTx * msg);

/// Check for msg/ServoTx message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
bool
indy_interfaces__msg__ServoTx__are_equal(const indy_interfaces__msg__ServoTx * lhs, const indy_interfaces__msg__ServoTx * rhs);

/// Copy a msg/ServoTx message.
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
indy_interfaces__msg__ServoTx__copy(
  const indy_interfaces__msg__ServoTx * input,
  indy_interfaces__msg__ServoTx * output);

/// Initialize array of msg/ServoTx messages.
/**
 * It allocates the memory for the number of elements and calls
 * indy_interfaces__msg__ServoTx__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
bool
indy_interfaces__msg__ServoTx__Sequence__init(indy_interfaces__msg__ServoTx__Sequence * array, size_t size);

/// Finalize array of msg/ServoTx messages.
/**
 * It calls
 * indy_interfaces__msg__ServoTx__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
void
indy_interfaces__msg__ServoTx__Sequence__fini(indy_interfaces__msg__ServoTx__Sequence * array);

/// Create array of msg/ServoTx messages.
/**
 * It allocates the memory for the array and calls
 * indy_interfaces__msg__ServoTx__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
indy_interfaces__msg__ServoTx__Sequence *
indy_interfaces__msg__ServoTx__Sequence__create(size_t size);

/// Destroy array of msg/ServoTx messages.
/**
 * It calls
 * indy_interfaces__msg__ServoTx__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
void
indy_interfaces__msg__ServoTx__Sequence__destroy(indy_interfaces__msg__ServoTx__Sequence * array);

/// Check for msg/ServoTx message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
bool
indy_interfaces__msg__ServoTx__Sequence__are_equal(const indy_interfaces__msg__ServoTx__Sequence * lhs, const indy_interfaces__msg__ServoTx__Sequence * rhs);

/// Copy an array of msg/ServoTx messages.
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
indy_interfaces__msg__ServoTx__Sequence__copy(
  const indy_interfaces__msg__ServoTx__Sequence * input,
  indy_interfaces__msg__ServoTx__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // INDY_INTERFACES__MSG__DETAIL__SERVO_TX__FUNCTIONS_H_
