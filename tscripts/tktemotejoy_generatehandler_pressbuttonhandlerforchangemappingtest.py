from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_pressbuttonhandlerforchangemappingtest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : {
        'generatehandler' : [
            'pressbuttonhandlerforchangemappingtest.cpp',
        ],
    },
    SOURCE_ROOT_DIR : [
        {
            'generatehandler' : [
                'pressbuttonhandlerforchangemapping.cpp',
                'shiftmapping.cpp',
                'togglemapping.cpp',
            ],
            'handler' : {
                'forchangemapping' : [
                    'shiftmapping.cpp',
                    'togglemapping.cpp',
                    'dummy.cpp',
                ],
                'forpspstate' : [
                    'dummy.cpp',
                ],
            },
        },
        'mapping.cpp',
        'mappingnames.cpp',
        'typeerror.cpp',
        'mappingnameerror.cpp',
    ],
}
