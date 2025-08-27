// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from indy_interfaces:msg/ServoRx.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__MSG__DETAIL__SERVO_RX__BUILDER_HPP_
#define INDY_INTERFACES__MSG__DETAIL__SERVO_RX__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "indy_interfaces/msg/detail/servo_rx__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace indy_interfaces
{

namespace msg
{

namespace builder
{

class Init_ServoRx_target_tor
{
public:
  explicit Init_ServoRx_target_tor(::indy_interfaces::msg::ServoRx & msg)
  : msg_(msg)
  {}
  ::indy_interfaces::msg::ServoRx target_tor(::indy_interfaces::msg::ServoRx::_target_tor_type arg)
  {
    msg_.target_tor = std::move(arg);
    return std::move(msg_);
  }

private:
  ::indy_interfaces::msg::ServoRx msg_;
};

class Init_ServoRx_target_vel
{
public:
  explicit Init_ServoRx_target_vel(::indy_interfaces::msg::ServoRx & msg)
  : msg_(msg)
  {}
  Init_ServoRx_target_tor target_vel(::indy_interfaces::msg::ServoRx::_target_vel_type arg)
  {
    msg_.target_vel = std::move(arg);
    return Init_ServoRx_target_tor(msg_);
  }

private:
  ::indy_interfaces::msg::ServoRx msg_;
};

class Init_ServoRx_target_pos
{
public:
  explicit Init_ServoRx_target_pos(::indy_interfaces::msg::ServoRx & msg)
  : msg_(msg)
  {}
  Init_ServoRx_target_vel target_pos(::indy_interfaces::msg::ServoRx::_target_pos_type arg)
  {
    msg_.target_pos = std::move(arg);
    return Init_ServoRx_target_vel(msg_);
  }

private:
  ::indy_interfaces::msg::ServoRx msg_;
};

class Init_ServoRx_mode_op
{
public:
  explicit Init_ServoRx_mode_op(::indy_interfaces::msg::ServoRx & msg)
  : msg_(msg)
  {}
  Init_ServoRx_target_pos mode_op(::indy_interfaces::msg::ServoRx::_mode_op_type arg)
  {
    msg_.mode_op = std::move(arg);
    return Init_ServoRx_target_pos(msg_);
  }

private:
  ::indy_interfaces::msg::ServoRx msg_;
};

class Init_ServoRx_control_word
{
public:
  Init_ServoRx_control_word()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServoRx_mode_op control_word(::indy_interfaces::msg::ServoRx::_control_word_type arg)
  {
    msg_.control_word = std::move(arg);
    return Init_ServoRx_mode_op(msg_);
  }

private:
  ::indy_interfaces::msg::ServoRx msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::indy_interfaces::msg::ServoRx>()
{
  return indy_interfaces::msg::builder::Init_ServoRx_control_word();
}

}  // namespace indy_interfaces

#endif  // INDY_INTERFACES__MSG__DETAIL__SERVO_RX__BUILDER_HPP_
