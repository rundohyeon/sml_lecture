// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from indy_interfaces:msg/ServoDataArray.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "indy_interfaces/msg/detail/servo_data_array__struct.h"
#include "indy_interfaces/msg/detail/servo_data_array__functions.h"

#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

// Nested array functions includes
#include "indy_interfaces/msg/detail/servo_rx__functions.h"
#include "indy_interfaces/msg/detail/servo_tx__functions.h"
// end nested array functions include
bool indy_interfaces__msg__servo_tx__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * indy_interfaces__msg__servo_tx__convert_to_py(void * raw_ros_message);
bool indy_interfaces__msg__servo_rx__convert_from_py(PyObject * _pymsg, void * _ros_message);
PyObject * indy_interfaces__msg__servo_rx__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool indy_interfaces__msg__servo_data_array__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[53];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("indy_interfaces.msg._servo_data_array.ServoDataArray", full_classname_dest, 52) == 0);
  }
  indy_interfaces__msg__ServoDataArray * ros_message = _ros_message;
  {  // tx
    PyObject * field = PyObject_GetAttrString(_pymsg, "tx");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'tx'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!indy_interfaces__msg__ServoTx__Sequence__init(&(ros_message->tx), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create indy_interfaces__msg__ServoTx__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    indy_interfaces__msg__ServoTx * dest = ros_message->tx.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!indy_interfaces__msg__servo_tx__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // rx
    PyObject * field = PyObject_GetAttrString(_pymsg, "rx");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'rx'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = PySequence_Size(field);
    if (-1 == size) {
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    if (!indy_interfaces__msg__ServoRx__Sequence__init(&(ros_message->rx), size)) {
      PyErr_SetString(PyExc_RuntimeError, "unable to create indy_interfaces__msg__ServoRx__Sequence ros_message");
      Py_DECREF(seq_field);
      Py_DECREF(field);
      return false;
    }
    indy_interfaces__msg__ServoRx * dest = ros_message->rx.data;
    for (Py_ssize_t i = 0; i < size; ++i) {
      if (!indy_interfaces__msg__servo_rx__convert_from_py(PySequence_Fast_GET_ITEM(seq_field, i), &dest[i])) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * indy_interfaces__msg__servo_data_array__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of ServoDataArray */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("indy_interfaces.msg._servo_data_array");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "ServoDataArray");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  indy_interfaces__msg__ServoDataArray * ros_message = (indy_interfaces__msg__ServoDataArray *)raw_ros_message;
  {  // tx
    PyObject * field = NULL;
    size_t size = ros_message->tx.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    indy_interfaces__msg__ServoTx * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->tx.data[i]);
      PyObject * pyitem = indy_interfaces__msg__servo_tx__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "tx", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // rx
    PyObject * field = NULL;
    size_t size = ros_message->rx.size;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    indy_interfaces__msg__ServoRx * item;
    for (size_t i = 0; i < size; ++i) {
      item = &(ros_message->rx.data[i]);
      PyObject * pyitem = indy_interfaces__msg__servo_rx__convert_to_py(item);
      if (!pyitem) {
        Py_DECREF(field);
        return NULL;
      }
      int rc = PyList_SetItem(field, i, pyitem);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "rx", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
