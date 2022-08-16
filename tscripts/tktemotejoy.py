# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.DEPENDS = [
    'tktemotejoy_joystickstate_forpressedbuttonstest',
    'tktemotejoy_joystickstate_foraxestest',
    'tktemotejoy_mapping_pressbuttonforpspstatetest',
    'tktemotejoy_mapping_operateaxisforpspstatetest',
    'tktemotejoy_mapping_pressbuttonforchangemappingtest',
    'tktemotejoy_mapping_operateaxisforchangemappingtest',
    'tktemotejoy_pspstate_difftest',
    'tktemotejoy_handler_forchangemapping_shiftmappingtest',
    'tktemotejoy_handler_forchangemapping_togglemappingtest',
]

module.BUILDER = cpp.program

module.TARGET = 'tktemotejoy'

module.SOURCE = [
    'main.cpp',
    'joystickstate.cpp',
    'mapping.cpp',
    'pspstate.cpp',
    {
        'handler' : {
            'forchangemapping' : [
                'shiftmapping.cpp',
                'togglemapping.cpp',
            ],
        },
    },
]
