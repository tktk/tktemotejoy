# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

from waflib.Tools import waf_unit_test

import os.path

APPNAME = 'tktemotejoy'
VERSION = '2.0.1'

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

taf.POST_FUNCTIONS = [
    waf_unit_test.summary,
]
