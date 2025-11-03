// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from indy_interfaces:msg/ServoDataArray.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__MSG__DETAIL__SERVO_DATA_ARRAY__BUILDER_HPP_
#define INDY_INTERFACES__MSG__DETAIL__SERVO_DATA_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "indy_interfaces/msg/detail/servo_data_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace indy_interfaces
{

namespace msg
{

namespace builder
{

class Init_ServoDataArray_rx
{
public:
  explicit Init_ServoDataArray_rx(::indy_interfaces::msg::ServoDataArray & msg)
  : msg_(msg)
  {}
  ::indy_interfaces::msg::ServoDataArray rx(::indy_interfaces::msg::ServoDataArray::_rx_type arg)
  {
    msg_.rx = std::move(arg);
    return std::move(msg_);
  }

private:
  ::indy_interfaces::msg::ServoDataArray msg_;
};

class Init_ServoDataArray_tx
{
public:
  Init_ServoDataArray_tx()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServoDataArray_rx tx(::indy_interfaces::msg::ServoDataArray::_tx_type arg)
  {
    msg_.tx = std::move(arg);
    return Init_ServoDataArray_rx(msg_);
  }

private:
  ::indy_interfaces::msg::ServoDataArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::indy_interfaces::msg::ServoDataArray>()
{
  return indy_interfaces::msg::builder::Init_ServoDataArray_tx();
}

}  // namespace indy_interfaces

#endif  // INDY_INTERFACES__MSG__DETAIL__SERVO_DATA_ARRAY__BUILDER_HPP_
