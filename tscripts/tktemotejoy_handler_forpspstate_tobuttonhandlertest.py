# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forpspstate_tobuttonhandlertest'

module.SOURCE = [
    {
        'handler' : {
            'forpspstate' : [
                'tobuttonhandlertest.cpp',
                'tobuttonhandler.cpp',
                'dummy.cpp',
            ],
            'forchangemapping' : [
                'dummy.cpp',
            ],
            'common' : [
                'calcrangedirection.cpp',
            ],
        },
    },
    'mapping.cpp',
    'pspstate.cpp',
]
