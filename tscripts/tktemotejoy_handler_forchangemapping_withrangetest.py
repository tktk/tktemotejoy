from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forchangemapping_withrangetest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : {
        'handler' : {
            'forchangemapping' : [
                'withrangetest.cpp',
            ],
        },
    },
    SOURCE_ROOT_DIR : [
        {
            'handler' : {
                'forchangemapping' : [
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
        'pspstate.cpp',
    ],
}
