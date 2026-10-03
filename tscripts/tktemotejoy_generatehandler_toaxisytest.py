from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_toaxisytest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : {
        'generatehandler' : [
            'toaxisytest.cpp',
        ],
    },
    SOURCE_ROOT_DIR : [
        {
            'generatehandler' : [
                'toaxisy.cpp',
            ],
            'handler' : {
                'forpspstate' : [
                    'toaxisy.cpp',
                    'calcpspstateaxis.cpp',
                    'dummy.cpp',
                ],
                'forchangemapping' : [
                    'dummy.cpp',
                ],
                'common' : [
                    'calcrangedirection.cpp',
                    'calcmintocenter.cpp',
                ],
            },
        },
        'mapping.cpp',
        'pspstate.cpp',
    ],
}
