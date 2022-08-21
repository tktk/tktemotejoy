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
    'tktemotejoy_handler_forpspstate_jseventaxistopspstateaxistest',
    'tktemotejoy_handler_forchangemapping_shiftmappingtest',
    'tktemotejoy_handler_forchangemapping_togglemappingtest',
    'tktemotejoy_handler_forchangemapping_withdeadzonetest',
    'tktemotejoy_handler_forchangemapping_tochangemappinghandlerstest',
    'tktemotejoy_mapping_pressbuttonforpspstatetest',
    'tktemotejoy_mapping_operateaxisforpspstatetest',
    'tktemotejoy_mapping_pressbuttonforchangemappingtest',
    'tktemotejoy_mapping_operateaxisforchangemappingtest',
    'tktemotejoy_mappings_joystickstatetopspstatetest',
    'tktemotejoy_customjson_parsetest',
    'tktemotejoy_generatehandler_generatehandleruniquetest',
    'tktemotejoy_generatehandler_tobuttonstest',
    'tktemotejoy_generatehandler_pressbuttonhandlerforpspstatetest',
    'tktemotejoy_generatemappingstest',
    'tktemotejoy_generatemappings_generaltest',
    'tktemotejoy_generatemappings_mappingstest',
    'tktemotejoy_jsonerrortest',
]

module.BUILDER = cpp.program

module.TARGET = 'tktemotejoy'

module.SOURCE = [
    'main.cpp',
    'joystickstate.cpp',
    'pspstate.cpp',
    'mapping.cpp',
    'mappings.cpp',
    {
        'handler' : {
            'forpspstate' : [
                'tobuttons.cpp',
                'tofixedaxisx.cpp',
                'tofixedaxisy.cpp',
                'toaxisx.cpp',
                'toaxisy.cpp',
                'jseventaxistopspstateaxis.cpp',
            ],
            'forchangemapping' : [
                'shiftmapping.cpp',
                'togglemapping.cpp',
            ],
        },
    },
]
