// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from indy_interfaces:srv/IndyService.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__SRV__DETAIL__INDY_SERVICE__TRAITS_HPP_
#define INDY_INTERFACES__SRV__DETAIL__INDY_SERVICE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "indy_interfaces/srv/detail/indy_service__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace indy_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const IndyService_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: data
  {
    out << "data: ";
    rosidl_generator_traits::value_to_yaml(msg.data, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const IndyService_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "data: ";
    rosidl_generator_traits::value_to_yaml(msg.data, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const IndyService_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace indy_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use indy_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const indy_interfaces::srv::IndyService_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  indy_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use indy_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const indy_interfaces::srv::IndyService_Request & msg)
{
  return indy_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<indy_interfaces::srv::IndyService_Request>()
{
  return "indy_interfaces::srv::IndyService_Request";
}

template<>
inline const char * name<indy_interfaces::srv::IndyService_Request>()
{
  return "indy_interfaces/srv/IndyService_Request";
}

template<>
struct has_fixed_size<indy_interfaces::srv::IndyService_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<indy_interfaces::srv::IndyService_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<indy_interfaces::srv::IndyService_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace indy_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const IndyService_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const IndyService_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const IndyService_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace indy_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use indy_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const indy_interfaces::srv::IndyService_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  indy_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use indy_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const indy_interfaces::srv::IndyService_Response & msg)
{
  return indy_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<indy_interfaces::srv::IndyService_Response>()
{
  return "indy_interfaces::srv::IndyService_Response";
}

template<>
inline const char * name<indy_interfaces::srv::IndyService_Response>()
{
  return "indy_interfaces/srv/IndyService_Response";
}

template<>
struct has_fixed_size<indy_interfaces::srv::IndyService_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<indy_interfaces::srv::IndyService_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<indy_interfaces::srv::IndyService_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<indy_interfaces::srv::IndyService>()
{
  return "indy_interfaces::srv::IndyService";
}

template<>
inline const char * name<indy_interfaces::srv::IndyService>()
{
  return "indy_interfaces/srv/IndyService";
}

template<>
struct has_fixed_size<indy_interfaces::srv::IndyService>
  : std::integral_constant<
    bool,
    has_fixed_size<indy_interfaces::srv::IndyService_Request>::value &&
    has_fixed_size<indy_interfaces::srv::IndyService_Response>::value
  >
{
};

template<>
struct has_bounded_size<indy_interfaces::srv::IndyService>
  : std::integral_constant<
    bool,
    has_bounded_size<indy_interfaces::srv::IndyService_Request>::value &&
    has_bounded_size<indy_interfaces::srv::IndyService_Response>::value
  >
{
};

template<>
struct is_service<indy_interfaces::srv::IndyService>
  : std::true_type
{
};

template<>
struct is_service_request<indy_interfaces::srv::IndyService_Request>
  : std::true_type
{
};

template<>
struct is_service_response<indy_interfaces::srv::IndyService_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // INDY_INTERFACES__SRV__DETAIL__INDY_SERVICE__TRAITS_HPP_
