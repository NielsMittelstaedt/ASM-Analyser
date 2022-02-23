from setuptools import setup, find_packages

with open('README.md') as f:
    long_description = f.read()

setup(
    name='asm-analyser',
    version='1.0',
    description='Tool for dynamic program analysis.',
    license='MIT',
    long_description=long_description,
    author='Niels Mittelstädt',
    author_email='niels.mittelstaedt@rwth-aachen.de',
    url='https://github.com/NielsMittelstaedt/ASM-Analyser',
    packages=find_packages(),
    scripts=['scripts/asm-analyse'],
    include_package_data=True,
    python_requires='>=3.6',
    classifiers=[
        'License :: OSI Approved :: MIT License',
        'Natural Language :: English',
        'Programming Language :: Python :: 3.9'
    ]
)
