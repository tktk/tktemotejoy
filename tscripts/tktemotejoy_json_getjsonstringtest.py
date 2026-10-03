from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_json_getjsonstringtest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : [
        'json_getjsonstringtest.cpp',
    ],
}
