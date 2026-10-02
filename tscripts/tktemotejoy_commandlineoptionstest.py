from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_commandlineoptionstest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : [
        'commandlineoptionstest.cpp',
    ],
    SOURCE_ROOT_DIR : [
        'commandlineoptions.cpp',
    ],
}
