from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_toaxistest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : {
        'generatehandler' : [
            'toaxistest.cpp',
        ],
    },
    SOURCE_ROOT_DIR : {
        'handler' : {
            'common' : [
                'calcmintocenter.cpp',
            ],
        },
    },
}
