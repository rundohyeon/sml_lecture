// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from indy_interfaces:msg/ServoDataArray.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__MSG__DETAIL__SERVO_DATA_ARRAY__TRAITS_HPP_
#define INDY_INTERFACES__MSG__DETAIL__SERVO_DATA_ARRAY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "indy_interfaces/msg/detail/servo_data_array__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'tx'
#include "indy_interfaces/msg/detail/servo_tx__traits.hpp"
// Member 'rx'
#include "indy_interfaces/msg/detail/servo_rx__traits.hpp"

namespace indy_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ServoDataArray & msg,
  std::ostream & out)
{
  out << "{";
  // member: tx
  {
    if (msg.tx.size() == 0) {
      out << "tx: []";
    } else {
      out << "tx: [";
      size_t pending_items = msg.tx.size();
      for (auto item : msg.tx) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: rx
  {
    if (msg.rx.size() == 0) {
      out << "rx: []";
    } else {
      out << "rx: [";
      size_t pending_items = msg.rx.size();
      for (auto item : msg.rx) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ServoDataArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: tx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.tx.size() == 0) {
      out << "tx: []\n";
    } else {
      out << "tx:\n";
      for (auto item : msg.tx) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: rx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.rx.size() == 0) {
      out << "rx: []\n";
    } else {
      out << "rx:\n";
      for (auto item : msg.rx) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ServoDataArray & msg, bool use_flow_style = false)
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
  const indy_interfaces::msg::ServoDataArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  indy_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use indy_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const indy_interfaces::msg::ServoDataArray & msg)
{
  return indy_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<indy_interfaces::msg::ServoDataArray>()
{
  return "indy_interfaces::msg::ServoDataArray";
}

template<>
inline const char * name<indy_interfaces::msg::ServoDataArray>()
{
  return "indy_interfaces/msg/ServoDataArray";
}

template<>
struct has_fixed_size<indy_interfaces::msg::ServoDataArray>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<indy_interfaces::msg::ServoDataArray>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<indy_interfaces::msg::ServoDataArray>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // INDY_INTERFACES__MSG__DETAIL__SERVO_DATA_ARRAY__TRAITS_HPP_
