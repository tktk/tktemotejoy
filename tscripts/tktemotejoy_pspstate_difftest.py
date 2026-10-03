from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_pspstate_difftest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : [
        'pspstate_difftest.cpp',
    ],
    SOURCE_ROOT_DIR : [
        'pspstate.cpp',
    ],
}
