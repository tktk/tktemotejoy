# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_pspstate_difftest'

module.SOURCE = [
    'pspstate_difftest.cpp',
    'pspstate.cpp',
]
