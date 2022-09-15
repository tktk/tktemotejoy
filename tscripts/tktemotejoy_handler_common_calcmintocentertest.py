# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_common_calcmintocentertest'

module.SOURCE = {
    'handler' : {
        'common' : [
            'calcmintocentertest.cpp',
            'calcmintocenter.cpp',
        ],
    },
}

