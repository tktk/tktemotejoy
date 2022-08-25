# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatemappings_generaltest'

module.SOURCE = [
    'generatemappings_generaltest.cpp',
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
            'pressbuttonhandlerforchangemapping.cpp',
            'shiftmapping.cpp',
            'togglemapping.cpp',
            'tobuttonhandlersforchangemapping.cpp',
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
                'dummy.cpp',
                'jseventaxistopspstateaxis.cpp',
            ],
            'forchangemapping' : [
                'shiftmapping.cpp',
                'togglemapping.cpp',
                'tobuttonhandlers.cpp',
                'dummy.cpp',
            ],
        },
    },
]
