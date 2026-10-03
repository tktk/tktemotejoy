from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_pressbuttonhandlerforpspstatetest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : {
        'generatehandler' : [
            'pressbuttonhandlerforpspstatetest.cpp',
        ],
    },
    SOURCE_ROOT_DIR : [
        {
            'generatehandler' : [
                'pressbuttonhandlerforpspstate.cpp',
                'tobuttons.cpp',
                'tofixedaxisx.cpp',
                'tofixedaxisy.cpp',
            ],
            'handler' : {
                'forpspstate' : [
                    'tobuttons.cpp',
                    'tofixedaxisx.cpp',
                    'tofixedaxisy.cpp',
                    'dummy.cpp',
                ],
                'forchangemapping' : [
                    'dummy.cpp',
                ],
            },
        },
        'pspstate.cpp',
        'mapping.cpp',
        'typeerror.cpp',
    ],
}
