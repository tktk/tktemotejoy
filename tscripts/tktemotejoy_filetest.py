# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.DEPENDS = [
    'tktemotejoy_testdata_filetest',
]

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_filetest'

module.SOURCE = [
    'filetest.cpp',
    'file.cpp',
]
