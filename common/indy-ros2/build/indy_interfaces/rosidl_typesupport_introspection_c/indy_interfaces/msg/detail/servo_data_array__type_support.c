// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from indy_interfaces:msg/ServoDataArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "indy_interfaces/msg/detail/servo_data_array__rosidl_typesupport_introspection_c.h"
#include "indy_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "indy_interfaces/msg/detail/servo_data_array__functions.h"
#include "indy_interfaces/msg/detail/servo_data_array__struct.h"


// Include directives for member types
// Member `tx`
#include "indy_interfaces/msg/servo_tx.h"
// Member `tx`
#include "indy_interfaces/msg/detail/servo_tx__rosidl_typesupport_introspection_c.h"
// Member `rx`
#include "indy_interfaces/msg/servo_rx.h"
// Member `rx`
#include "indy_interfaces/msg/detail/servo_rx__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__ServoDataArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  indy_interfaces__msg__ServoDataArray__init(message_memory);
}

void indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__ServoDataArray_fini_function(void * message_memory)
{
  indy_interfaces__msg__ServoDataArray__fini(message_memory);
}

size_t indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__size_function__ServoDataArray__tx(
  const void * untyped_member)
{
  const indy_interfaces__msg__ServoTx__Sequence * member =
    (const indy_interfaces__msg__ServoTx__Sequence *)(untyped_member);
  return member->size;
}

const void * indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__get_const_function__ServoDataArray__tx(
  const void * untyped_member, size_t index)
{
  const indy_interfaces__msg__ServoTx__Sequence * member =
    (const indy_interfaces__msg__ServoTx__Sequence *)(untyped_member);
  return &member->data[index];
}

void * indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__get_function__ServoDataArray__tx(
  void * untyped_member, size_t index)
{
  indy_interfaces__msg__ServoTx__Sequence * member =
    (indy_interfaces__msg__ServoTx__Sequence *)(untyped_member);
  return &member->data[index];
}

void indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__fetch_function__ServoDataArray__tx(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const indy_interfaces__msg__ServoTx * item =
    ((const indy_interfaces__msg__ServoTx *)
    indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__get_const_function__ServoDataArray__tx(untyped_member, index));
  indy_interfaces__msg__ServoTx * value =
    (indy_interfaces__msg__ServoTx *)(untyped_value);
  *value = *item;
}

void indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__assign_function__ServoDataArray__tx(
  void * untyped_member, size_t index, const void * untyped_value)
{
  indy_interfaces__msg__ServoTx * item =
    ((indy_interfaces__msg__ServoTx *)
    indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__get_function__ServoDataArray__tx(untyped_member, index));
  const indy_interfaces__msg__ServoTx * value =
    (const indy_interfaces__msg__ServoTx *)(untyped_value);
  *item = *value;
}

bool indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__resize_function__ServoDataArray__tx(
  void * untyped_member, size_t size)
{
  indy_interfaces__msg__ServoTx__Sequence * member =
    (indy_interfaces__msg__ServoTx__Sequence *)(untyped_member);
  indy_interfaces__msg__ServoTx__Sequence__fini(member);
  return indy_interfaces__msg__ServoTx__Sequence__init(member, size);
}

size_t indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__size_function__ServoDataArray__rx(
  const void * untyped_member)
{
  const indy_interfaces__msg__ServoRx__Sequence * member =
    (const indy_interfaces__msg__ServoRx__Sequence *)(untyped_member);
  return member->size;
}

const void * indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__get_const_function__ServoDataArray__rx(
  const void * untyped_member, size_t index)
{
  const indy_interfaces__msg__ServoRx__Sequence * member =
    (const indy_interfaces__msg__ServoRx__Sequence *)(untyped_member);
  return &member->data[index];
}

void * indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__get_function__ServoDataArray__rx(
  void * untyped_member, size_t index)
{
  indy_interfaces__msg__ServoRx__Sequence * member =
    (indy_interfaces__msg__ServoRx__Sequence *)(untyped_member);
  return &member->data[index];
}

void indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__fetch_function__ServoDataArray__rx(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const indy_interfaces__msg__ServoRx * item =
    ((const indy_interfaces__msg__ServoRx *)
    indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__get_const_function__ServoDataArray__rx(untyped_member, index));
  indy_interfaces__msg__ServoRx * value =
    (indy_interfaces__msg__ServoRx *)(untyped_value);
  *value = *item;
}

void indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__assign_function__ServoDataArray__rx(
  void * untyped_member, size_t index, const void * untyped_value)
{
  indy_interfaces__msg__ServoRx * item =
    ((indy_interfaces__msg__ServoRx *)
    indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__get_function__ServoDataArray__rx(untyped_member, index));
  const indy_interfaces__msg__ServoRx * value =
    (const indy_interfaces__msg__ServoRx *)(untyped_value);
  *item = *value;
}

bool indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__resize_function__ServoDataArray__rx(
  void * untyped_member, size_t size)
{
  indy_interfaces__msg__ServoRx__Sequence * member =
    (indy_interfaces__msg__ServoRx__Sequence *)(untyped_member);
  indy_interfaces__msg__ServoRx__Sequence__fini(member);
  return indy_interfaces__msg__ServoRx__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__ServoDataArray_message_member_array[2] = {
  {
    "tx",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(indy_interfaces__msg__ServoDataArray, tx),  // bytes offset in struct
    NULL,  // default value
    indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__size_function__ServoDataArray__tx,  // size() function pointer
    indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__get_const_function__ServoDataArray__tx,  // get_const(index) function pointer
    indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__get_function__ServoDataArray__tx,  // get(index) function pointer
    indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__fetch_function__ServoDataArray__tx,  // fetch(index, &value) function pointer
    indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__assign_function__ServoDataArray__tx,  // assign(index, value) function pointer
    indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__resize_function__ServoDataArray__tx  // resize(index) function pointer
  },
  {
    "rx",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(indy_interfaces__msg__ServoDataArray, rx),  // bytes offset in struct
    NULL,  // default value
    indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__size_function__ServoDataArray__rx,  // size() function pointer
    indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__get_const_function__ServoDataArray__rx,  // get_const(index) function pointer
    indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__get_function__ServoDataArray__rx,  // get(index) function pointer
    indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__fetch_function__ServoDataArray__rx,  // fetch(index, &value) function pointer
    indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__assign_function__ServoDataArray__rx,  // assign(index, value) function pointer
    indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__resize_function__ServoDataArray__rx  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__ServoDataArray_message_members = {
  "indy_interfaces__msg",  // message namespace
  "ServoDataArray",  // message name
  2,  // number of fields
  sizeof(indy_interfaces__msg__ServoDataArray),
  indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__ServoDataArray_message_member_array,  // message members
  indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__ServoDataArray_init_function,  // function to initialize message memory (memory has to be allocated)
  indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__ServoDataArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__ServoDataArray_message_type_support_handle = {
  0,
  &indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__ServoDataArray_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_indy_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, indy_interfaces, msg, ServoDataArray)() {
  indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__ServoDataArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, indy_interfaces, msg, ServoTx)();
  indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__ServoDataArray_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, indy_interfaces, msg, ServoRx)();
  if (!indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__ServoDataArray_message_type_support_handle.typesupport_identifier) {
    indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__ServoDataArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &indy_interfaces__msg__ServoDataArray__rosidl_typesupport_introspection_c__ServoDataArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
