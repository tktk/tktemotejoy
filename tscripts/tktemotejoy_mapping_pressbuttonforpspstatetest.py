# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_mapping_pressbuttonforpspstatetest'

module.SOURCE = [
    'mapping_pressbuttonforpspstatetest.cpp',
    'mapping.cpp',
]
