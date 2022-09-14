# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

module.TYPE = module.test

module.BUILDER = cpp.gtest

module.TARGET = 'tktemotejoy_handler_forpspstate_calcpspstateaxistest'

module.SOURCE = {
    'handler' : {
        'forpspstate' : [
            'calcpspstateaxistest.cpp',
            'calcpspstateaxis.cpp',
        ],
    },
}
