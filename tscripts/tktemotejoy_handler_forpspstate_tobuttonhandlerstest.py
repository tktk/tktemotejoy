# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forpspstate_tobuttonhandlerstest'

module.SOURCE = [
    {
        'handler' : {
            'forpspstate' : [
                'tobuttonhandlerstest.cpp',
                'tobuttonhandlers.cpp',
            ],
        },
    },
    'mapping.cpp',
    'pspstate.cpp',
]