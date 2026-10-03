from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_shiftmappingtest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : {
        'generatehandler' : [
            'shiftmappingtest.cpp',
        ],
    },
    SOURCE_ROOT_DIR : [
        {
            'generatehandler' : [
                'shiftmapping.cpp',
            ],
            'handler' : {
                'forchangemapping' : [
                    'shiftmapping.cpp',
                    'dummy.cpp',
                ],
                'forpspstate' : [
                    'dummy.cpp',
                ],
            },
        },
        'mapping.cpp',
        'mappingnames.cpp',
        'mappingnameerror.cpp',
    ],
}
