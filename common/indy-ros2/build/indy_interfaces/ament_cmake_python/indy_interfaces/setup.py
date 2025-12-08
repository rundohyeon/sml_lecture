from setuptools import find_packages
from setuptools import setup

setup(
    name='indy_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('indy_interfaces', 'indy_interfaces.*')),
)
