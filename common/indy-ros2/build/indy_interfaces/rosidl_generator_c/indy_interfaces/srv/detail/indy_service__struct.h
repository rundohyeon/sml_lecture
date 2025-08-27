// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from indy_interfaces:srv/IndyService.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__SRV__DETAIL__INDY_SERVICE__STRUCT_H_
#define INDY_INTERFACES__SRV__DETAIL__INDY_SERVICE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/IndyService in the package indy_interfaces.
typedef struct indy_interfaces__srv__IndyService_Request
{
  int32_t data;
} indy_interfaces__srv__IndyService_Request;

// Struct for a sequence of indy_interfaces__srv__IndyService_Request.
typedef struct indy_interfaces__srv__IndyService_Request__Sequence
{
  indy_interfaces__srv__IndyService_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} indy_interfaces__srv__IndyService_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/IndyService in the package indy_interfaces.
typedef struct indy_interfaces__srv__IndyService_Response
{
  /// indicate successful run of service
  bool success;
  /// informational
  rosidl_runtime_c__String message;
} indy_interfaces__srv__IndyService_Response;

// Struct for a sequence of indy_interfaces__srv__IndyService_Response.
typedef struct indy_interfaces__srv__IndyService_Response__Sequence
{
  indy_interfaces__srv__IndyService_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} indy_interfaces__srv__IndyService_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INDY_INTERFACES__SRV__DETAIL__INDY_SERVICE__STRUCT_H_
