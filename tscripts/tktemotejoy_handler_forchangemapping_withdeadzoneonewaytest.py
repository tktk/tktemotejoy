# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forchangemapping_withdeadzoneonewaytest'

module.SOURCE = [
    {
        'handler' : {
            'forchangemapping' : [
                'withdeadzoneonewaytest.cpp',
                'dummy.cpp',
            ],
            'forpspstate' : [
                'dummy.cpp',
            ],
        },
    },
    'mapping.cpp',
]
