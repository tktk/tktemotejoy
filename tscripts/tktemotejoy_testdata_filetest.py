# -*- coding: utf-8 -*-

from taf import *
from taf.tools import copy

module.TYPE = module.test

module.BUILDER = copy.files

module.TARGET = 'filetest'

module.SOURCE = {
    'testdata' : {
        'filetest' : [
            'test.txt',
        ]
    }
}
