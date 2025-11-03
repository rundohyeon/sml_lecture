// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from indy_interfaces:msg/ServoRx.idl
// generated code does not contain a copyright notice
#include "indy_interfaces/msg/detail/servo_rx__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
indy_interfaces__msg__ServoRx__init(indy_interfaces__msg__ServoRx * msg)
{
  if (!msg) {
    return false;
  }
  // control_word
  // mode_op
  // target_pos
  // target_vel
  // target_tor
  return true;
}

void
indy_interfaces__msg__ServoRx__fini(indy_interfaces__msg__ServoRx * msg)
{
  if (!msg) {
    return;
  }
  // control_word
  // mode_op
  // target_pos
  // target_vel
  // target_tor
}

bool
indy_interfaces__msg__ServoRx__are_equal(const indy_interfaces__msg__ServoRx * lhs, const indy_interfaces__msg__ServoRx * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // control_word
  if (lhs->control_word != rhs->control_word) {
    return false;
  }
  // mode_op
  if (lhs->mode_op != rhs->mode_op) {
    return false;
  }
  // target_pos
  if (lhs->target_pos != rhs->target_pos) {
    return false;
  }
  // target_vel
  if (lhs->target_vel != rhs->target_vel) {
    return false;
  }
  // target_tor
  if (lhs->target_tor != rhs->target_tor) {
    return false;
  }
  return true;
}

bool
indy_interfaces__msg__ServoRx__copy(
  const indy_interfaces__msg__ServoRx * input,
  indy_interfaces__msg__ServoRx * output)
{
  if (!input || !output) {
    return false;
  }
  // control_word
  output->control_word = input->control_word;
  // mode_op
  output->mode_op = input->mode_op;
  // target_pos
  output->target_pos = input->target_pos;
  // target_vel
  output->target_vel = input->target_vel;
  // target_tor
  output->target_tor = input->target_tor;
  return true;
}

indy_interfaces__msg__ServoRx *
indy_interfaces__msg__ServoRx__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  indy_interfaces__msg__ServoRx * msg = (indy_interfaces__msg__ServoRx *)allocator.allocate(sizeof(indy_interfaces__msg__ServoRx), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(indy_interfaces__msg__ServoRx));
  bool success = indy_interfaces__msg__ServoRx__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
indy_interfaces__msg__ServoRx__destroy(indy_interfaces__msg__ServoRx * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    indy_interfaces__msg__ServoRx__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
indy_interfaces__msg__ServoRx__Sequence__init(indy_interfaces__msg__ServoRx__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  indy_interfaces__msg__ServoRx * data = NULL;

  if (size) {
    data = (indy_interfaces__msg__ServoRx *)allocator.zero_allocate(size, sizeof(indy_interfaces__msg__ServoRx), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = indy_interfaces__msg__ServoRx__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        indy_interfaces__msg__ServoRx__fini(&data[i - 1]);
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
indy_interfaces__msg__ServoRx__Sequence__fini(indy_interfaces__msg__ServoRx__Sequence * array)
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
      indy_interfaces__msg__ServoRx__fini(&array->data[i]);
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

indy_interfaces__msg__ServoRx__Sequence *
indy_interfaces__msg__ServoRx__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  indy_interfaces__msg__ServoRx__Sequence * array = (indy_interfaces__msg__ServoRx__Sequence *)allocator.allocate(sizeof(indy_interfaces__msg__ServoRx__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = indy_interfaces__msg__ServoRx__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
indy_interfaces__msg__ServoRx__Sequence__destroy(indy_interfaces__msg__ServoRx__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    indy_interfaces__msg__ServoRx__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
indy_interfaces__msg__ServoRx__Sequence__are_equal(const indy_interfaces__msg__ServoRx__Sequence * lhs, const indy_interfaces__msg__ServoRx__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!indy_interfaces__msg__ServoRx__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
indy_interfaces__msg__ServoRx__Sequence__copy(
  const indy_interfaces__msg__ServoRx__Sequence * input,
  indy_interfaces__msg__ServoRx__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(indy_interfaces__msg__ServoRx);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    indy_interfaces__msg__ServoRx * data =
      (indy_interfaces__msg__ServoRx *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!indy_interfaces__msg__ServoRx__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          indy_interfaces__msg__ServoRx__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!indy_interfaces__msg__ServoRx__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
