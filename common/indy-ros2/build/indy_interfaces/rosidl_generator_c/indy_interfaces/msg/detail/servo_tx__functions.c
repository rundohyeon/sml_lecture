// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from indy_interfaces:msg/ServoTx.idl
// generated code does not contain a copyright notice
#include "indy_interfaces/msg/detail/servo_tx__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `status_word`
// Member `mode_op_disp`
#include "rosidl_runtime_c/string_functions.h"

bool
indy_interfaces__msg__ServoTx__init(indy_interfaces__msg__ServoTx * msg)
{
  if (!msg) {
    return false;
  }
  // status_word
  if (!rosidl_runtime_c__String__init(&msg->status_word)) {
    indy_interfaces__msg__ServoTx__fini(msg);
    return false;
  }
  // mode_op_disp
  if (!rosidl_runtime_c__String__init(&msg->mode_op_disp)) {
    indy_interfaces__msg__ServoTx__fini(msg);
    return false;
  }
  // actual_pos
  // actual_vel
  // actual_tor
  return true;
}

void
indy_interfaces__msg__ServoTx__fini(indy_interfaces__msg__ServoTx * msg)
{
  if (!msg) {
    return;
  }
  // status_word
  rosidl_runtime_c__String__fini(&msg->status_word);
  // mode_op_disp
  rosidl_runtime_c__String__fini(&msg->mode_op_disp);
  // actual_pos
  // actual_vel
  // actual_tor
}

bool
indy_interfaces__msg__ServoTx__are_equal(const indy_interfaces__msg__ServoTx * lhs, const indy_interfaces__msg__ServoTx * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status_word
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->status_word), &(rhs->status_word)))
  {
    return false;
  }
  // mode_op_disp
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->mode_op_disp), &(rhs->mode_op_disp)))
  {
    return false;
  }
  // actual_pos
  if (lhs->actual_pos != rhs->actual_pos) {
    return false;
  }
  // actual_vel
  if (lhs->actual_vel != rhs->actual_vel) {
    return false;
  }
  // actual_tor
  if (lhs->actual_tor != rhs->actual_tor) {
    return false;
  }
  return true;
}

bool
indy_interfaces__msg__ServoTx__copy(
  const indy_interfaces__msg__ServoTx * input,
  indy_interfaces__msg__ServoTx * output)
{
  if (!input || !output) {
    return false;
  }
  // status_word
  if (!rosidl_runtime_c__String__copy(
      &(input->status_word), &(output->status_word)))
  {
    return false;
  }
  // mode_op_disp
  if (!rosidl_runtime_c__String__copy(
      &(input->mode_op_disp), &(output->mode_op_disp)))
  {
    return false;
  }
  // actual_pos
  output->actual_pos = input->actual_pos;
  // actual_vel
  output->actual_vel = input->actual_vel;
  // actual_tor
  output->actual_tor = input->actual_tor;
  return true;
}

indy_interfaces__msg__ServoTx *
indy_interfaces__msg__ServoTx__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  indy_interfaces__msg__ServoTx * msg = (indy_interfaces__msg__ServoTx *)allocator.allocate(sizeof(indy_interfaces__msg__ServoTx), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(indy_interfaces__msg__ServoTx));
  bool success = indy_interfaces__msg__ServoTx__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
indy_interfaces__msg__ServoTx__destroy(indy_interfaces__msg__ServoTx * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    indy_interfaces__msg__ServoTx__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
indy_interfaces__msg__ServoTx__Sequence__init(indy_interfaces__msg__ServoTx__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  indy_interfaces__msg__ServoTx * data = NULL;

  if (size) {
    data = (indy_interfaces__msg__ServoTx *)allocator.zero_allocate(size, sizeof(indy_interfaces__msg__ServoTx), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = indy_interfaces__msg__ServoTx__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        indy_interfaces__msg__ServoTx__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
indy_interfaces__msg__ServoTx__Sequence__fini(indy_interfaces__msg__ServoTx__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      indy_interfaces__msg__ServoTx__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

indy_interfaces__msg__ServoTx__Sequence *
indy_interfaces__msg__ServoTx__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  indy_interfaces__msg__ServoTx__Sequence * array = (indy_interfaces__msg__ServoTx__Sequence *)allocator.allocate(sizeof(indy_interfaces__msg__ServoTx__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = indy_interfaces__msg__ServoTx__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
indy_interfaces__msg__ServoTx__Sequence__destroy(indy_interfaces__msg__ServoTx__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    indy_interfaces__msg__ServoTx__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
indy_interfaces__msg__ServoTx__Sequence__are_equal(const indy_interfaces__msg__ServoTx__Sequence * lhs, const indy_interfaces__msg__ServoTx__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!indy_interfaces__msg__ServoTx__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
indy_interfaces__msg__ServoTx__Sequence__copy(
  const indy_interfaces__msg__ServoTx__Sequence * input,
  indy_interfaces__msg__ServoTx__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(indy_interfaces__msg__ServoTx);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    indy_interfaces__msg__ServoTx * data =
      (indy_interfaces__msg__ServoTx *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!indy_interfaces__msg__ServoTx__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          indy_interfaces__msg__ServoTx__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!indy_interfaces__msg__ServoTx__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
