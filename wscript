import tscripts
from taf import *
from taf.tools import cpp

from waflib.Tools import waf_unit_test

APPNAME = tscripts.PACKAGE_NAME
VERSION = '5.0.0'

out = 'build'

taf.PACKAGE_NAME = tscripts.PACKAGE_NAME

taf.LOAD_TOOLS = [
    'compiler_cxx',
    'waf_unit_test',
    'taf.tools.cpp',
]

cpp.INCLUDES = [
    tscripts.HEADER_DIR,
]

cpp.TEST_INCLUDES = [
    tscripts.TEST_HEADER_DIR,
]

taf.POST_FUNCTIONS = [
    waf_unit_test.summary,
]
