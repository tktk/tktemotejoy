# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_joystickstate_forpressedbuttonstest'

module.SOURCE = [
    'joystickstate_forpressedbuttonstest.cpp',
    'joystickstate.cpp',
]
