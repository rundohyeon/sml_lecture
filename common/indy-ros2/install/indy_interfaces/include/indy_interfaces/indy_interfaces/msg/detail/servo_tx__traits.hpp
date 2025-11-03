// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from indy_interfaces:msg/ServoTx.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__MSG__DETAIL__SERVO_TX__TRAITS_HPP_
#define INDY_INTERFACES__MSG__DETAIL__SERVO_TX__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "indy_interfaces/msg/detail/servo_tx__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace indy_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ServoTx & msg,
  std::ostream & out)
{
  out << "{";
  // member: status_word
  {
    out << "status_word: ";
    rosidl_generator_traits::value_to_yaml(msg.status_word, out);
    out << ", ";
  }

  // member: mode_op_disp
  {
    out << "mode_op_disp: ";
    rosidl_generator_traits::value_to_yaml(msg.mode_op_disp, out);
    out << ", ";
  }

  // member: actual_pos
  {
    out << "actual_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.actual_pos, out);
    out << ", ";
  }

  // member: actual_vel
  {
    out << "actual_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.actual_vel, out);
    out << ", ";
  }

  // member: actual_tor
  {
    out << "actual_tor: ";
    rosidl_generator_traits::value_to_yaml(msg.actual_tor, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ServoTx & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: status_word
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status_word: ";
    rosidl_generator_traits::value_to_yaml(msg.status_word, out);
    out << "\n";
  }

  // member: mode_op_disp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode_op_disp: ";
    rosidl_generator_traits::value_to_yaml(msg.mode_op_disp, out);
    out << "\n";
  }

  // member: actual_pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "actual_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.actual_pos, out);
    out << "\n";
  }

  // member: actual_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "actual_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.actual_vel, out);
    out << "\n";
  }

  // member: actual_tor
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "actual_tor: ";
    rosidl_generator_traits::value_to_yaml(msg.actual_tor, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ServoTx & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace indy_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use indy_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const indy_interfaces::msg::ServoTx & msg,
  std::ostream & out, size_t indentation = 0)
{
  indy_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use indy_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const indy_interfaces::msg::ServoTx & msg)
{
  return indy_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<indy_interfaces::msg::ServoTx>()
{
  return "indy_interfaces::msg::ServoTx";
}

template<>
inline const char * name<indy_interfaces::msg::ServoTx>()
{
  return "indy_interfaces/msg/ServoTx";
}

template<>
struct has_fixed_size<indy_interfaces::msg::ServoTx>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<indy_interfaces::msg::ServoTx>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<indy_interfaces::msg::ServoTx>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // INDY_INTERFACES__MSG__DETAIL__SERVO_TX__TRAITS_HPP_
