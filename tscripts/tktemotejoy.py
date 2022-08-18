# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.DEPENDS = [
    'tktemotejoy_joystickstate_forpressedbuttonstest',
    'tktemotejoy_joystickstate_foraxestest',
    'tktemotejoy_pspstate_difftest',
    'tktemotejoy_handler_forpspstate_tobuttonstest',
    'tktemotejoy_handler_forpspstate_tofixedaxisxtest',
    'tktemotejoy_handler_forpspstate_tofixedaxisytest',
    'tktemotejoy_handler_forpspstate_withdeadzonetest',
    'tktemotejoy_handler_forpspstate_toaxisxtest',
    'tktemotejoy_handler_forpspstate_toaxisytest',
    'tktemotejoy_handler_forpspstate_tobuttonhandlerstest',
    'tktemotejoy_handler_forchangemapping_shiftmappingtest',
    'tktemotejoy_handler_forchangemapping_togglemappingtest',
    'tktemotejoy_handler_forchangemapping_withdeadzonetest',
    'tktemotejoy_handler_forchangemapping_tochangemappinghandlerstest',
    'tktemotejoy_mapping_pressbuttonforpspstatetest',
    'tktemotejoy_mapping_operateaxisforpspstatetest',
    'tktemotejoy_mapping_pressbuttonforchangemappingtest',
    'tktemotejoy_mapping_operateaxisforchangemappingtest',
    'tktemotejoy_mappings_joystickstatetopspstatetest',
    'tktemotejoy_common_jseventaxistopspstateaxistest',
]

module.BUILDER = cpp.program

module.TARGET = 'tktemotejoy'

module.SOURCE = [
    'main.cpp',
    'joystickstate.cpp',
    'pspstate.cpp',
    'mapping.cpp',
    'mappings.cpp',
    'common.cpp',
    {
        'handler' : {
            'forpspstate' : [
                'tobuttons.cpp',
                'tofixedaxisx.cpp',
                'tofixedaxisy.cpp',
                'toaxisx.cpp',
                'toaxisy.cpp',
            ],
            'forchangemapping' : [
                'shiftmapping.cpp',
                'togglemapping.cpp',
            ],
        },
    },
]
