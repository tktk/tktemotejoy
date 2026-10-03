from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_common_withrangeonewayimpltest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : {
        'handler' : {
            'common' : [
                'withrangeonewayimpltest.cpp',
            ],
        },
    },
    SOURCE_ROOT_DIR : {
        'handler' : {
            'common' : [
                'calcrangedirection.cpp',
            ],
        },
    },
}
