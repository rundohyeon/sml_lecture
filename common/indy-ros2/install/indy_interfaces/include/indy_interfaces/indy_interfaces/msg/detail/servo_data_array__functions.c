// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from indy_interfaces:msg/ServoDataArray.idl
// generated code does not contain a copyright notice
#include "indy_interfaces/msg/detail/servo_data_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `tx`
#include "indy_interfaces/msg/detail/servo_tx__functions.h"
// Member `rx`
#include "indy_interfaces/msg/detail/servo_rx__functions.h"

bool
indy_interfaces__msg__ServoDataArray__init(indy_interfaces__msg__ServoDataArray * msg)
{
  if (!msg) {
    return false;
  }
  // tx
  if (!indy_interfaces__msg__ServoTx__Sequence__init(&msg->tx, 0)) {
    indy_interfaces__msg__ServoDataArray__fini(msg);
    return false;
  }
  // rx
  if (!indy_interfaces__msg__ServoRx__Sequence__init(&msg->rx, 0)) {
    indy_interfaces__msg__ServoDataArray__fini(msg);
    return false;
  }
  return true;
}

void
indy_interfaces__msg__ServoDataArray__fini(indy_interfaces__msg__ServoDataArray * msg)
{
  if (!msg) {
    return;
  }
  // tx
  indy_interfaces__msg__ServoTx__Sequence__fini(&msg->tx);
  // rx
  indy_interfaces__msg__ServoRx__Sequence__fini(&msg->rx);
}

bool
indy_interfaces__msg__ServoDataArray__are_equal(const indy_interfaces__msg__ServoDataArray * lhs, const indy_interfaces__msg__ServoDataArray * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // tx
  if (!indy_interfaces__msg__ServoTx__Sequence__are_equal(
      &(lhs->tx), &(rhs->tx)))
  {
    return false;
  }
  // rx
  if (!indy_interfaces__msg__ServoRx__Sequence__are_equal(
      &(lhs->rx), &(rhs->rx)))
  {
    return false;
  }
  return true;
}

bool
indy_interfaces__msg__ServoDataArray__copy(
  const indy_interfaces__msg__ServoDataArray * input,
  indy_interfaces__msg__ServoDataArray * output)
{
  if (!input || !output) {
    return false;
  }
  // tx
  if (!indy_interfaces__msg__ServoTx__Sequence__copy(
      &(input->tx), &(output->tx)))
  {
    return false;
  }
  // rx
  if (!indy_interfaces__msg__ServoRx__Sequence__copy(
      &(input->rx), &(output->rx)))
  {
    return false;
  }
  return true;
}

indy_interfaces__msg__ServoDataArray *
indy_interfaces__msg__ServoDataArray__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  indy_interfaces__msg__ServoDataArray * msg = (indy_interfaces__msg__ServoDataArray *)allocator.allocate(sizeof(indy_interfaces__msg__ServoDataArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(indy_interfaces__msg__ServoDataArray));
  bool success = indy_interfaces__msg__ServoDataArray__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
indy_interfaces__msg__ServoDataArray__destroy(indy_interfaces__msg__ServoDataArray * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    indy_interfaces__msg__ServoDataArray__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
indy_interfaces__msg__ServoDataArray__Sequence__init(indy_interfaces__msg__ServoDataArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  indy_interfaces__msg__ServoDataArray * data = NULL;

  if (size) {
    data = (indy_interfaces__msg__ServoDataArray *)allocator.zero_allocate(size, sizeof(indy_interfaces__msg__ServoDataArray), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = indy_interfaces__msg__ServoDataArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        indy_interfaces__msg__ServoDataArray__fini(&data[i - 1]);
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
indy_interfaces__msg__ServoDataArray__Sequence__fini(indy_interfaces__msg__ServoDataArray__Sequence * array)
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
      indy_interfaces__msg__ServoDataArray__fini(&array->data[i]);
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

indy_interfaces__msg__ServoDataArray__Sequence *
indy_interfaces__msg__ServoDataArray__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  indy_interfaces__msg__ServoDataArray__Sequence * array = (indy_interfaces__msg__ServoDataArray__Sequence *)allocator.allocate(sizeof(indy_interfaces__msg__ServoDataArray__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = indy_interfaces__msg__ServoDataArray__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
indy_interfaces__msg__ServoDataArray__Sequence__destroy(indy_interfaces__msg__ServoDataArray__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    indy_interfaces__msg__ServoDataArray__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
indy_interfaces__msg__ServoDataArray__Sequence__are_equal(const indy_interfaces__msg__ServoDataArray__Sequence * lhs, const indy_interfaces__msg__ServoDataArray__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!indy_interfaces__msg__ServoDataArray__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
indy_interfaces__msg__ServoDataArray__Sequence__copy(
  const indy_interfaces__msg__ServoDataArray__Sequence * input,
  indy_interfaces__msg__ServoDataArray__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(indy_interfaces__msg__ServoDataArray);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    indy_interfaces__msg__ServoDataArray * data =
      (indy_interfaces__msg__ServoDataArray *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!indy_interfaces__msg__ServoDataArray__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          indy_interfaces__msg__ServoDataArray__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!indy_interfaces__msg__ServoDataArray__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
