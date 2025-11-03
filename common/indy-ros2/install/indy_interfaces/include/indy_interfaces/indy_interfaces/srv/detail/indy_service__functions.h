// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from indy_interfaces:srv/IndyService.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__SRV__DETAIL__INDY_SERVICE__FUNCTIONS_H_
#define INDY_INTERFACES__SRV__DETAIL__INDY_SERVICE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "indy_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "indy_interfaces/srv/detail/indy_service__struct.h"

/// Initialize srv/IndyService message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * indy_interfaces__srv__IndyService_Request
 * )) before or use
 * indy_interfaces__srv__IndyService_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
bool
indy_interfaces__srv__IndyService_Request__init(indy_interfaces__srv__IndyService_Request * msg);

/// Finalize srv/IndyService message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
void
indy_interfaces__srv__IndyService_Request__fini(indy_interfaces__srv__IndyService_Request * msg);

/// Create srv/IndyService message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * indy_interfaces__srv__IndyService_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
indy_interfaces__srv__IndyService_Request *
indy_interfaces__srv__IndyService_Request__create();

/// Destroy srv/IndyService message.
/**
 * It calls
 * indy_interfaces__srv__IndyService_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
void
indy_interfaces__srv__IndyService_Request__destroy(indy_interfaces__srv__IndyService_Request * msg);

/// Check for srv/IndyService message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
bool
indy_interfaces__srv__IndyService_Request__are_equal(const indy_interfaces__srv__IndyService_Request * lhs, const indy_interfaces__srv__IndyService_Request * rhs);

/// Copy a srv/IndyService message.
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
indy_interfaces__srv__IndyService_Request__copy(
  const indy_interfaces__srv__IndyService_Request * input,
  indy_interfaces__srv__IndyService_Request * output);

/// Initialize array of srv/IndyService messages.
/**
 * It allocates the memory for the number of elements and calls
 * indy_interfaces__srv__IndyService_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
bool
indy_interfaces__srv__IndyService_Request__Sequence__init(indy_interfaces__srv__IndyService_Request__Sequence * array, size_t size);

/// Finalize array of srv/IndyService messages.
/**
 * It calls
 * indy_interfaces__srv__IndyService_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
void
indy_interfaces__srv__IndyService_Request__Sequence__fini(indy_interfaces__srv__IndyService_Request__Sequence * array);

/// Create array of srv/IndyService messages.
/**
 * It allocates the memory for the array and calls
 * indy_interfaces__srv__IndyService_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
indy_interfaces__srv__IndyService_Request__Sequence *
indy_interfaces__srv__IndyService_Request__Sequence__create(size_t size);

/// Destroy array of srv/IndyService messages.
/**
 * It calls
 * indy_interfaces__srv__IndyService_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
void
indy_interfaces__srv__IndyService_Request__Sequence__destroy(indy_interfaces__srv__IndyService_Request__Sequence * array);

/// Check for srv/IndyService message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
bool
indy_interfaces__srv__IndyService_Request__Sequence__are_equal(const indy_interfaces__srv__IndyService_Request__Sequence * lhs, const indy_interfaces__srv__IndyService_Request__Sequence * rhs);

/// Copy an array of srv/IndyService messages.
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
indy_interfaces__srv__IndyService_Request__Sequence__copy(
  const indy_interfaces__srv__IndyService_Request__Sequence * input,
  indy_interfaces__srv__IndyService_Request__Sequence * output);

/// Initialize srv/IndyService message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * indy_interfaces__srv__IndyService_Response
 * )) before or use
 * indy_interfaces__srv__IndyService_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
bool
indy_interfaces__srv__IndyService_Response__init(indy_interfaces__srv__IndyService_Response * msg);

/// Finalize srv/IndyService message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
void
indy_interfaces__srv__IndyService_Response__fini(indy_interfaces__srv__IndyService_Response * msg);

/// Create srv/IndyService message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * indy_interfaces__srv__IndyService_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
indy_interfaces__srv__IndyService_Response *
indy_interfaces__srv__IndyService_Response__create();

/// Destroy srv/IndyService message.
/**
 * It calls
 * indy_interfaces__srv__IndyService_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
void
indy_interfaces__srv__IndyService_Response__destroy(indy_interfaces__srv__IndyService_Response * msg);

/// Check for srv/IndyService message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
bool
indy_interfaces__srv__IndyService_Response__are_equal(const indy_interfaces__srv__IndyService_Response * lhs, const indy_interfaces__srv__IndyService_Response * rhs);

/// Copy a srv/IndyService message.
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
indy_interfaces__srv__IndyService_Response__copy(
  const indy_interfaces__srv__IndyService_Response * input,
  indy_interfaces__srv__IndyService_Response * output);

/// Initialize array of srv/IndyService messages.
/**
 * It allocates the memory for the number of elements and calls
 * indy_interfaces__srv__IndyService_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
bool
indy_interfaces__srv__IndyService_Response__Sequence__init(indy_interfaces__srv__IndyService_Response__Sequence * array, size_t size);

/// Finalize array of srv/IndyService messages.
/**
 * It calls
 * indy_interfaces__srv__IndyService_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
void
indy_interfaces__srv__IndyService_Response__Sequence__fini(indy_interfaces__srv__IndyService_Response__Sequence * array);

/// Create array of srv/IndyService messages.
/**
 * It allocates the memory for the array and calls
 * indy_interfaces__srv__IndyService_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
indy_interfaces__srv__IndyService_Response__Sequence *
indy_interfaces__srv__IndyService_Response__Sequence__create(size_t size);

/// Destroy array of srv/IndyService messages.
/**
 * It calls
 * indy_interfaces__srv__IndyService_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
void
indy_interfaces__srv__IndyService_Response__Sequence__destroy(indy_interfaces__srv__IndyService_Response__Sequence * array);

/// Check for srv/IndyService message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_indy_interfaces
bool
indy_interfaces__srv__IndyService_Response__Sequence__are_equal(const indy_interfaces__srv__IndyService_Response__Sequence * lhs, const indy_interfaces__srv__IndyService_Response__Sequence * rhs);

/// Copy an array of srv/IndyService messages.
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
indy_interfaces__srv__IndyService_Response__Sequence__copy(
  const indy_interfaces__srv__IndyService_Response__Sequence * input,
  indy_interfaces__srv__IndyService_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // INDY_INTERFACES__SRV__DETAIL__INDY_SERVICE__FUNCTIONS_H_
