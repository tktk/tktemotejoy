# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forpspstate_withrangetest'

module.SOURCE = [
    {
        'handler' : {
            'forpspstate' : [
                'withrangetest.cpp',
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
