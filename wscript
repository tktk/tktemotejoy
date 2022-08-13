# -*- coding: utf-8 -*-

from taf import *

from waflib.Tools import waf_unit_test

APPNAME = 'tktemote'
VERSION = '0.1.0'

out = 'build'

taf.PACKAGE_NAME = 'tktemotejoy'

taf.LOAD_TOOLS = [
    'compiler_cxx',
    'waf_unit_test',
    'taf.tools.cpp',
]

taf.POST_FUNCTIONS = [
    waf_unit_test.summary,
]
