from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forpspstate_tobuttonhandlertest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : {
        'handler' : {
            'forpspstate' : [
                'tobuttonhandlertest.cpp',
            ],
        },
    },
    SOURCE_ROOT_DIR : [
        {
            'handler' : {
                'forpspstate' : [
                    'tobuttonhandler.cpp',
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
