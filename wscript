# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

from waflib.Tools import waf_unit_test

import os.path

APPNAME = 'tktemotejoy'
VERSION = '4.4.0'

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
        'tktusbrepeater',
        'inc',
    ),
    os.path.join(
        '..',
        'nlohmann-json',
        'single_include',
    ),
]

cpp.LIBPATH = [
    os.path.join(
        '..',
        'tktusbrepeater',
        'build',
        'tktusbrepeater',
    ),
]

taf.POST_FUNCTIONS = [
    waf_unit_test.summary,
]
