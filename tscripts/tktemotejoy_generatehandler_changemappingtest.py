# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_changemappingtest'

module.SOURCE = [
    {
        'generatehandler' : [
            'changemappingtest.cpp',
        ],
    },
    'mappingnames.cpp',
    'mappingnameerror.cpp',
]
