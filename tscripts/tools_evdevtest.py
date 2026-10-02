from . import SOURCE_ROOT_DIR
from . import TOOLS_DIR
from taf import *
from taf.tools import cpp

import os.path

module.BUILDER = cpp.program

module.TARGET = os.path.join(
    TOOLS_DIR,
    'evdevtest',
)

module.SOURCE = {
    TOOLS_DIR : [
        'evdevtest.cpp',
    ],
    SOURCE_ROOT_DIR : [
        'evdev.cpp',
        'descriptorcloser.cpp',
    ],
}
