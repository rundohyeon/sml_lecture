// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from indy_interfaces:msg/ServoTx.idl
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
#include "indy_interfaces/msg/detail/servo_tx__struct.h"
#include "indy_interfaces/msg/detail/servo_tx__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool indy_interfaces__msg__servo_tx__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[38];
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
    assert(strncmp("indy_interfaces.msg._servo_tx.ServoTx", full_classname_dest, 37) == 0);
  }
  indy_interfaces__msg__ServoTx * ros_message = _ros_message;
  {  // status_word
    PyObject * field = PyObject_GetAttrString(_pymsg, "status_word");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->status_word, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // mode_op_disp
    PyObject * field = PyObject_GetAttrString(_pymsg, "mode_op_disp");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->mode_op_disp, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // actual_pos
    PyObject * field = PyObject_GetAttrString(_pymsg, "actual_pos");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->actual_pos = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // actual_vel
    PyObject * field = PyObject_GetAttrString(_pymsg, "actual_vel");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->actual_vel = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // actual_tor
    PyObject * field = PyObject_GetAttrString(_pymsg, "actual_tor");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->actual_tor = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * indy_interfaces__msg__servo_tx__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of ServoTx */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("indy_interfaces.msg._servo_tx");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "ServoTx");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  indy_interfaces__msg__ServoTx * ros_message = (indy_interfaces__msg__ServoTx *)raw_ros_message;
  {  // status_word
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->status_word.data,
      strlen(ros_message->status_word.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "status_word", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mode_op_disp
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->mode_op_disp.data,
      strlen(ros_message->mode_op_disp.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "mode_op_disp", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // actual_pos
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->actual_pos);
    {
      int rc = PyObject_SetAttrString(_pymessage, "actual_pos", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // actual_vel
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->actual_vel);
    {
      int rc = PyObject_SetAttrString(_pymessage, "actual_vel", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // actual_tor
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->actual_tor);
    {
      int rc = PyObject_SetAttrString(_pymessage, "actual_tor", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
