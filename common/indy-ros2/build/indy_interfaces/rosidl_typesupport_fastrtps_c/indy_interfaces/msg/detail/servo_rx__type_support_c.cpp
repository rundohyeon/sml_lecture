// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from indy_interfaces:msg/ServoRx.idl
// generated code does not contain a copyright notice
#include "indy_interfaces/msg/detail/servo_rx__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "indy_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "indy_interfaces/msg/detail/servo_rx__struct.h"
#include "indy_interfaces/msg/detail/servo_rx__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _ServoRx__ros_msg_type = indy_interfaces__msg__ServoRx;

static bool _ServoRx__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _ServoRx__ros_msg_type * ros_message = static_cast<const _ServoRx__ros_msg_type *>(untyped_ros_message);
  // Field name: control_word
  {
    cdr << ros_message->control_word;
  }

  // Field name: mode_op
  {
    cdr << ros_message->mode_op;
  }

  // Field name: target_pos
  {
    cdr << ros_message->target_pos;
  }

  // Field name: target_vel
  {
    cdr << ros_message->target_vel;
  }

  // Field name: target_tor
  {
    cdr << ros_message->target_tor;
  }

  return true;
}

static bool _ServoRx__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _ServoRx__ros_msg_type * ros_message = static_cast<_ServoRx__ros_msg_type *>(untyped_ros_message);
  // Field name: control_word
  {
    cdr >> ros_message->control_word;
  }

  // Field name: mode_op
  {
    cdr >> ros_message->mode_op;
  }

  // Field name: target_pos
  {
    cdr >> ros_message->target_pos;
  }

  // Field name: target_vel
  {
    cdr >> ros_message->target_vel;
  }

  // Field name: target_tor
  {
    cdr >> ros_message->target_tor;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_indy_interfaces
size_t get_serialized_size_indy_interfaces__msg__ServoRx(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ServoRx__ros_msg_type * ros_message = static_cast<const _ServoRx__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name control_word
  {
    size_t item_size = sizeof(ros_message->control_word);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name mode_op
  {
    size_t item_size = sizeof(ros_message->mode_op);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name target_pos
  {
    size_t item_size = sizeof(ros_message->target_pos);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name target_vel
  {
    size_t item_size = sizeof(ros_message->target_vel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name target_tor
  {
    size_t item_size = sizeof(ros_message->target_tor);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _ServoRx__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_indy_interfaces__msg__ServoRx(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_indy_interfaces
size_t max_serialized_size_indy_interfaces__msg__ServoRx(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: control_word
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: mode_op
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: target_pos
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: target_vel
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: target_tor
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = indy_interfaces__msg__ServoRx;
    is_plain =
      (
      offsetof(DataType, target_tor) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _ServoRx__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_indy_interfaces__msg__ServoRx(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_ServoRx = {
  "indy_interfaces::msg",
  "ServoRx",
  _ServoRx__cdr_serialize,
  _ServoRx__cdr_deserialize,
  _ServoRx__get_serialized_size,
  _ServoRx__max_serialized_size
};

static rosidl_message_type_support_t _ServoRx__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ServoRx,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, indy_interfaces, msg, ServoRx)() {
  return &_ServoRx__type_support;
}

#if defined(__cplusplus)
}
#endif
