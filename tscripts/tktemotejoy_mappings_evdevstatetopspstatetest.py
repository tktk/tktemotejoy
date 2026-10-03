from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_mappings_evdevstatetopspstatetest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : [
        'mappings_evdevstatetopspstatetest.cpp',
    ],
    SOURCE_ROOT_DIR : [
        'mappings.cpp',
        'mapping.cpp',
        'evdevstate.cpp',
        'pspstate.cpp',
        {
            'handler' : {
                'forpspstate' : [
                    'tobuttons.cpp',
                    'tofixedaxisx.cpp',
                    'toaxisy.cpp',
                    'tobuttonhandlers.cpp',
                    'calcpspstateaxis.cpp',
                    'dummy.cpp',
                ],
                'forchangemapping' : [
                    'shiftmapping.cpp',
                    'togglemapping.cpp',
                    'tobuttonhandlers.cpp',
                    'dummy.cpp',
                ],
                'common' : [
                    'calcrangedirection.cpp',
                    'calcmintocenter.cpp',
                ],
            },
        },
    ],
}
