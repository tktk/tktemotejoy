from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forpspstate_withrangeonewaytest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : {
        'handler' : {
            'forpspstate' : [
                'withrangeonewaytest.cpp',
            ],
        },
    },
    SOURCE_ROOT_DIR : [
        {
            'handler' : {
                'forpspstate' : [
                    'dummy.cpp',
                ],
                'forchangemapping' : [
                    'dummy.cpp',
                ],
                'common' : [
                    'calcrangedirection.cpp',
                ],
            },
        },
        'mapping.cpp',
        'pspstate.cpp',
    ],
}
