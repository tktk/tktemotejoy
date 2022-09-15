# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_mappings_evdevstatetopspstatetest'

module.SOURCE = [
    'mappings_evdevstatetopspstatetest.cpp',
    'mappings.cpp',
    'mapping.cpp',
    'evdevstate.cpp',
    'pspstate.cpp',
    {
        'handler' : {
            'forpspstate' : [
                'tobuttons.cpp',
                'tofixedaxisx.cpp',
                'toaxisy.cpp',
                'tobuttonhandlers.cpp',
                'calcpspstateaxis.cpp',
                'dummy.cpp',
            ],
            'forchangemapping' : [
                'shiftmapping.cpp',
                'togglemapping.cpp',
                'tobuttonhandlers.cpp',
                'dummy.cpp',
            ],
            'common' : [
                'calcrangedirection.cpp',
                'calcmintocenter.cpp',
            ],
        },
    },
]
