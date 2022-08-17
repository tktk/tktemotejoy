# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forpspstate_withdeadzonetest'

module.SOURCE = [
    {
        'handler' : {
            'forpspstate' : [
                'withdeadzonetest.cpp',
            ],
        },
    },
    'mapping.cpp',
    'pspstate.cpp',
]
