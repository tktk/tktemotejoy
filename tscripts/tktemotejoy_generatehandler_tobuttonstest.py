# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_tobuttonstest'

module.SOURCE = [
    {
        'generatehandler' : [
            'tobuttonstest.cpp',
            'tobuttons.cpp',
        ],
        'handler' : {
            'forpspstate' : [
                'tobuttons.cpp',
                'dummy.cpp',
            ],
            'forchangemapping' : [
                'dummy.cpp',
            ],
        },
    },
    'pspstate.cpp',
    'mapping.cpp',
]
