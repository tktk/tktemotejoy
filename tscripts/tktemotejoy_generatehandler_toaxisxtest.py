# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_toaxisxtest'

module.SOURCE = [
    {
        'generatehandler' : [
            'toaxisxtest.cpp',
            'toaxisx.cpp',
        ],
        'handler' : {
            'forpspstate' : [
                'toaxisx.cpp',
                'calcpspstateaxis.cpp',
                'dummy.cpp',
            ],
            'forchangemapping' : [
                'dummy.cpp',
            ],
            'common' : [
                'calcrangedirection.cpp',
                'calcmintocenter.cpp',
            ],
        },
    },
    'mapping.cpp',
    'pspstate.cpp',
]
