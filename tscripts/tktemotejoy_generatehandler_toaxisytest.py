# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_toaxisytest'

module.SOURCE = [
    {
        'generatehandler' : [
            'toaxisytest.cpp',
            'toaxisy.cpp',
        ],
        'handler' : {
            'forpspstate' : [
                'toaxisy.cpp',
                'jseventaxistopspstateaxis.cpp',
                'dummy.cpp',
            ],
            'forchangemapping' : [
                'dummy.cpp',
            ],
        },
    },
    'mapping.cpp',
    'pspstate.cpp',
]
