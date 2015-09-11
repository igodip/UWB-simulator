# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

# def options(opt):
#     pass

# def configure(conf):
#     conf.check_nonfatal(header_name='stdint.h', define_name='HAVE_STDINT_H')

def build(bld):
    module = bld.create_ns3_module('uwb-module', ['core'])
    module.source = [
        'helper/uwb-module-helper.cc',
		'model/uwb-module-net-device.cc',
		'model/uwb-module-target-app.cc',
		'model/uwb-module-node-app.cc'
        ]

    module_test = bld.create_ns3_module_test_library('uwb-module')
    module_test.source = [
        'test/uwb-module-test-suite.cc',
        ]

    headers = bld(features='ns3header')
    headers.module = 'uwb-module'
    headers.source = [
        'helper/uwb-module-helper.h',
		'model/uwb-module-net-device.h',
		'model/uwb-module-channel.h',
		'model/uwb-module-node-app.h',
		'model/uwb-module-target-app.h'
        ]

    if bld.env.ENABLE_EXAMPLES:
        bld.recurse('examples')

    # bld.ns3_python_bindings()

