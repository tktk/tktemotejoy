# -*- coding: utf-8 -*-

from taf import *
from taf.tools import cpp

import os.path

module.BUILDER = cpp.program

module.TARGET = os.path.join(
    'tools',
    'evdevtest',
)

module.SOURCE = [
    {
        'tools' : [
            'evdevtest.cpp',
        ],
    },
    'evdev.cpp',
    'descriptorcloser.cpp',
]
