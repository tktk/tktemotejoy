from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_evdevstate_forpressedbuttonstest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : [
        'evdevstate_forpressedbuttonstest.cpp',
    ],
    SOURCE_ROOT_DIR : [
    'evdevstate.cpp',
    ],
}
