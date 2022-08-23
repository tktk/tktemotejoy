# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.DEPENDS = [
    'tktemotejoy_commandlineoptionstest',
    'tktemotejoy_filetest',
    'tktemotejoy_customjson_parsetest',
    'tktemotejoy_jsonerrortest',
    'tktemotejoy_joystickstate_forpressedbuttonstest',
    'tktemotejoy_joystickstate_foraxestest',
    'tktemotejoy_pspstate_difftest',
    'tktemotejoy_handler_forpspstate_tobuttonstest',
    'tktemotejoy_handler_forpspstate_tofixedaxisxtest',
    'tktemotejoy_handler_forpspstate_tofixedaxisytest',
    'tktemotejoy_handler_forpspstate_dummytest',
    'tktemotejoy_handler_forpspstate_withdeadzonetest',
    'tktemotejoy_handler_forpspstate_toaxisxtest',
    'tktemotejoy_handler_forpspstate_toaxisytest',
    'tktemotejoy_handler_forpspstate_tobuttonhandlerstest',
    'tktemotejoy_handler_forpspstate_jseventaxistopspstateaxistest',
    'tktemotejoy_handler_forchangemapping_shiftmappingtest',
    'tktemotejoy_handler_forchangemapping_togglemappingtest',
    'tktemotejoy_handler_forchangemapping_dummytest',
    'tktemotejoy_handler_forchangemapping_withdeadzonetest',
    'tktemotejoy_handler_forchangemapping_tobuttonhandlerstest',
    'tktemotejoy_mapping_pressbuttonforpspstatetest',
    'tktemotejoy_mapping_operateaxisforpspstatetest',
    'tktemotejoy_mapping_pressbuttonforchangemappingtest',
    'tktemotejoy_mapping_operateaxisforchangemappingtest',
    'tktemotejoy_mappings_joystickstatetopspstatetest',
    'tktemotejoy_generatehandler_generatehandleruniquetest',
    'tktemotejoy_generatehandler_tobuttonstest',
    'tktemotejoy_generatehandler_pressbuttonhandlerforpspstatetest',
    'tktemotejoy_generatehandler_withdeadzonetest',
    'tktemotejoy_generatehandler_toaxistest',
    'tktemotejoy_generatehandler_toaxisxtest',
    'tktemotejoy_generatehandler_toaxisytest',
    'tktemotejoy_generatehandler_operateaxishandlerforpspstatetest',
    'tktemotejoy_generatemappingstest',
    'tktemotejoy_generatemappings_generaltest',
    'tktemotejoy_generatemappings_mappingstest',
]

module.BUILDER = cpp.program

module.TARGET = 'tktemotejoy'

module.SOURCE = [
    'main.cpp',
    'commandlineoptions.cpp',
    'file.cpp',
    'customjson.cpp',
    'generatemappings.cpp',
    'mappings.cpp',
    'mapping.cpp',
    'joystickstate.cpp',
    'pspstate.cpp',
    'tousbhostfs.cpp',
    'joystick.cpp',
    'descriptorcloser.cpp',
    {
        'generatehandler' : [
            'tobuttons.cpp',
            'pressbuttonhandlerforpspstate.cpp',
            'toaxisx.cpp',
            'toaxisy.cpp',
            'operateaxishandlerforpspstate.cpp',
        ],
        'handler' : {
            'forpspstate' : [
                'tobuttons.cpp',
                'toaxisx.cpp',
                'toaxisy.cpp',
                'jseventaxistopspstateaxis.cpp',
            ],
        },
    },
]

module.LIB = [
    'boost_program_options',
]
