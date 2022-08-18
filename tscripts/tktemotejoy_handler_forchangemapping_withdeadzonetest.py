# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forchangemapping_withdeadzonetest'

module.SOURCE = [
    {
        'handler' : {
            'forchangemapping' : [
                'withdeadzonetest.cpp',
            ],
        },
    },
    'mapping.cpp',
]
