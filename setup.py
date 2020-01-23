from distutils.core import setup, Extension
setup(name = 'mymodule', version = '1.0.0', ext_modules = [Extension('mymodule', ['mymodule.c'], include_dirs=['/usr/local/lib/python2.7/dist-packages/numpy/core/include'])])
