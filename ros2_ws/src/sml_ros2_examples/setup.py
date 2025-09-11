from setuptools import find_packages, setup

package_name = 'ros2_examples'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='root',
    maintainer_email='dohyeon@snu.ac.kr',
    description='sml lecture example',
    license='Seoul National University IDIM Lab.',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'topic_publish = ros2_examples.topic_publish:main',
            'topic_subscribe = ros2_examples.topic_subscribe:main',
            'service_server = ros2_examples.service_server:main',
            'service_client = ros2_examples.service_client:main',
        ],
    },
)
