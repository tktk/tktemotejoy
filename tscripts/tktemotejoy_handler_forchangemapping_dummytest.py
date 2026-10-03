from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forchangemapping_dummytest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : {
        'handler' : {
            'forchangemapping' : [
                'dummytest.cpp',
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
            },
        },
        'mapping.cpp',
    ],
}
