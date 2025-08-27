// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from indy_interfaces:msg/ServoDataArray.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "indy_interfaces/msg/detail/servo_data_array__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace indy_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void ServoDataArray_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) indy_interfaces::msg::ServoDataArray(_init);
}

void ServoDataArray_fini_function(void * message_memory)
{
  auto typed_message = static_cast<indy_interfaces::msg::ServoDataArray *>(message_memory);
  typed_message->~ServoDataArray();
}

size_t size_function__ServoDataArray__tx(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<indy_interfaces::msg::ServoTx> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ServoDataArray__tx(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<indy_interfaces::msg::ServoTx> *>(untyped_member);
  return &member[index];
}

void * get_function__ServoDataArray__tx(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<indy_interfaces::msg::ServoTx> *>(untyped_member);
  return &member[index];
}

void fetch_function__ServoDataArray__tx(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const indy_interfaces::msg::ServoTx *>(
    get_const_function__ServoDataArray__tx(untyped_member, index));
  auto & value = *reinterpret_cast<indy_interfaces::msg::ServoTx *>(untyped_value);
  value = item;
}

void assign_function__ServoDataArray__tx(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<indy_interfaces::msg::ServoTx *>(
    get_function__ServoDataArray__tx(untyped_member, index));
  const auto & value = *reinterpret_cast<const indy_interfaces::msg::ServoTx *>(untyped_value);
  item = value;
}

void resize_function__ServoDataArray__tx(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<indy_interfaces::msg::ServoTx> *>(untyped_member);
  member->resize(size);
}

size_t size_function__ServoDataArray__rx(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<indy_interfaces::msg::ServoRx> *>(untyped_member);
  return member->size();
}

const void * get_const_function__ServoDataArray__rx(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<indy_interfaces::msg::ServoRx> *>(untyped_member);
  return &member[index];
}

void * get_function__ServoDataArray__rx(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<indy_interfaces::msg::ServoRx> *>(untyped_member);
  return &member[index];
}

void fetch_function__ServoDataArray__rx(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const indy_interfaces::msg::ServoRx *>(
    get_const_function__ServoDataArray__rx(untyped_member, index));
  auto & value = *reinterpret_cast<indy_interfaces::msg::ServoRx *>(untyped_value);
  value = item;
}

void assign_function__ServoDataArray__rx(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<indy_interfaces::msg::ServoRx *>(
    get_function__ServoDataArray__rx(untyped_member, index));
  const auto & value = *reinterpret_cast<const indy_interfaces::msg::ServoRx *>(untyped_value);
  item = value;
}

void resize_function__ServoDataArray__rx(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<indy_interfaces::msg::ServoRx> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember ServoDataArray_message_member_array[2] = {
  {
    "tx",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<indy_interfaces::msg::ServoTx>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(indy_interfaces::msg::ServoDataArray, tx),  // bytes offset in struct
    nullptr,  // default value
    size_function__ServoDataArray__tx,  // size() function pointer
    get_const_function__ServoDataArray__tx,  // get_const(index) function pointer
    get_function__ServoDataArray__tx,  // get(index) function pointer
    fetch_function__ServoDataArray__tx,  // fetch(index, &value) function pointer
    assign_function__ServoDataArray__tx,  // assign(index, value) function pointer
    resize_function__ServoDataArray__tx  // resize(index) function pointer
  },
  {
    "rx",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<indy_interfaces::msg::ServoRx>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(indy_interfaces::msg::ServoDataArray, rx),  // bytes offset in struct
    nullptr,  // default value
    size_function__ServoDataArray__rx,  // size() function pointer
    get_const_function__ServoDataArray__rx,  // get_const(index) function pointer
    get_function__ServoDataArray__rx,  // get(index) function pointer
    fetch_function__ServoDataArray__rx,  // fetch(index, &value) function pointer
    assign_function__ServoDataArray__rx,  // assign(index, value) function pointer
    resize_function__ServoDataArray__rx  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers ServoDataArray_message_members = {
  "indy_interfaces::msg",  // message namespace
  "ServoDataArray",  // message name
  2,  // number of fields
  sizeof(indy_interfaces::msg::ServoDataArray),
  ServoDataArray_message_member_array,  // message members
  ServoDataArray_init_function,  // function to initialize message memory (memory has to be allocated)
  ServoDataArray_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t ServoDataArray_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &ServoDataArray_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace indy_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<indy_interfaces::msg::ServoDataArray>()
{
  return &::indy_interfaces::msg::rosidl_typesupport_introspection_cpp::ServoDataArray_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, indy_interfaces, msg, ServoDataArray)() {
  return &::indy_interfaces::msg::rosidl_typesupport_introspection_cpp::ServoDataArray_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
