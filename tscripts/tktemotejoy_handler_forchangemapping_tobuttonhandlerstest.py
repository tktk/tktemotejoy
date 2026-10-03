from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forchangemapping_tobuttonhandlerstest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : {
        'handler' : {
            'forchangemapping' : [
                'tobuttonhandlerstest.cpp',
            ],
        },
    },
    SOURCE_ROOT_DIR : [
        {
            'handler' : {
                'forchangemapping' : [
                    'tobuttonhandlers.cpp',
                    'dummy.cpp',
                ],
                'forpspstate' : [
                    'dummy.cpp',
                ],
                'common' : [
                    'calcrangedirection.cpp',
                    'calcmintocenter.cpp',
                ],
            },
        },
        'mapping.cpp',
    ],
}
