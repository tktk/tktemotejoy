# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_operateaxishandlerforpspstatetest'

module.SOURCE = [
    {
        'generatehandler' : [
            'operateaxishandlerforpspstatetest.cpp',
            'operateaxishandlerforpspstate.cpp',
            'toaxisx.cpp',
            'toaxisy.cpp',
            'tobuttonhandlersforpspstate.cpp',
            'tobuttonhandlerforpspstate.cpp',
            'pressbuttonhandlerforpspstate.cpp',
            'tobuttons.cpp',
            'tofixedaxisx.cpp',
            'tofixedaxisy.cpp',
        ],
        'handler' : {
            'forpspstate' : [
                'toaxisx.cpp',
                'toaxisy.cpp',
                'tobuttonhandlers.cpp',
                'tobuttonhandler.cpp',
                'dummy.cpp',
                'tobuttons.cpp',
                'tofixedaxisx.cpp',
                'tofixedaxisy.cpp',
                'calcpspstateaxis.cpp',
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
    'pspstate.cpp',
    'mapping.cpp',
    'typeerror.cpp',
]
