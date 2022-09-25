# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_pressbuttonhandlerforchangemappingtest'

module.SOURCE = [
    {
        'generatehandler' : [
            'pressbuttonhandlerforchangemappingtest.cpp',
            'pressbuttonhandlerforchangemapping.cpp',
            'shiftmapping.cpp',
            'togglemapping.cpp',
        ],
        'handler' : {
            'forchangemapping' : [
                'shiftmapping.cpp',
                'togglemapping.cpp',
                'dummy.cpp',
            ],
            'forpspstate' : [
                'dummy.cpp',
            ],
        },
    },
    'mapping.cpp',
    'mappingnames.cpp',
    'typeerror.cpp',
    'mappingnameerror.cpp',
]
