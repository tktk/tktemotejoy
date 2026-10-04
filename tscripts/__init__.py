import os.path

_SOURCE_DIR = 'src'

HEADER_DIR = 'inc'
TEST_DIR = 'test'
TOOLS_DIR = 'tools'

PACKAGE_NAME = 'tktemotejoy'

SOURCE_ROOT_DIR = os.path.join(
    _SOURCE_DIR,
    PACKAGE_NAME,
)

TEST_SOURCE_ROOT_DIR = os.path.join(
    TEST_DIR,
    _SOURCE_DIR,
    PACKAGE_NAME,
)

TEST_HEADER_DIR = os.path.join(
    TEST_DIR,
    HEADER_DIR,
)
