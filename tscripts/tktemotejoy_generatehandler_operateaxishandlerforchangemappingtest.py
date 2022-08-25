# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_operateaxishandlerforchangemappingtest'

module.SOURCE = [
    {
        'generatehandler' : [
            'operateaxishandlerforchangemappingtest.cpp',
            'operateaxishandlerforchangemapping.cpp',
            'tobuttonhandlersforchangemapping.cpp',
            'pressbuttonhandlerforchangemapping.cpp',
            'shiftmapping.cpp',
            'togglemapping.cpp',
        ],
        'handler' : {
            'forchangemapping' : [
                'tobuttonhandlers.cpp',
                'shiftmapping.cpp',
                'togglemapping.cpp',
                'dummy.cpp',
            ],
        },
    },
    'mapping.cpp',
    'typeerror.cpp',
]
