# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forchangemapping_tochangemappinghandlerstest'

module.SOURCE = [
    {
        'handler' : {
            'forchangemapping' : [
                'tochangemappinghandlerstest.cpp',
                'tochangemappinghandlers.cpp',
            ],
        },
    },
    'mapping.cpp',
]
