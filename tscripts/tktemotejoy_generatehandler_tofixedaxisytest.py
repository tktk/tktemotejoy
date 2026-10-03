from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_tofixedaxisytest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : {
        'generatehandler' : [
            'tofixedaxisytest.cpp',
        ],
    },
    SOURCE_ROOT_DIR : [
        {
            'generatehandler' : [
                'tofixedaxisy.cpp',
            ],
            'handler' : {
                'forpspstate' : [
                    'tofixedaxisy.cpp',
                    'dummy.cpp',
                ],
                'forchangemapping' : [
                    'dummy.cpp',
                ],
            },
        },
        'mapping.cpp',
        'pspstate.cpp',
    ],
}
