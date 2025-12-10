from setuptools import Extension, setup

setup(
    name="matrix_",
    version="0.0.1",
    description="Matrix power calculation module",
    author="dbg",
    ext_modules=[
        Extension(
            name="matrix_",
            sources=["matrix__.c"],
        ),
    ]
)