# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_tobuttonhandlersforpspstatetest'

module.SOURCE = [
    {
        'generatehandler' : [
            'tobuttonhandlersforpspstatetest.cpp',
            'tobuttonhandlersforpspstate.cpp',
            'pressbuttonhandlerforpspstate.cpp',
            'tobuttons.cpp',
            'tofixedaxisx.cpp',
            'tofixedaxisy.cpp',
        ],
        'handler' : {
            'forpspstate' : [
                'tobuttonhandlers.cpp',
                'tobuttons.cpp',
                'tofixedaxisx.cpp',
                'tofixedaxisy.cpp',
                'jseventaxistopspstateaxis.cpp',
                'dummy.cpp',
            ],
        },
    },
    'mapping.cpp',
    'pspstate.cpp',
]
