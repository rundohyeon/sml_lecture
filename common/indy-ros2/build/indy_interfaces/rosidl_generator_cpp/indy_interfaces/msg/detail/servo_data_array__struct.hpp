// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from indy_interfaces:msg/ServoDataArray.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__MSG__DETAIL__SERVO_DATA_ARRAY__STRUCT_HPP_
#define INDY_INTERFACES__MSG__DETAIL__SERVO_DATA_ARRAY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'tx'
#include "indy_interfaces/msg/detail/servo_tx__struct.hpp"
// Member 'rx'
#include "indy_interfaces/msg/detail/servo_rx__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__indy_interfaces__msg__ServoDataArray __attribute__((deprecated))
#else
# define DEPRECATED__indy_interfaces__msg__ServoDataArray __declspec(deprecated)
#endif

namespace indy_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ServoDataArray_
{
  using Type = ServoDataArray_<ContainerAllocator>;

  explicit ServoDataArray_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit ServoDataArray_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _tx_type =
    std::vector<indy_interfaces::msg::ServoTx_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<indy_interfaces::msg::ServoTx_<ContainerAllocator>>>;
  _tx_type tx;
  using _rx_type =
    std::vector<indy_interfaces::msg::ServoRx_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<indy_interfaces::msg::ServoRx_<ContainerAllocator>>>;
  _rx_type rx;

  // setters for named parameter idiom
  Type & set__tx(
    const std::vector<indy_interfaces::msg::ServoTx_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<indy_interfaces::msg::ServoTx_<ContainerAllocator>>> & _arg)
  {
    this->tx = _arg;
    return *this;
  }
  Type & set__rx(
    const std::vector<indy_interfaces::msg::ServoRx_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<indy_interfaces::msg::ServoRx_<ContainerAllocator>>> & _arg)
  {
    this->rx = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    indy_interfaces::msg::ServoDataArray_<ContainerAllocator> *;
  using ConstRawPtr =
    const indy_interfaces::msg::ServoDataArray_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<indy_interfaces::msg::ServoDataArray_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<indy_interfaces::msg::ServoDataArray_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      indy_interfaces::msg::ServoDataArray_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<indy_interfaces::msg::ServoDataArray_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      indy_interfaces::msg::ServoDataArray_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<indy_interfaces::msg::ServoDataArray_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<indy_interfaces::msg::ServoDataArray_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<indy_interfaces::msg::ServoDataArray_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__indy_interfaces__msg__ServoDataArray
    std::shared_ptr<indy_interfaces::msg::ServoDataArray_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__indy_interfaces__msg__ServoDataArray
    std::shared_ptr<indy_interfaces::msg::ServoDataArray_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ServoDataArray_ & other) const
  {
    if (this->tx != other.tx) {
      return false;
    }
    if (this->rx != other.rx) {
      return false;
    }
    return true;
  }
  bool operator!=(const ServoDataArray_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ServoDataArray_

// alias to use template instance with default allocator
using ServoDataArray =
  indy_interfaces::msg::ServoDataArray_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace indy_interfaces

#endif  // INDY_INTERFACES__MSG__DETAIL__SERVO_DATA_ARRAY__STRUCT_HPP_
