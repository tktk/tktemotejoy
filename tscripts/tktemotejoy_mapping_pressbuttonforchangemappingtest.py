# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_mapping_pressbuttonforchangemappingtest'

module.SOURCE = [
    'mapping_pressbuttonforchangemappingtest.cpp',
    'mapping.cpp',
    {
        'handler' : {
            'forpspstate' : [
                'dummy.cpp',
            ],
            'forchangemapping' : [
                'dummy.cpp',
            ],
        },
    },
]
