# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_mapping_operateaxisforpspstatetest'

module.SOURCE = [
    'mapping_operateaxisforpspstatetest.cpp',
    'mapping.cpp',
    'pspstate.cpp',
    {
        'handler' : {
            'forpspstate' : [
                'dummy.cpp',
            ],
        },
    },
]
