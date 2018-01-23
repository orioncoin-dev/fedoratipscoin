from distutils.core import setup
setup(name='btcspendfrom',
      version='1.0',
      description='Command-line utility for bitcoin "coin control"',
      author='jojapoppa (originally was Gavin Andresen)',
      author_email='tipsbugreports@protonmail.com',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
