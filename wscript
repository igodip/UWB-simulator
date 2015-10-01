# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

# def options(opt):
#     pass

# def configure(conf):
#     conf.check_nonfatal(header_name='stdint.h', define_name='HAVE_STDINT_H')

def build(bld):
    module = bld.create_ns3_module('uwb-module',['core', 'network', 'mobility', 'spectrum', 'propagation','netanim'])
    module.source = [
        'helper/uwb-module-helper.cc',
		'model/uwb-module-net-device.cc',
		'model/uwb-module-target-app.cc',
		'model/uwb-module-node-app.cc',
		'model/uwb-module-channel.cc',
		'model/uwb-module-phy.cc',
		'model/uwb-module-spectrum-signal-parameters.cc',
		'model/uwb-module-spectrum-model-factory.cc',
		'model/uwb-module-spectrum-value-helper.cc',
		'model/states/uwb-module-abstract-state.cc',
		'model/states/uwb-module-neighbor-discovery-state.cc',
		'model/states/uwb-module-drand-state.cc',
		'model/states/uwb-module-idle-state.cc',
		'model/states/uwb-module-grant-state.cc',
		'model/states/uwb-module-request-state.cc',
		'model/states/uwb-module-election-state.cc',
		'model/uwb-module-le-app.cc',
		'model/uwb-module-drand-app.cc',
		'model/mac/uwb-module-drand-protocol.cc',
		'model/mac/uwb-module-election-protocol.cc',
		'model/mac/uwb-module-ndle-protocol.cc',
		'model/mac/uwb-module-rp-protocol.cc',
		'model/uwb-module-ndle-app.cc',
		'model/states/uwb-module-abs-drand-state.cc',
		'helper/uwb-module-phy-stat-helper.cc',
		'model/mac/uwb-module-mac-trailer.cc',
		'model/mac/uwb-module-mac-header.cc',
		'model/mac/uwb-module-nd-protocol.cc',
		'model/uwb-module-manager.cc'
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
		'model/uwb-module-target-app.h',
		'model/uwb-module-phy.h',
		'model/uwb-module-spectrum-signal-parameters.h',
		'model/uwb-module-spectrum-model-factory.h',
		'model/uwb-module-spectrum-value-helper.h',
		'model/states/uwb-module-abstract-state.h',
		'model/states/uwb-module-request-state.h',
		'model/states/uwb-module-neighbor-discovery-state.h',
		'model/states/uwb-module-idle-state.h',
		'model/states/uwb-module-grant-state.h',
		'model/states/uwb-module-release-state.h',
		'model/states/uwb-module-drand-state.h',
		'model/states/uwb-module-election-state.h',
		'model/states/uwb-module-abs-drand-state.h',
		'model/mac/uwb-module-drand-protocol.h',
		'model/mac/uwb-module-election-protocol.h',
		'model/mac/uwb-module-ndle-protocol.h',
		'model/mac/uwb-module-rp-protocol.h',
		'model/uwb-module-ndle-app.h',
		'model/uwb-module-drand-app.h',
		'model/uwb-module-le-app.h',
		'helper/uwb-module-phy-stat-helper.h',
		'model/mac/uwb-module-mac-trailer.h',
		'model/mac/uwb-module-mac-header.h',
		'model/mac/uwb-module-nd-protocol.h',
		'model/uwb-module-manager.h'
        ]

    if bld.env.ENABLE_EXAMPLES:
        bld.recurse('examples')

    # bld.ns3_python_bindings()

