# generated from rosidl_generator_py/resource/_idl.py.em
# with input from indy_interfaces:msg/ServoTx.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ServoTx(type):
    """Metaclass of message 'ServoTx'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('indy_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'indy_interfaces.msg.ServoTx')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__servo_tx
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__servo_tx
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__servo_tx
            cls._TYPE_SUPPORT = module.type_support_msg__msg__servo_tx
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__servo_tx

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ServoTx(metaclass=Metaclass_ServoTx):
    """Message class 'ServoTx'."""

    __slots__ = [
        '_status_word',
        '_mode_op_disp',
        '_actual_pos',
        '_actual_vel',
        '_actual_tor',
    ]

    _fields_and_field_types = {
        'status_word': 'string',
        'mode_op_disp': 'string',
        'actual_pos': 'int32',
        'actual_vel': 'int32',
        'actual_tor': 'int32',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.status_word = kwargs.get('status_word', str())
        self.mode_op_disp = kwargs.get('mode_op_disp', str())
        self.actual_pos = kwargs.get('actual_pos', int())
        self.actual_vel = kwargs.get('actual_vel', int())
        self.actual_tor = kwargs.get('actual_tor', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.status_word != other.status_word:
            return False
        if self.mode_op_disp != other.mode_op_disp:
            return False
        if self.actual_pos != other.actual_pos:
            return False
        if self.actual_vel != other.actual_vel:
            return False
        if self.actual_tor != other.actual_tor:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def status_word(self):
        """Message field 'status_word'."""
        return self._status_word

    @status_word.setter
    def status_word(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'status_word' field must be of type 'str'"
        self._status_word = value

    @builtins.property
    def mode_op_disp(self):
        """Message field 'mode_op_disp'."""
        return self._mode_op_disp

    @mode_op_disp.setter
    def mode_op_disp(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'mode_op_disp' field must be of type 'str'"
        self._mode_op_disp = value

    @builtins.property
    def actual_pos(self):
        """Message field 'actual_pos'."""
        return self._actual_pos

    @actual_pos.setter
    def actual_pos(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'actual_pos' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'actual_pos' field must be an integer in [-2147483648, 2147483647]"
        self._actual_pos = value

    @builtins.property
    def actual_vel(self):
        """Message field 'actual_vel'."""
        return self._actual_vel

    @actual_vel.setter
    def actual_vel(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'actual_vel' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'actual_vel' field must be an integer in [-2147483648, 2147483647]"
        self._actual_vel = value

    @builtins.property
    def actual_tor(self):
        """Message field 'actual_tor'."""
        return self._actual_tor

    @actual_tor.setter
    def actual_tor(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'actual_tor' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'actual_tor' field must be an integer in [-2147483648, 2147483647]"
        self._actual_tor = value
