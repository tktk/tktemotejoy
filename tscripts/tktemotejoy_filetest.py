from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_filetest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : [
        'filetest.cpp',
    ],
}
