# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forpspstate_tofixedaxisytest'

module.SOURCE = [
    {
        'handler' : {
            'forpspstate' : [
                'tofixedaxisytest.cpp',
                'tofixedaxisy.cpp',
            ],
        },
    },
    'mapping.cpp',
    'pspstate.cpp',
    'common.cpp',
]
