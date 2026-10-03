from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_mapping_pressbuttonforpspstatetest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : [
        'mapping_pressbuttonforpspstatetest.cpp',
    ],
    SOURCE_ROOT_DIR : [
        'mapping.cpp',
        'pspstate.cpp',
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
