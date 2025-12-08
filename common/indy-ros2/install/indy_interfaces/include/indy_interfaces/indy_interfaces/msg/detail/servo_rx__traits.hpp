// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from indy_interfaces:msg/ServoRx.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__MSG__DETAIL__SERVO_RX__TRAITS_HPP_
#define INDY_INTERFACES__MSG__DETAIL__SERVO_RX__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "indy_interfaces/msg/detail/servo_rx__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace indy_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ServoRx & msg,
  std::ostream & out)
{
  out << "{";
  // member: control_word
  {
    out << "control_word: ";
    rosidl_generator_traits::value_to_yaml(msg.control_word, out);
    out << ", ";
  }

  // member: mode_op
  {
    out << "mode_op: ";
    rosidl_generator_traits::value_to_yaml(msg.mode_op, out);
    out << ", ";
  }

  // member: target_pos
  {
    out << "target_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.target_pos, out);
    out << ", ";
  }

  // member: target_vel
  {
    out << "target_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.target_vel, out);
    out << ", ";
  }

  // member: target_tor
  {
    out << "target_tor: ";
    rosidl_generator_traits::value_to_yaml(msg.target_tor, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ServoRx & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: control_word
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "control_word: ";
    rosidl_generator_traits::value_to_yaml(msg.control_word, out);
    out << "\n";
  }

  // member: mode_op
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode_op: ";
    rosidl_generator_traits::value_to_yaml(msg.mode_op, out);
    out << "\n";
  }

  // member: target_pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.target_pos, out);
    out << "\n";
  }

  // member: target_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.target_vel, out);
    out << "\n";
  }

  // member: target_tor
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_tor: ";
    rosidl_generator_traits::value_to_yaml(msg.target_tor, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ServoRx & msg, bool use_flow_style = false)
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
  const indy_interfaces::msg::ServoRx & msg,
  std::ostream & out, size_t indentation = 0)
{
  indy_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use indy_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const indy_interfaces::msg::ServoRx & msg)
{
  return indy_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<indy_interfaces::msg::ServoRx>()
{
  return "indy_interfaces::msg::ServoRx";
}

template<>
inline const char * name<indy_interfaces::msg::ServoRx>()
{
  return "indy_interfaces/msg/ServoRx";
}

template<>
struct has_fixed_size<indy_interfaces::msg::ServoRx>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<indy_interfaces::msg::ServoRx>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<indy_interfaces::msg::ServoRx>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // INDY_INTERFACES__MSG__DETAIL__SERVO_RX__TRAITS_HPP_
