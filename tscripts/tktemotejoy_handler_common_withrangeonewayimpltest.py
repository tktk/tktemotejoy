# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_common_withrangeonewayimpltest'

module.SOURCE = {
    'handler' : {
        'common' : [
            'withrangeonewayimpltest.cpp',
            'calcrangedirection.cpp',
        ],
    },
}

