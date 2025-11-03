// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from indy_interfaces:msg/ServoRx.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__MSG__DETAIL__SERVO_RX__STRUCT_HPP_
#define INDY_INTERFACES__MSG__DETAIL__SERVO_RX__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__indy_interfaces__msg__ServoRx __attribute__((deprecated))
#else
# define DEPRECATED__indy_interfaces__msg__ServoRx __declspec(deprecated)
#endif

namespace indy_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ServoRx_
{
  using Type = ServoRx_<ContainerAllocator>;

  explicit ServoRx_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->control_word = 0l;
      this->mode_op = 0l;
      this->target_pos = 0l;
      this->target_vel = 0l;
      this->target_tor = 0l;
    }
  }

  explicit ServoRx_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->control_word = 0l;
      this->mode_op = 0l;
      this->target_pos = 0l;
      this->target_vel = 0l;
      this->target_tor = 0l;
    }
  }

  // field types and members
  using _control_word_type =
    int32_t;
  _control_word_type control_word;
  using _mode_op_type =
    int32_t;
  _mode_op_type mode_op;
  using _target_pos_type =
    int32_t;
  _target_pos_type target_pos;
  using _target_vel_type =
    int32_t;
  _target_vel_type target_vel;
  using _target_tor_type =
    int32_t;
  _target_tor_type target_tor;

  // setters for named parameter idiom
  Type & set__control_word(
    const int32_t & _arg)
  {
    this->control_word = _arg;
    return *this;
  }
  Type & set__mode_op(
    const int32_t & _arg)
  {
    this->mode_op = _arg;
    return *this;
  }
  Type & set__target_pos(
    const int32_t & _arg)
  {
    this->target_pos = _arg;
    return *this;
  }
  Type & set__target_vel(
    const int32_t & _arg)
  {
    this->target_vel = _arg;
    return *this;
  }
  Type & set__target_tor(
    const int32_t & _arg)
  {
    this->target_tor = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    indy_interfaces::msg::ServoRx_<ContainerAllocator> *;
  using ConstRawPtr =
    const indy_interfaces::msg::ServoRx_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<indy_interfaces::msg::ServoRx_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<indy_interfaces::msg::ServoRx_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      indy_interfaces::msg::ServoRx_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<indy_interfaces::msg::ServoRx_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      indy_interfaces::msg::ServoRx_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<indy_interfaces::msg::ServoRx_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<indy_interfaces::msg::ServoRx_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<indy_interfaces::msg::ServoRx_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__indy_interfaces__msg__ServoRx
    std::shared_ptr<indy_interfaces::msg::ServoRx_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__indy_interfaces__msg__ServoRx
    std::shared_ptr<indy_interfaces::msg::ServoRx_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ServoRx_ & other) const
  {
    if (this->control_word != other.control_word) {
      return false;
    }
    if (this->mode_op != other.mode_op) {
      return false;
    }
    if (this->target_pos != other.target_pos) {
      return false;
    }
    if (this->target_vel != other.target_vel) {
      return false;
    }
    if (this->target_tor != other.target_tor) {
      return false;
    }
    return true;
  }
  bool operator!=(const ServoRx_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ServoRx_

// alias to use template instance with default allocator
using ServoRx =
  indy_interfaces::msg::ServoRx_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace indy_interfaces

#endif  // INDY_INTERFACES__MSG__DETAIL__SERVO_RX__STRUCT_HPP_
