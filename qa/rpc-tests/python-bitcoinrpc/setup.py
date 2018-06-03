#!/usr/bin/env python

from distutils.core import setup

setup(name='python-bitcoinrpc',
      version='0.1',
      description='Enhanced version of python-jsonrpc for use with Bitcoin',
      long_description=open('README').read(),
      author='jojapoppa (originally Jeff Garzik)',
      author_email='<tipsbugreports@protonmail.com>',
      maintainer='jojapoppa',
      maintainer_email='<tipsbugreports@protonmail.com>',
      url='http://www.github.com/jgarzik/python-bitcoinrpc',
      packages=['bitcoinrpc'],
      classifiers=['License :: OSI Approved :: GNU Library or Lesser General Public License (LGPL)', 'Operating System :: OS Independent'])
