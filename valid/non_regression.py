# -*- coding: utf-8 -*-

import commands
import argparse


import metalibm_functions.ml_log10
import metalibm_functions.ml_log1p
import metalibm_functions.ml_log2
import metalibm_functions.ml_log
import metalibm_functions.ml_exp

from metalibm_core.core.ml_formats import ML_Binary32, ML_Binary64, ML_Int32
from metalibm_core.core.ml_function import DefaultArgTemplate

class TestResult:
  ## @param result boolean indicating success (True) or failure (False)
  #  @param details string with test information
  def __init__(self, result, details):
    self.result = result
    self.details = details

  def get_result(self):
    return self.result

  def get_details(self):
    return self.details

# Test object for new type meta function
class NewSchemeTest:
  ## @param ctor MetaFunction constructor
  #  @param argument_tc list of argument tests cases (dict)
  def __init__(self, ctor, argument_tc):
    self.ctor = ctor
    self.argument_tc = argument_tc

  def single_test(self, arg_tc):
    function_name = self.ctor.get_name()
    test_desc = "{}/{}".format(function_name, str(arg_tc))
    arg_template = DefaultArgTemplate(**arg_tc) 
    try:
      fct = self.ctor(arg_template)
    except:
      return TestResult(False, "{} ctor failed".format(test_desc))
    try:
      fct.gen_implementation()
    except:
      return TestResult(False, "{} gen_implementation failed".format(test_desc))

    return TestResult(True, "{} succeed".format(test_desc))

  def perform_all_test(self):
    result_list = [self.single_test(tc) for tc in self.argument_tc]
    success_count = [r.get_result() for r in result_list].count(True)
    failure_count = len(result_list) - success_count
    overall_success = (success_count > 0) and (failure_count == 0)
    function_name = self.ctor.get_name()

    if overall_success:
      return TestResult(True, "{} success ! ({}/{})".format(function_name, success_count, len(result_list)))
    else:
      return TestResult(False, "{} success ! ({}/{})\n {}".format(function_name, success_count, len(result_list), "\n".join(r.get_details() for r in result_list)))

# old scheme
old_scheme_function_list = [
  metalibm_functions.ml_log1p.ML_Log1p,
  metalibm_functions.ml_log.ML_Log,
]

# new scheme (ML_Function)
new_scheme_function_list = [
  NewSchemeTest(
    metalibm_functions.ml_log2.ML_Log2,
    [
      {"precision": ML_Binary32}, 
      {"precision": ML_Binary64}
    ]
  ), 
  NewSchemeTest(
    metalibm_functions.ml_log10.ML_Log10,
    [
      {"precision": ML_Binary32}, 
      {"precision": ML_Binary64}
    ]
  ), 
  NewSchemeTest(
    metalibm_functions.ml_exp.ML_Exponential,
    [
      {"precision": ML_Binary32}, 
      {"precision": ML_Binary64},
    ]
  ), 
]

def old_scheme_test(function_ctor, options = []):
  function_name = function_ctor.get_name()
  try: 
    fct = function_ctor()
  except:
    return False
  return True

def new_scheme_test(function_ctor, options = []):
  function_name = function_ctor.get_name()
  fct = function_ctor()
  fct.gen_implementation()
  #try: 
  #except:
  #  return False
  return True


test_list = [(function, old_scheme_test) for function in old_scheme_function_list]
#test_list += [(function, new_scheme_test) for function in new_scheme_function_list]




success = True
result_map = {}
# list of TestResult objects generated by execution
# of new scheme tests
result_details = []

for function, test_function in test_list:
  test_result = test_function(function)
  result_map[function] = test_result 
  success &= test_result


for test_scheme in new_scheme_function_list:
  test_result = test_scheme.perform_all_test()
  result_details.append(test_result)

  success = success and test_result.get_result()

# Printing test summary for old scheme
for function in result_map:
  function_name = function.get_name()
  if not result_map[function]:
    print "%s \033[31;1m FAILED \033[0;m" % function_name
  else:
    print "%s SUCCESS" % function_name

# Printing test summary for new scheme
for result in result_details:
  print result.get_details()

if success:
  print "OVERALL SUCCESS"
  exit(0)
else:
  print "OVERALL FAILURE"
  exit(1)
