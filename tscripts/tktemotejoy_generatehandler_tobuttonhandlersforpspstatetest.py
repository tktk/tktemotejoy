# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_tobuttonhandlersforpspstatetest'

module.SOURCE = [
    {
        'generatehandler' : [
            'tobuttonhandlersforpspstatetest.cpp',
            'tobuttonhandlersforpspstate.cpp',
        ],
    },
    'mapping.cpp',
    'pspstate.cpp',
]
