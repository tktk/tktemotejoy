from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_tobuttonhandlerforchangemappingtest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : {
        'generatehandler' : [
            'tobuttonhandlerforchangemappingtest.cpp',
        ],
    },
    SOURCE_ROOT_DIR : [
        {
            'generatehandler' : [
                'tobuttonhandlerforchangemapping.cpp',
                'pressbuttonhandlerforchangemapping.cpp',
                'togglemapping.cpp',
                'shiftmapping.cpp',
            ],
            'handler' : {
                'forchangemapping' : [
                    'tobuttonhandler.cpp',
                    'togglemapping.cpp',
                    'shiftmapping.cpp',
                    'dummy.cpp',
                ],
                'forpspstate' : [
                    'dummy.cpp',
                ],
                'common' : [
                    'calcrangedirection.cpp',
                ],
            },
        },
        'mapping.cpp',
        'mappingnames.cpp',
        'typeerror.cpp',
        'mappingnameerror.cpp',
    ],
}
