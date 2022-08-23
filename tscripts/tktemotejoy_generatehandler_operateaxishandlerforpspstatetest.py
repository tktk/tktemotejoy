# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_operateaxishandlerforpspstatetest'

module.SOURCE = [
    {
        'generatehandler' : [
            'operateaxishandlerforpspstatetest.cpp',
            'operateaxishandlerforpspstate.cpp',
            'toaxisx.cpp',
            'toaxisy.cpp',
        ],
        'handler' : {
            'forpspstate' : [
                'toaxisx.cpp',
                'toaxisy.cpp',
                'jseventaxistopspstateaxis.cpp',
            ],
        },
    },
    'pspstate.cpp',
    'mapping.cpp',
]
