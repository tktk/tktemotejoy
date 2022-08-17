# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forpspstate_toaxisxtest'

module.SOURCE = [
    {
        'handler' : {
            'forpspstate' : [
                'toaxisxtest.cpp',
                'toaxisx.cpp',
            ],
        },
    },
    'mapping.cpp',
    'pspstate.cpp',
    #'common.cpp',
]
