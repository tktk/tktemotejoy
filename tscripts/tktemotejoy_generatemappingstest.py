# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatemappingstest'

module.SOURCE = [
    'generatemappingstest.cpp',
    'generatemappings.cpp',
    'mappings.cpp',
    'mapping.cpp',
    'joystickstate.cpp',
    'pspstate.cpp',
    'typeerror.cpp',
    {
        'generatehandler' : [
            'pressbuttonhandlerforpspstate.cpp',
            'tobuttons.cpp',
            'operateaxishandlerforpspstate.cpp',
            'toaxisx.cpp',
            'toaxisy.cpp',
            'tofixedaxisx.cpp',
            'tofixedaxisy.cpp',
            'tobuttonhandlersforpspstate.cpp',
            'tobuttonhandlerforpspstate.cpp',
            'pressbuttonhandlerforchangemapping.cpp',
            'shiftmapping.cpp',
            'togglemapping.cpp',
            'tobuttonhandlersforchangemapping.cpp',
            'tobuttonhandlerforchangemapping.cpp',
            'operateaxishandlerforchangemapping.cpp',
        ],
        'handler' : {
            'forpspstate' : [
                'tobuttons.cpp',
                'toaxisx.cpp',
                'toaxisy.cpp',
                'tofixedaxisx.cpp',
                'tofixedaxisy.cpp',
                'tobuttonhandlers.cpp',
                'tobuttonhandler.cpp',
                'dummy.cpp',
                'calcpspstateaxis.cpp',
            ],
            'forchangemapping' : [
                'shiftmapping.cpp',
                'togglemapping.cpp',
                'tobuttonhandlers.cpp',
                'tobuttonhandler.cpp',
                'dummy.cpp',
            ],
            'common' : [
                'calcrangedirection.cpp',
            ],
        },
    },
]
