# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_mappingnamestest'

module.SOURCE = [
    'mappingnamestest.cpp',
    'mappingnames.cpp',
    'mappingnameerror.cpp',
]
