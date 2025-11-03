// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from indy_interfaces:srv/IndyService.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__SRV__DETAIL__INDY_SERVICE__BUILDER_HPP_
#define INDY_INTERFACES__SRV__DETAIL__INDY_SERVICE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "indy_interfaces/srv/detail/indy_service__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace indy_interfaces
{

namespace srv
{

namespace builder
{

class Init_IndyService_Request_data
{
public:
  Init_IndyService_Request_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::indy_interfaces::srv::IndyService_Request data(::indy_interfaces::srv::IndyService_Request::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::indy_interfaces::srv::IndyService_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::indy_interfaces::srv::IndyService_Request>()
{
  return indy_interfaces::srv::builder::Init_IndyService_Request_data();
}

}  // namespace indy_interfaces


namespace indy_interfaces
{

namespace srv
{

namespace builder
{

class Init_IndyService_Response_message
{
public:
  explicit Init_IndyService_Response_message(::indy_interfaces::srv::IndyService_Response & msg)
  : msg_(msg)
  {}
  ::indy_interfaces::srv::IndyService_Response message(::indy_interfaces::srv::IndyService_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::indy_interfaces::srv::IndyService_Response msg_;
};

class Init_IndyService_Response_success
{
public:
  Init_IndyService_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_IndyService_Response_message success(::indy_interfaces::srv::IndyService_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_IndyService_Response_message(msg_);
  }

private:
  ::indy_interfaces::srv::IndyService_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::indy_interfaces::srv::IndyService_Response>()
{
  return indy_interfaces::srv::builder::Init_IndyService_Response_success();
}

}  // namespace indy_interfaces

#endif  // INDY_INTERFACES__SRV__DETAIL__INDY_SERVICE__BUILDER_HPP_
