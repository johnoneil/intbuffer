from setuptools import setup

def readme():
    with open('README.md') as f:
        return f.read()

setup(name='intbuffer',
    version='0.1',
    description='Generate integer buffer read/write code via text markup.',
    long_description = readme(),
	classifiers=[
        'Development Status :: 3 - Alpha',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 2.7',
        'Topic :: Software Development :: Code Generators',
      ],
    keywords = 'mako c++ code generation integer buffer',
    url='https://github.com/johnoneil/IntBuffer',
    author='John O\'Neil',
    author_email='oneil.john@gmail.com',
    license='MIT',
    packages=['intbuffer'],
    install_requires=[
        'mako',
	'argparse',
      ],
	package_data = {
		'intbuffer': ['*.cpp', '*.hpp','*.txt'],
	},
    entry_points = {
		'console_scripts': ['intbuffer-generate=intbuffer.intbuffer:main'],
    },
      zip_safe=True)
