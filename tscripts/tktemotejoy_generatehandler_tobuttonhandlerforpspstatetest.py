from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_tobuttonhandlerforpspstatetest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : {
        'generatehandler' : [
            'tobuttonhandlerforpspstatetest.cpp',
        ],
    },
    SOURCE_ROOT_DIR : [
        {
            'generatehandler' : [
                'tobuttonhandlerforpspstate.cpp',
                'pressbuttonhandlerforpspstate.cpp',
                'tobuttons.cpp',
                'tofixedaxisx.cpp',
                'tofixedaxisy.cpp',
            ],
            'handler' : {
                'forpspstate' : [
                    'tobuttonhandler.cpp',
                    'tobuttons.cpp',
                    'tofixedaxisx.cpp',
                    'tofixedaxisy.cpp',
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
        'typeerror.cpp',
    ],
}
