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
                'jseventaxistopspstateaxis.cpp',
            ],
        },
    },
    'mapping.cpp',
    'pspstate.cpp',
]
