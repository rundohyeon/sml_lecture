// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from indy_interfaces:msg/ServoRx.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "indy_interfaces/msg/detail/servo_rx__rosidl_typesupport_introspection_c.h"
#include "indy_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "indy_interfaces/msg/detail/servo_rx__functions.h"
#include "indy_interfaces/msg/detail/servo_rx__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void indy_interfaces__msg__ServoRx__rosidl_typesupport_introspection_c__ServoRx_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  indy_interfaces__msg__ServoRx__init(message_memory);
}

void indy_interfaces__msg__ServoRx__rosidl_typesupport_introspection_c__ServoRx_fini_function(void * message_memory)
{
  indy_interfaces__msg__ServoRx__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember indy_interfaces__msg__ServoRx__rosidl_typesupport_introspection_c__ServoRx_message_member_array[5] = {
  {
    "control_word",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(indy_interfaces__msg__ServoRx, control_word),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mode_op",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(indy_interfaces__msg__ServoRx, mode_op),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "target_pos",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(indy_interfaces__msg__ServoRx, target_pos),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "target_vel",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(indy_interfaces__msg__ServoRx, target_vel),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "target_tor",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(indy_interfaces__msg__ServoRx, target_tor),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers indy_interfaces__msg__ServoRx__rosidl_typesupport_introspection_c__ServoRx_message_members = {
  "indy_interfaces__msg",  // message namespace
  "ServoRx",  // message name
  5,  // number of fields
  sizeof(indy_interfaces__msg__ServoRx),
  indy_interfaces__msg__ServoRx__rosidl_typesupport_introspection_c__ServoRx_message_member_array,  // message members
  indy_interfaces__msg__ServoRx__rosidl_typesupport_introspection_c__ServoRx_init_function,  // function to initialize message memory (memory has to be allocated)
  indy_interfaces__msg__ServoRx__rosidl_typesupport_introspection_c__ServoRx_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t indy_interfaces__msg__ServoRx__rosidl_typesupport_introspection_c__ServoRx_message_type_support_handle = {
  0,
  &indy_interfaces__msg__ServoRx__rosidl_typesupport_introspection_c__ServoRx_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_indy_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, indy_interfaces, msg, ServoRx)() {
  if (!indy_interfaces__msg__ServoRx__rosidl_typesupport_introspection_c__ServoRx_message_type_support_handle.typesupport_identifier) {
    indy_interfaces__msg__ServoRx__rosidl_typesupport_introspection_c__ServoRx_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &indy_interfaces__msg__ServoRx__rosidl_typesupport_introspection_c__ServoRx_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
