# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forpspstate_withrangeonewaytest'

module.SOURCE = [
    {
        'handler' : {
            'forpspstate' : [
                'withrangeonewaytest.cpp',
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
