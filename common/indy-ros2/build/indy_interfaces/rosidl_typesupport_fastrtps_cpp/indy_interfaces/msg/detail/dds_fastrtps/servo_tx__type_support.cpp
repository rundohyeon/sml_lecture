// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from indy_interfaces:msg/ServoTx.idl
// generated code does not contain a copyright notice
#include "indy_interfaces/msg/detail/servo_tx__rosidl_typesupport_fastrtps_cpp.hpp"
#include "indy_interfaces/msg/detail/servo_tx__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace indy_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_indy_interfaces
cdr_serialize(
  const indy_interfaces::msg::ServoTx & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: status_word
  cdr << ros_message.status_word;
  // Member: mode_op_disp
  cdr << ros_message.mode_op_disp;
  // Member: actual_pos
  cdr << ros_message.actual_pos;
  // Member: actual_vel
  cdr << ros_message.actual_vel;
  // Member: actual_tor
  cdr << ros_message.actual_tor;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_indy_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  indy_interfaces::msg::ServoTx & ros_message)
{
  // Member: status_word
  cdr >> ros_message.status_word;

  // Member: mode_op_disp
  cdr >> ros_message.mode_op_disp;

  // Member: actual_pos
  cdr >> ros_message.actual_pos;

  // Member: actual_vel
  cdr >> ros_message.actual_vel;

  // Member: actual_tor
  cdr >> ros_message.actual_tor;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_indy_interfaces
get_serialized_size(
  const indy_interfaces::msg::ServoTx & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: status_word
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.status_word.size() + 1);
  // Member: mode_op_disp
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.mode_op_disp.size() + 1);
  // Member: actual_pos
  {
    size_t item_size = sizeof(ros_message.actual_pos);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: actual_vel
  {
    size_t item_size = sizeof(ros_message.actual_vel);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: actual_tor
  {
    size_t item_size = sizeof(ros_message.actual_tor);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_indy_interfaces
max_serialized_size_ServoTx(
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


  // Member: status_word
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Member: mode_op_disp
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Member: actual_pos
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: actual_vel
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: actual_tor
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
    using DataType = indy_interfaces::msg::ServoTx;
    is_plain =
      (
      offsetof(DataType, actual_tor) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _ServoTx__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const indy_interfaces::msg::ServoTx *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _ServoTx__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<indy_interfaces::msg::ServoTx *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _ServoTx__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const indy_interfaces::msg::ServoTx *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _ServoTx__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_ServoTx(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _ServoTx__callbacks = {
  "indy_interfaces::msg",
  "ServoTx",
  _ServoTx__cdr_serialize,
  _ServoTx__cdr_deserialize,
  _ServoTx__get_serialized_size,
  _ServoTx__max_serialized_size
};

static rosidl_message_type_support_t _ServoTx__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_ServoTx__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace indy_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_indy_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<indy_interfaces::msg::ServoTx>()
{
  return &indy_interfaces::msg::typesupport_fastrtps_cpp::_ServoTx__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, indy_interfaces, msg, ServoTx)() {
  return &indy_interfaces::msg::typesupport_fastrtps_cpp::_ServoTx__handle;
}

#ifdef __cplusplus
}
#endif
