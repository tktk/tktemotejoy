# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

from waflib.Tools import waf_unit_test

import os.path

APPNAME = 'tktemote'
VERSION = '0.1.1'

out = 'build'

taf.PACKAGE_NAME = 'tktemotejoy'

taf.LOAD_TOOLS = [
    'compiler_cxx',
    'waf_unit_test',
    'taf.tools.cpp',
]

cpp.INCLUDES = [
    os.path.join(
        '..',
        'nlohmann-json',
        'single_include',
    ),
]

CXXFLAGS_GCC_COMMON_DEFAULT = [
    '-Wall',
    '-fvisibility=hidden',
    '-std=c++17',
]

cpp.CXXFLAGS_GCC_DEBUG = CXXFLAGS_GCC_COMMON_DEFAULT + cpp.CXXFLAGS_GCC_DEBUG_DEFAULT
cpp.CXXFLAGS_GCC_RELEASE = CXXFLAGS_GCC_COMMON_DEFAULT + cpp.CXXFLAGS_GCC_RELEASE_DEFAULT

taf.POST_FUNCTIONS = [
    waf_unit_test.summary,
]
