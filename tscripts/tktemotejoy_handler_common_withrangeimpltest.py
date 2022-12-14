# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_common_withrangeimpltest'

module.SOURCE = {
    'handler' : {
        'common' : [
            'withrangeimpltest.cpp',
            'calcrangedirection.cpp',
            'calcmintocenter.cpp',
        ],
    },
}

