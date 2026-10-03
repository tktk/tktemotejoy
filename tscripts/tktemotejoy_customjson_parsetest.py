from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_customjson_parsetest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : [
        'customjson_parsetest.cpp',
    ],
    SOURCE_ROOT_DIR : [
        'customjson.cpp',
    ],
}
