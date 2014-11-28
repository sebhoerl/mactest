#!/usr/bin/env python

from distutils.core import setup, Extension
import pkgconfig

#PKG_CONFIG_LIBRARIES = ['gtkmm-3.0', 'glfw3']
#
#def resolve_pkg_config(what):
#	try: 
#		return subprocess.check_output('pkg-config', '--' + what, *PKG_CONFIG_LIBRARIES)
#	except subprocess.CalledProcessError:
#		raise Exception('pkg-config error!!!!')

socs_ext = Extension(
	'cas_socs_test', 
	[
		'cas_socs_test.cpp'
	],
	libraries = [
		'gtkmm-3.0', 
		'glfw3', 'GL', 'GLU', 
		'boost_system', 'boost_thread', 'boost_python'
	]
)

options = dict(
	name='cas_socs', 
	version='1.0', 
	description='SOCS Project Backend', 
	ext_modules=[socs_ext]
)

setup(**options)
