# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_shiftmappingtest'

module.SOURCE = [
    {
        'generatehandler' : [
            'shiftmappingtest.cpp',
            'shiftmapping.cpp',
        ],
        'handler' : {
            'forchangemapping' : [
                'shiftmapping.cpp',
                'dummy.cpp',
            ],
            'forpspstate' : [
                'dummy.cpp',
            ],
        },
    },
    'mapping.cpp',
    'mappingnames.cpp',
    'mappingnameerror.cpp',
]
