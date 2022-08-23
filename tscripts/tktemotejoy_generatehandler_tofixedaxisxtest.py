# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_tofixedaxisxtest'

module.SOURCE = [
    {
        'generatehandler' : [
            'tofixedaxisxtest.cpp',
            'tofixedaxisx.cpp',
        ],
        'handler' : {
            'forpspstate' : [
                'tofixedaxisx.cpp',
                'jseventaxistopspstateaxis.cpp',
            ],
        },
    },
    'mapping.cpp',
    'pspstate.cpp',
]
