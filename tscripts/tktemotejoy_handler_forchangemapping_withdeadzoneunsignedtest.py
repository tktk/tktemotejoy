# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forchangemapping_withdeadzoneunsignedtest'

module.SOURCE = [
    {
        'handler' : {
            'forchangemapping' : [
                'withdeadzoneunsignedtest.cpp',
            ],
            'forpspstate' : [
                'dummy.cpp',
            ],
        },
    },
    'mapping.cpp',
]
