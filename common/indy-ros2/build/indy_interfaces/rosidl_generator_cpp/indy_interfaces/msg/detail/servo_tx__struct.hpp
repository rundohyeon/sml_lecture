// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from indy_interfaces:msg/ServoTx.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__MSG__DETAIL__SERVO_TX__STRUCT_HPP_
#define INDY_INTERFACES__MSG__DETAIL__SERVO_TX__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__indy_interfaces__msg__ServoTx __attribute__((deprecated))
#else
# define DEPRECATED__indy_interfaces__msg__ServoTx __declspec(deprecated)
#endif

namespace indy_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ServoTx_
{
  using Type = ServoTx_<ContainerAllocator>;

  explicit ServoTx_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status_word = "";
      this->mode_op_disp = "";
      this->actual_pos = 0l;
      this->actual_vel = 0l;
      this->actual_tor = 0l;
    }
  }

  explicit ServoTx_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : status_word(_alloc),
    mode_op_disp(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status_word = "";
      this->mode_op_disp = "";
      this->actual_pos = 0l;
      this->actual_vel = 0l;
      this->actual_tor = 0l;
    }
  }

  // field types and members
  using _status_word_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _status_word_type status_word;
  using _mode_op_disp_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mode_op_disp_type mode_op_disp;
  using _actual_pos_type =
    int32_t;
  _actual_pos_type actual_pos;
  using _actual_vel_type =
    int32_t;
  _actual_vel_type actual_vel;
  using _actual_tor_type =
    int32_t;
  _actual_tor_type actual_tor;

  // setters for named parameter idiom
  Type & set__status_word(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->status_word = _arg;
    return *this;
  }
  Type & set__mode_op_disp(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->mode_op_disp = _arg;
    return *this;
  }
  Type & set__actual_pos(
    const int32_t & _arg)
  {
    this->actual_pos = _arg;
    return *this;
  }
  Type & set__actual_vel(
    const int32_t & _arg)
  {
    this->actual_vel = _arg;
    return *this;
  }
  Type & set__actual_tor(
    const int32_t & _arg)
  {
    this->actual_tor = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    indy_interfaces::msg::ServoTx_<ContainerAllocator> *;
  using ConstRawPtr =
    const indy_interfaces::msg::ServoTx_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<indy_interfaces::msg::ServoTx_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<indy_interfaces::msg::ServoTx_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      indy_interfaces::msg::ServoTx_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<indy_interfaces::msg::ServoTx_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      indy_interfaces::msg::ServoTx_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<indy_interfaces::msg::ServoTx_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<indy_interfaces::msg::ServoTx_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<indy_interfaces::msg::ServoTx_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__indy_interfaces__msg__ServoTx
    std::shared_ptr<indy_interfaces::msg::ServoTx_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__indy_interfaces__msg__ServoTx
    std::shared_ptr<indy_interfaces::msg::ServoTx_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ServoTx_ & other) const
  {
    if (this->status_word != other.status_word) {
      return false;
    }
    if (this->mode_op_disp != other.mode_op_disp) {
      return false;
    }
    if (this->actual_pos != other.actual_pos) {
      return false;
    }
    if (this->actual_vel != other.actual_vel) {
      return false;
    }
    if (this->actual_tor != other.actual_tor) {
      return false;
    }
    return true;
  }
  bool operator!=(const ServoTx_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ServoTx_

// alias to use template instance with default allocator
using ServoTx =
  indy_interfaces::msg::ServoTx_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace indy_interfaces

#endif  // INDY_INTERFACES__MSG__DETAIL__SERVO_TX__STRUCT_HPP_
