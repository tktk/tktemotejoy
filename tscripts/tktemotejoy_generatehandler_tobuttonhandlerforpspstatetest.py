# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_tobuttonhandlerforpspstatetest'

module.SOURCE = [
    {
        'generatehandler' : [
            'tobuttonhandlerforpspstatetest.cpp',
            'tobuttonhandlerforpspstate.cpp',
            'pressbuttonhandlerforpspstate.cpp',
            'tobuttons.cpp',
            'tofixedaxisx.cpp',
            'tofixedaxisy.cpp',
        ],
        'handler' : {
            'forpspstate' : [
                'tobuttonhandler.cpp',
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
    'typeerror.cpp',
]
