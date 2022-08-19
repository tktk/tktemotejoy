# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_customjson_parsetest'

module.SOURCE = [
    'customjson_parsetest.cpp',
    'customjson.cpp',
]
