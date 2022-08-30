# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_mappings_joystickstatetopspstatetest'

module.SOURCE = [
    'mappings_joystickstatetopspstatetest.cpp',
    'mappings.cpp',
    'mapping.cpp',
    'joystickstate.cpp',
    'pspstate.cpp',
    {
        'handler' : {
            'forpspstate' : [
                'tobuttons.cpp',
                'tofixedaxisx.cpp',
                'toaxisy.cpp',
                'tobuttonhandlers.cpp',
                'jseventaxistopspstateaxis.cpp',
                'dummy.cpp',
            ],
            'forchangemapping' : [
                'shiftmapping.cpp',
                'togglemapping.cpp',
                'tobuttonhandlers.cpp',
            ],
        },
    },
]
