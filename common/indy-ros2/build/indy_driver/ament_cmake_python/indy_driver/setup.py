from setuptools import find_packages
from setuptools import setup

setup(
    name='indy_driver',
    version='1.0.0',
    packages=find_packages(
        include=('indy_driver', 'indy_driver.*')),
)
