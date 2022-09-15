# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_evdevstate_foraxestest'

module.SOURCE = [
    'evdevstate_foraxestest.cpp',
    'evdevstate.cpp',
]
