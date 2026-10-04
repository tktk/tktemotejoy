from . import SOURCE_ROOT_DIR
from . import TEST_SOURCE_ROOT_DIR
from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_generatehandler_operateaxishandlerforchangemappingtest'

module.SOURCE = {
    TEST_SOURCE_ROOT_DIR : {
        'generatehandler' : [
            'operateaxishandlerforchangemappingtest.cpp',
        ],
    },
    SOURCE_ROOT_DIR : [
        {
            'generatehandler' : [
                'operateaxishandlerforchangemapping.cpp',
                'tobuttonhandlersforchangemapping.cpp',
                'tobuttonhandlerforchangemapping.cpp',
                'pressbuttonhandlerforchangemapping.cpp',
                'shiftmapping.cpp',
                'togglemapping.cpp',
            ],
            'handler' : {
                'forchangemapping' : [
                    'tobuttonhandlers.cpp',
                    'tobuttonhandler.cpp',
                    'shiftmapping.cpp',
                    'togglemapping.cpp',
                    'dummy.cpp',
                ],
                'forpspstate' : [
                    'dummy.cpp',
                ],
                'common' : [
                    'calcrangedirection.cpp',
                    'calcmintocenter.cpp',
                ],
            },
        },
        'mapping.cpp',
        'mappingnames.cpp',
        'typeerror.cpp',
        'mappingnameerror.cpp',
    ],
}
