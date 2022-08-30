# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forpspstate_withdeadzoneunsignedtest'

module.SOURCE = [
    {
        'handler' : {
            'forpspstate' : [
                'withdeadzoneunsignedtest.cpp',
                'dummy.cpp',
            ],
        },
    },
    'mapping.cpp',
    'pspstate.cpp',
]
