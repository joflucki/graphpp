TEMPLATE = subdirs

SUBDIRS += \
    App \
    Lib \
    Tests

App.depends = Lib
Tests.depends = Lib
