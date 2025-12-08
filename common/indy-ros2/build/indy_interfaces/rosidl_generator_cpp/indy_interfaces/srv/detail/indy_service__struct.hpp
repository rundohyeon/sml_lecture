// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from indy_interfaces:srv/IndyService.idl
// generated code does not contain a copyright notice

#ifndef INDY_INTERFACES__SRV__DETAIL__INDY_SERVICE__STRUCT_HPP_
#define INDY_INTERFACES__SRV__DETAIL__INDY_SERVICE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__indy_interfaces__srv__IndyService_Request __attribute__((deprecated))
#else
# define DEPRECATED__indy_interfaces__srv__IndyService_Request __declspec(deprecated)
#endif

namespace indy_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct IndyService_Request_
{
  using Type = IndyService_Request_<ContainerAllocator>;

  explicit IndyService_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->data = 0l;
    }
  }

  explicit IndyService_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->data = 0l;
    }
  }

  // field types and members
  using _data_type =
    int32_t;
  _data_type data;

  // setters for named parameter idiom
  Type & set__data(
    const int32_t & _arg)
  {
    this->data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    indy_interfaces::srv::IndyService_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const indy_interfaces::srv::IndyService_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<indy_interfaces::srv::IndyService_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<indy_interfaces::srv::IndyService_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      indy_interfaces::srv::IndyService_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<indy_interfaces::srv::IndyService_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      indy_interfaces::srv::IndyService_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<indy_interfaces::srv::IndyService_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<indy_interfaces::srv::IndyService_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<indy_interfaces::srv::IndyService_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__indy_interfaces__srv__IndyService_Request
    std::shared_ptr<indy_interfaces::srv::IndyService_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__indy_interfaces__srv__IndyService_Request
    std::shared_ptr<indy_interfaces::srv::IndyService_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const IndyService_Request_ & other) const
  {
    if (this->data != other.data) {
      return false;
    }
    return true;
  }
  bool operator!=(const IndyService_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct IndyService_Request_

// alias to use template instance with default allocator
using IndyService_Request =
  indy_interfaces::srv::IndyService_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace indy_interfaces


#ifndef _WIN32
# define DEPRECATED__indy_interfaces__srv__IndyService_Response __attribute__((deprecated))
#else
# define DEPRECATED__indy_interfaces__srv__IndyService_Response __declspec(deprecated)
#endif

namespace indy_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct IndyService_Response_
{
  using Type = IndyService_Response_<ContainerAllocator>;

  explicit IndyService_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit IndyService_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    indy_interfaces::srv::IndyService_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const indy_interfaces::srv::IndyService_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<indy_interfaces::srv::IndyService_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<indy_interfaces::srv::IndyService_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      indy_interfaces::srv::IndyService_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<indy_interfaces::srv::IndyService_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      indy_interfaces::srv::IndyService_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<indy_interfaces::srv::IndyService_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<indy_interfaces::srv::IndyService_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<indy_interfaces::srv::IndyService_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__indy_interfaces__srv__IndyService_Response
    std::shared_ptr<indy_interfaces::srv::IndyService_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__indy_interfaces__srv__IndyService_Response
    std::shared_ptr<indy_interfaces::srv::IndyService_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const IndyService_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const IndyService_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct IndyService_Response_

// alias to use template instance with default allocator
using IndyService_Response =
  indy_interfaces::srv::IndyService_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace indy_interfaces

namespace indy_interfaces
{

namespace srv
{

struct IndyService
{
  using Request = indy_interfaces::srv::IndyService_Request;
  using Response = indy_interfaces::srv::IndyService_Response;
};

}  // namespace srv

}  // namespace indy_interfaces

#endif  // INDY_INTERFACES__SRV__DETAIL__INDY_SERVICE__STRUCT_HPP_
