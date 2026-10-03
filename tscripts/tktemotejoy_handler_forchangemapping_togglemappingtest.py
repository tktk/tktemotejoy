from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forchangemapping_togglemappingtest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : {
        'handler' : {
            'forchangemapping' : [
                'togglemappingtest.cpp',
            ],
        },
    },
    SOURCE_ROOT_DIR : [
        {
            'handler' : {
                'forchangemapping' : [
                    'togglemapping.cpp',
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
