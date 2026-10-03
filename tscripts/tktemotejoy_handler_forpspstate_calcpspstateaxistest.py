from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forpspstate_calcpspstateaxistest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : {
        'handler' : {
            'forpspstate' : [
                'calcpspstateaxistest.cpp',
            ],
        },
    },
    SOURCE_ROOT_DIR : {
        'handler' : {
            'forpspstate' : [
                'calcpspstateaxis.cpp',
            ],
        },
    },
}
