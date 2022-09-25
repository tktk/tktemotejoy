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
    'mappingnames.cpp',
    'evdevstate.cpp',
    'pspstate.cpp',
    'typeerror.cpp',
    'mappingnameerror.cpp',
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
                'calcmintocenter.cpp',
            ],
        },
    },
]
