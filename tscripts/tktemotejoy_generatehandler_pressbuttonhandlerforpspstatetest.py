# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_pressbuttonhandlerforpspstatetest'

module.SOURCE = [
    {
        'generatehandler' : [
            'pressbuttonhandlerforpspstatetest.cpp',
            'pressbuttonhandlerforpspstate.cpp',
            'tobuttons.cpp',
            'tofixedaxisx.cpp',
            'tofixedaxisy.cpp',
        ],
        'handler' : {
            'forpspstate' : [
                'tobuttons.cpp',
                'tofixedaxisx.cpp',
                'tofixedaxisy.cpp',
                'jseventaxistopspstateaxis.cpp',
            ],
        },
    },
    'pspstate.cpp',
    'mapping.cpp',
    'typeerror.cpp',
]
