# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.DEPENDS = [
    'tktemotejoy_commandlineoptionstest',
    'tktemotejoy_filetest',
    'tktemotejoy_mappingnamestest',
    'tktemotejoy_customjson_parsetest',
    'tktemotejoy_json_getjsonfromobjecttest',
    'tktemotejoy_json_getjsonarraytest',
    'tktemotejoy_json_getjsonobjecttest',
    'tktemotejoy_json_getjsonunsignedtest',
    'tktemotejoy_json_getjsonintegertest',
    'tktemotejoy_json_getjsonstringtest',
    'tktemotejoy_jsonerrortest',
    'tktemotejoy_evdevstate_forpressedbuttonstest',
    'tktemotejoy_evdevstate_foraxestest',
    'tktemotejoy_pspstate_difftest',
    'tktemotejoy_handler_common_calcrangedirectiontest',
    'tktemotejoy_handler_common_calcmintocentertest',
    'tktemotejoy_handler_common_withrangeimpltest',
    'tktemotejoy_handler_common_withrangeonewayimpltest',
    'tktemotejoy_handler_forpspstate_tobuttonstest',
    'tktemotejoy_handler_forpspstate_tofixedaxisxtest',
    'tktemotejoy_handler_forpspstate_tofixedaxisytest',
    'tktemotejoy_handler_forpspstate_dummytest',
    'tktemotejoy_handler_forpspstate_withrangetest',
    'tktemotejoy_handler_forpspstate_withrangeonewaytest',
    'tktemotejoy_handler_forpspstate_toaxisxtest',
    'tktemotejoy_handler_forpspstate_toaxisytest',
    'tktemotejoy_handler_forpspstate_tobuttonhandlerstest',
    'tktemotejoy_handler_forpspstate_calcpspstateaxistest',
    'tktemotejoy_handler_forpspstate_tobuttonhandlertest',
    'tktemotejoy_handler_forchangemapping_shiftmappingtest',
    'tktemotejoy_handler_forchangemapping_togglemappingtest',
    'tktemotejoy_handler_forchangemapping_dummytest',
    'tktemotejoy_handler_forchangemapping_withrangetest',
    'tktemotejoy_handler_forchangemapping_withrangeonewaytest',
    'tktemotejoy_handler_forchangemapping_tobuttonhandlerstest',
    'tktemotejoy_handler_forchangemapping_tobuttonhandlertest',
    'tktemotejoy_mapping_pressbuttonforpspstatetest',
    'tktemotejoy_mapping_operateaxisforpspstatetest',
    'tktemotejoy_mapping_pressbuttonforchangemappingtest',
    'tktemotejoy_mapping_operateaxisforchangemappingtest',
    'tktemotejoy_mappings_evdevstatetopspstatetest',
    'tktemotejoy_generatehandler_generatehandleruniquetest',
    'tktemotejoy_generatehandler_tobuttonstest',
    'tktemotejoy_generatehandler_tofixedaxistest',
    'tktemotejoy_generatehandler_tofixedaxisxtest',
    'tktemotejoy_generatehandler_tofixedaxisytest',
    'tktemotejoy_generatehandler_pressbuttonhandlerforpspstatetest',
    'tktemotejoy_generatehandler_withrangetest',
    'tktemotejoy_generatehandler_toaxistest',
    'tktemotejoy_generatehandler_toaxisxtest',
    'tktemotejoy_generatehandler_toaxisytest',
    'tktemotejoy_generatehandler_operateaxishandlerforpspstatetest',
    'tktemotejoy_generatehandler_changemappingtest',
    'tktemotejoy_generatehandler_shiftmappingtest',
    'tktemotejoy_generatehandler_togglemappingtest',
    'tktemotejoy_generatehandler_pressbuttonhandlerforchangemappingtest',
    'tktemotejoy_generatehandler_tobuttonhandlerstest',
    'tktemotejoy_generatehandler_tobuttonhandlersforpspstatetest',
    'tktemotejoy_generatehandler_tobuttonhandlersforchangemappingtest',
    'tktemotejoy_generatehandler_tobuttonhandlertest',
    'tktemotejoy_generatehandler_tobuttonhandlerforpspstatetest',
    'tktemotejoy_generatehandler_tobuttonhandlerforchangemappingtest',
    'tktemotejoy_generatehandler_operateaxishandlerforchangemappingtest',
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
    'mappingnames.cpp',
    'evdevstate.cpp',
    'pspstate.cpp',
    'tousbhostfs.cpp',
    'evdev.cpp',
    'descriptorcloser.cpp',
    'typeerror.cpp',
    'mappingnameerror.cpp',
    {
        'generatehandler' : [
            'tobuttons.cpp',
            'pressbuttonhandlerforpspstate.cpp',
            'toaxisx.cpp',
            'toaxisy.cpp',
            'tofixedaxisx.cpp',
            'tofixedaxisy.cpp',
            'tobuttonhandlersforpspstate.cpp',
            'tobuttonhandlerforpspstate.cpp',
            'operateaxishandlerforpspstate.cpp',
            'pressbuttonhandlerforchangemapping.cpp',
            'shiftmapping.cpp',
            'togglemapping.cpp',
            'tobuttonhandlersforchangemapping.cpp',
            'tobuttonhandlerforchangemapping.cpp',
            'operateaxishandlerforchangemapping.cpp',
        ],
        'handler' : {
            'forpspstate' : [
                'tobuttons.cpp',
                'toaxisx.cpp',
                'toaxisy.cpp',
                'tofixedaxisx.cpp',
                'tofixedaxisy.cpp',
                'tobuttonhandlers.cpp',
                'tobuttonhandler.cpp',
                'dummy.cpp',
                'calcpspstateaxis.cpp',
            ],
            'forchangemapping' : [
                'shiftmapping.cpp',
                'togglemapping.cpp',
                'tobuttonhandlers.cpp',
                'tobuttonhandler.cpp',
                'dummy.cpp',
            ],
            'common' : [
                'calcrangedirection.cpp',
                'calcmintocenter.cpp',
            ],
        },
    },
]
