# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.BUILDER = cpp.program

module.TARGET = 'benchmark'

module.SOURCE = [
    'benchmark.cpp',
    'file.cpp',
    'customjson.cpp',
    'generatemappings.cpp',
    'mappings.cpp',
    'mapping.cpp',
    'joystickstate.cpp',
    'pspstate.cpp',
    'tousbhostfs.cpp',
    'joystick.cpp',
    'descriptorcloser.cpp',
    'typeerror.cpp',
    {
        'generatehandler' : [
            'tobuttons.cpp',
            'pressbuttonhandlerforpspstate.cpp',
            'toaxisx.cpp',
            'toaxisy.cpp',
            'tofixedaxisx.cpp',
            'tofixedaxisy.cpp',
            'tobuttonhandlersforpspstate.cpp',
            'tobuttonhandlerforpspstate.cpp',
            'operateaxishandlerforpspstate.cpp',
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
            ],
            'forchangemapping' : [
                'shiftmapping.cpp',
                'togglemapping.cpp',
                'tobuttonhandlers.cpp',
                'tobuttonhandler.cpp',
                'dummy.cpp',
            ],
        },
    },
]
