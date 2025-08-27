// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from indy_interfaces:msg/ServoTx.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__MSG__DETAIL__SERVO_TX__BUILDER_HPP_
#define INDY_INTERFACES__MSG__DETAIL__SERVO_TX__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "indy_interfaces/msg/detail/servo_tx__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace indy_interfaces
{

namespace msg
{

namespace builder
{

class Init_ServoTx_actual_tor
{
public:
  explicit Init_ServoTx_actual_tor(::indy_interfaces::msg::ServoTx & msg)
  : msg_(msg)
  {}
  ::indy_interfaces::msg::ServoTx actual_tor(::indy_interfaces::msg::ServoTx::_actual_tor_type arg)
  {
    msg_.actual_tor = std::move(arg);
    return std::move(msg_);
  }

private:
  ::indy_interfaces::msg::ServoTx msg_;
};

class Init_ServoTx_actual_vel
{
public:
  explicit Init_ServoTx_actual_vel(::indy_interfaces::msg::ServoTx & msg)
  : msg_(msg)
  {}
  Init_ServoTx_actual_tor actual_vel(::indy_interfaces::msg::ServoTx::_actual_vel_type arg)
  {
    msg_.actual_vel = std::move(arg);
    return Init_ServoTx_actual_tor(msg_);
  }

private:
  ::indy_interfaces::msg::ServoTx msg_;
};

class Init_ServoTx_actual_pos
{
public:
  explicit Init_ServoTx_actual_pos(::indy_interfaces::msg::ServoTx & msg)
  : msg_(msg)
  {}
  Init_ServoTx_actual_vel actual_pos(::indy_interfaces::msg::ServoTx::_actual_pos_type arg)
  {
    msg_.actual_pos = std::move(arg);
    return Init_ServoTx_actual_vel(msg_);
  }

private:
  ::indy_interfaces::msg::ServoTx msg_;
};

class Init_ServoTx_mode_op_disp
{
public:
  explicit Init_ServoTx_mode_op_disp(::indy_interfaces::msg::ServoTx & msg)
  : msg_(msg)
  {}
  Init_ServoTx_actual_pos mode_op_disp(::indy_interfaces::msg::ServoTx::_mode_op_disp_type arg)
  {
    msg_.mode_op_disp = std::move(arg);
    return Init_ServoTx_actual_pos(msg_);
  }

private:
  ::indy_interfaces::msg::ServoTx msg_;
};

class Init_ServoTx_status_word
{
public:
  Init_ServoTx_status_word()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServoTx_mode_op_disp status_word(::indy_interfaces::msg::ServoTx::_status_word_type arg)
  {
    msg_.status_word = std::move(arg);
    return Init_ServoTx_mode_op_disp(msg_);
  }

private:
  ::indy_interfaces::msg::ServoTx msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::indy_interfaces::msg::ServoTx>()
{
  return indy_interfaces::msg::builder::Init_ServoTx_status_word();
}

}  // namespace indy_interfaces

#endif  // INDY_INTERFACES__MSG__DETAIL__SERVO_TX__BUILDER_HPP_
