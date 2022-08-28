# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_json_getjsonunsignedtest'

module.SOURCE = [
    'json_getjsonunsignedtest.cpp',
]
