from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_mapping_operateaxisforchangemappingtest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : [
        'mapping_operateaxisforchangemappingtest.cpp',
    ],
    SOURCE_ROOT_DIR : [
        'mapping.cpp',
        {
            'handler' : {
                'forpspstate' : [
                    'dummy.cpp',
                ],
                'forchangemapping' : [
                    'dummy.cpp',
                ],
            },
        },
    ],
}
