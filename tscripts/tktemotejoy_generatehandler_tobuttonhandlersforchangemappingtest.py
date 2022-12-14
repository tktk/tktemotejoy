# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_tobuttonhandlersforchangemappingtest'

module.SOURCE = [
    {
        'generatehandler' : [
            'tobuttonhandlersforchangemappingtest.cpp',
            'tobuttonhandlersforchangemapping.cpp',
            'pressbuttonhandlerforchangemapping.cpp',
            'togglemapping.cpp',
            'shiftmapping.cpp',
        ],
        'handler' : {
            'forchangemapping' : [
                'tobuttonhandlers.cpp',
                'togglemapping.cpp',
                'shiftmapping.cpp',
                'dummy.cpp',
            ],
            'forpspstate' : [
                'dummy.cpp',
            ],
            'common' : [
                'calcrangedirection.cpp',
                'calcmintocenter.cpp',
            ],
        },
    },
    'mapping.cpp',
    'mappingnames.cpp',
    'typeerror.cpp',
    'mappingnameerror.cpp',
]
