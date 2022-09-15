# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_tobuttonhandlerforchangemappingtest'

module.SOURCE = [
    {
        'generatehandler' : [
            'tobuttonhandlerforchangemappingtest.cpp',
            'tobuttonhandlerforchangemapping.cpp',
            'pressbuttonhandlerforchangemapping.cpp',
            'togglemapping.cpp',
            'shiftmapping.cpp',
        ],
        'handler' : {
            'forchangemapping' : [
                'tobuttonhandler.cpp',
                'togglemapping.cpp',
                'shiftmapping.cpp',
                'dummy.cpp',
            ],
            'forpspstate' : [
                'dummy.cpp',
            ],
            'common' : [
                'calcrangedirection.cpp',
            ],
        },
    },
    'mapping.cpp',
    'typeerror.cpp',
]
