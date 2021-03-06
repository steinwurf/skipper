#! /usr/bin/env python
# encoding: utf-8

APPNAME = 'skipper'
VERSION = '3.0.0'


def build(bld):

    bld.env.append_unique(
        'DEFINES_STEINWURF_VERSION',
        'STEINWURF_SKIPPER_VERSION="{}"'.format(
            VERSION))

    bld.recurse('src/skipper')

    if bld.is_toplevel():

        # Only build tests when executed from the top-level wscript,
        # i.e. not when included as a dependency
        bld.recurse('test')

        bld.recurse('examples/simple')
