# -*- coding: utf-8 -*-

###############################################################################
# This file is part of Kalray's Metalibm tool
# Copyright (2013-2015)
# All rights reserved
# created:          Dec 23rd, 2013
# last-modified:    Oct  6th, 2015
#
# author(s): Nicolas Brunie (nicolas.brunie@kalray.eu)
###############################################################################

from pythonsollya import *

class ML_FloatingPoint_RoundingMode_Type:
    def get_c_name(self):
        return "ml_rnd_mode_t"

class ML_FloatingPoint_RoundingMode:
    pass

ML_FPRM_Type = ML_FloatingPoint_RoundingMode_Type()

ML_RoundToNearest        = ML_FloatingPoint_RoundingMode()
ML_RoundTowardZero       = ML_FloatingPoint_RoundingMode()
ML_RoundTowardPlusInfty  = ML_FloatingPoint_RoundingMode()
ML_RoundTowardMinusInfty = ML_FloatingPoint_RoundingMode()
ML_GlobalRoundMode       = ML_FloatingPoint_RoundingMode()


class ML_FloatingPointException: pass

class ML_FloatingPointException_Type: 
    def get_c_cst(self, value):
        return "NONE"

ML_FPE_Type = ML_FloatingPointException_Type()

ML_FPE_Underflow    = ML_FloatingPointException()
ML_FPE_Overflow     = ML_FloatingPointException()
ML_FPE_Inexact      = ML_FloatingPointException()
ML_FPE_Invalid      = ML_FloatingPointException()
ML_FPE_DivideByZero = ML_FloatingPointException()

class ML_Format(object): 
    """ parent to every Metalibm's format class """

    def get_bit_size(self):
        """ <abstract> return the bit size of the format (if it exists) """
        print self # Exception ML_NotImplemented print
        raise ML_NotImplemented()

    def generate_c_initialization(self, *args):
      return None

    def generate_c_assignation(self, var, value, final = True):
      final_symbol = ";\n" if final else ""
      return "%s = %s" % (var, value)


class ML_AbstractFormat(ML_Format): 
    def __init__(self, c_name): 
        self.c_name = c_name

    def __str__(self):
        return self.c_name

    def get_gappa_cst(self, cst_value):
        """ C code for constante cst_value """
        display(hexadecimal)
        if isinstance(cst_value, int):
            return str(float(cst_value)) 
        else:
            return str(cst_value) 

ML_Exact = ML_AbstractFormat("ML_Exact")

def AbstractFormat_Builder(name, inheritance):
    field_map = {
        "name": name,
        "__str__": lambda self: self.name,
    }
    return type(name, (ML_AbstractFormat,) + inheritance, field_map)

class ML_InstanciatedFormat(ML_Format): pass

class ML_FP_Format(ML_Format): 
    """ parent to every Metalibm's floating-point class """
    pass


class ML_Std_FP_Format(ML_FP_Format):
    """ standard floating-point format base class """

    def __init__(self, bit_size, exponent_size, field_size, c_suffix, c_name, ml_support_prefix, c_display_format, sollya_object):
        self.bit_size = bit_size
        self.exponent_size = exponent_size
        self.field_size = field_size
        self.c_suffix = c_suffix
        self.c_name = c_name
        self.ml_support_prefix = ml_support_prefix
        self.sollya_object = sollya_object
        self.c_display_format = c_display_format

    def get_sollya_object(self):
      return self.sollya_object

    def __str__(self):
        return self.c_name

    def get_c_name(self):
        return self.c_name

    def get_bias(self):
        return - 2**(self.get_exponent_size() - 1) + 1

    def get_emax(self):
        return 2**self.get_exponent_size() - 2 + self.get_bias()

    def get_emin_normal(self):
        return 1 + self.get_bias()

    def get_emin_subnormal(self):
        return 1 - (self.get_field_size() + 1) + self.get_bias()

    def get_c_display_format(self):
        return self.c_display_format

    def get_bit_size(self):
        """ return the format bit size """ 
        return self.bit_size

    def get_exponent_size(self):
        return self.exponent_size

    def get_exponent_interval(self):
        low_bound  = self.get_emin_normal()
        high_bound = self.get_emax()
        return Interval(low_bound, high_bound)

    def get_field_size(self):
        return self.field_size

    def get_c_cst(self, cst_value):
        """ C code for constante cst_value """
        if isinstance(cst_value, FP_SpecialValue): 
            return cst_value.get_c_cst()
        else:
            display(hexadecimal)
            if cst_value == 0:
                conv_result = "0.0" + self.c_suffix
            elif isinstance(cst_value, int):
                conv_result = str(float(cst_value)) + self.c_suffix
            else:
                conv_result  = str(cst_value) + self.c_suffix
            return conv_result

    def get_precision(self):
        """ return the bit-size of the mantissa """
        return self.get_field_size()

    def get_gappa_cst(self, cst_value):
        """ C code for constante cst_value """
        if isinstance(cst_value, FP_SpecialValue): 
            return cst_value.get_gappa_cst()
        else:
            display(hexadecimal)
            if isinstance(cst_value, int):
                return str(float(cst_value)) 
            else:
                return str(cst_value) 


class ML_Compound_FP_Format(ML_FP_Format):
    def __init__(self, c_name, c_field_list, field_format_list, ml_support_prefix, c_display_format, sollya_object):
        self.c_name = c_name
        self.ml_support_prefix = ml_support_prefix
        self.sollya_object = sollya_object
        self.c_display_format = c_display_format
        self.c_display_format = "undefined"

    def get_c_name(self):
        return self.c_name

    def get_c_cst(self, cst_value):
        tmp_cst = cst_value
        field_str_list = []
        for field_name, field_format in zip(c_field_list, field_format_list):
            field_value = round(tmp_cst, field_format.sollya_object, RN)
            tmp_cst = cst_value - field_value
            field_str_list.append(".%s = %s" % (field_name, field_format.get_c_cst(field_value)))
        return "{%s}" % (", ".join(field_str_list))


    def get_c_display_format(self):
        return self.c_display_format


class ML_FormatConstructor(ML_Format):
    def __init__(self, bit_size, c_name, c_display_format, get_c_cst):
        self.bit_size = bit_size
        self.c_name = c_name
        self.c_display_format = c_display_format
        self.get_c_cst = get_c_cst

    def __str__(self):
        return self.c_name

    def get_c_name(self):
        return self.c_name

    def get_c_display_format(self):
        return self.c_display_format

    def get_bit_size(self):
        return self.bit_size

class ML_Fixed_Format(ML_Format):
    """ parent to every Metalibm's fixed-point class """
    pass


class ML_Base_FixedPoint_Format(ML_Fixed_Format):
    """ base class for standard integer format """
    def __init__(self, integer_size, frac_size, signed = True):
        """ standard fixed-point format object initialization function """
        
        self.integer_size = integer_size
        self.frac_size = frac_size
        self.signed = signed
        
        # guess the minimal bit_size required in the c repesentation
        bit_size = integer_size + frac_size
        if bit_size < 1 or bit_size > 128:
            raise ValueError("integer_size+frac_size must be between 1 and 128 (is "+str(bit_size)+")")
        possible_c_bit_sizes = [8, 16, 32, 64, 128]
        self.c_bit_size = next(n for n in possible_c_bit_sizes if n >= bit_size)
        self.c_name = ("" if self.signed else "u") + "int" + str(self.c_bit_size) + "_t"
        self.c_display_format = "%\"PRIx" + str(self.c_bit_size) + "\""

    def get_integer_size(self):
        return self.integer_size

    def get_c_bit_size(self):
        return self.c_bit_size

    def get_frac_size(self):
        return self.frac_size

    def get_precision(self):
        """ return the number of digits after the point """
        return self.frac_size

    def get_signed(self):
        return self.signed

    def __str__(self):
        if self.frac_size == 0:
          return self.c_name
        elif self.signed:
          return "FS%d.%d" % (self.integer_size, self.frac_size)
        else:
          return "FU%d.%d" % (self.integer_size, self.frac_size)

    def get_c_name(self):
        return self.c_name

    def get_c_display_format(self):
        return self.c_display_format

    def get_bit_size(self):
        return self.integer_size + self.frac_size

    def get_c_cst(self, cst_value):
        """ C-language constant generation """
        encoded_value = int(cst_value * S2**self.frac_size)
        return ("" if self.signed else "U") + "INT" + str(self.c_bit_size) + "_C(" + str(encoded_value) + ")"

    def get_gappa_cst(self, cst_value):
        """ Gappa-language constant generation """
        return str(cst_value)

class ML_Standard_FixedPoint_Format(ML_Base_FixedPoint_Format):
    pass

class ML_Custom_FixedPoint_Format(ML_Base_FixedPoint_Format):
    def __eq__(self, other):
        return (type(self) == type(other)) and (self.__dict__ == other.__dict__)
    
    def __ne__(self, other):
        return not (self == other)

class ML_Bool_Format: 
    """ abstract Boolean format """
    pass

# Standard binary floating-point format declarations
ML_Binary32 = ML_Std_FP_Format(32, 8, 23, "f", "float", "fp32", "%a", binary32)
ML_Binary64 = ML_Std_FP_Format(64, 11, 52, "", "double", "fp64", "%la", binary64)
ML_Binary80 = ML_Std_FP_Format(80, 15, 64, "L", "long double", "fp80", "%la", binary80)

# compound binary floating-point format declaration
ML_DoubleDouble = ML_Compound_FP_Format("ml_dd_t", ["hi", "lo"], [ML_Binary64, ML_Binary64], "", "", doubledouble)
ML_TripleDouble = ML_Compound_FP_Format("ml_td_t", ["hi", "me", "lo"], [ML_Binary64, ML_Binary64, ML_Binary64], "", "", tripledouble)

# Standard integer format declarations
ML_Int8    = ML_Standard_FixedPoint_Format(8, 0, True)
ML_UInt8   = ML_Standard_FixedPoint_Format(8, 0, False)

ML_Int16    = ML_Standard_FixedPoint_Format(16, 0, True)
ML_UInt16   = ML_Standard_FixedPoint_Format(16, 0, False)

ML_Int32    = ML_Standard_FixedPoint_Format(32, 0, True)
ML_UInt32   = ML_Standard_FixedPoint_Format(32, 0, False)

ML_Int64    = ML_Standard_FixedPoint_Format(64, 0, True)
ML_UInt64   = ML_Standard_FixedPoint_Format(64, 0, False)

ML_Int128    = ML_Standard_FixedPoint_Format(128, 0, True)
ML_UInt128   = ML_Standard_FixedPoint_Format(128, 0, False)


def is_std_integer_format(precision):
  return precision in [ML_Int8,ML_UInt8,ML_Int16,ML_UInt16,ML_Int32,ML_UInt32,ML_Int64,ML_UInt64,ML_Int128,ML_UInt128]

def get_std_integer_support_format(precision):
  """ return the ML's integer format to contains
      the fixed-point format precision """
  assert(isinstance(precision, ML_Fixed_Format))
  format_map = {
    # signed
    True: {
      8: ML_Int8,
      16: ML_Int16,
      32: ML_Int32,
      64: ML_Int64,
      128: ML_Int128,
    },
    # unsigned
    False: {
      8: ML_UInt8,
      16: ML_UInt16,
      32: ML_UInt32,
      64: ML_UInt64,
      128: ML_UInt128,
    },
  }
  return format_map[precision.get_signed()][precision.get_c_bit_size()]



# abstract formats
ML_Integer  = AbstractFormat_Builder("ML_Integer",  (ML_Fixed_Format,))("ML_Integer")
ML_Float    = AbstractFormat_Builder("ML_Float",    (ML_FP_Format,))("ML_Float")
ML_Bool     = AbstractFormat_Builder("ML_Bool",     (ML_Bool_Format,))("ML_Bool")


###############################################################################
#                     FLOATING-POINT SPECIAL VALUES
###############################################################################
class FP_SpecialValue(object): 
    """ parent to all floating-point constants """
    suffix_table = {
        ML_Binary32: ".f",
        ML_Binary64: ".d",
    }
    support_prefix = {
        ML_Binary32: "fp32",
        ML_Binary64: "fp64",
    }

def FP_SpecialValue_get_c_cst(self):
    prefix = self.support_prefix[self.precision]
    suffix = self.suffix_table[self.precision]
    return prefix + self.ml_support_name + suffix

def FP_SpecialValue_init(self, precision):
    self.precision = precision

def FP_SpecialValue_get_str(self):
    return "%s" % (self.ml_support_name)

def FP_SpecialValueBuilder(special_value):
    attr_map = {
        "ml_support_name": special_value, 
        "__str__": FP_SpecialValue_get_str,
        "get_precision": lambda self: self.precision,
        "__init__": FP_SpecialValue_init,
        "get_c_cst": FP_SpecialValue_get_c_cst 
    
    }
    return type(special_value, (FP_SpecialValue,), attr_map)

class FP_PlusInfty(FP_SpecialValueBuilder("_sv_PlusInfty")): 
    pass
class FP_MinusInfty(FP_SpecialValueBuilder("_sv_MinusInfty")): 
    pass
class FP_PlusOmega(FP_SpecialValueBuilder("_sv_PlusOmega")): 
    pass
class FP_MinusOmega(FP_SpecialValueBuilder("_sv_MinusOmega")): 
    pass
class FP_PlusZero(FP_SpecialValueBuilder("_sv_PlusZero")): 
    pass
class FP_MinusZero(FP_SpecialValueBuilder("_sv_MinusZero")): 
    pass
class FP_QNaN(FP_SpecialValueBuilder("_sv_QNaN")): 
    pass
class FP_SNaN(FP_SpecialValueBuilder("_sv_SNaN")): 
    pass


class FP_Context:
    """ Floating-Point context """
    def __init__(self, rounding_mode = ML_GlobalRoundMode, silent = None):
        self.rounding_mode       = rounding_mode
        self.init_ev_value       = None
        self.init_rnd_mode_value = None
        self.silent              = silent

    def get_rounding_mode(self):
        return self.rounding_mode

    def get_silent(self):
        return self.silent

class ML_FunctionPrecision:
    pass

class ML_Faithful(ML_FunctionPrecision):
    pass

class ML_CorrectlyRounded(ML_FunctionPrecision):
    pass

class ML_DegradedAccuracyAbsolute(ML_FunctionPrecision):
    """ absolute error accuracy """
    def __init__(self, absolute_goal):
        self.goal = absolute_goal

class ML_DegradedAccuracyRelative(ML_FunctionPrecision):
    """ relative error accuracy """
    def __init__(self, relative_goal):
        self.goal = relative_goal


# degraded accuracy shorcuts
def daa(*args, **kwords):
    return ML_DegradedAccuracyAbsolute(*args, **kwords)
def dar(*args, **kwords):
    return ML_DegradedAccuracyRelative(*args, **kwords)
