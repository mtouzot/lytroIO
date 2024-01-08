# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.1.0] - 2024-01-08
### Added
- Added `lytrostream` module to read, decode and save Lytro file components (`LytroFile`, `LytroDecoder` and `LytroElement`). Currenty, `.jpeg`, `.png` and `.json` files are the only formats supported by the library. A binary file (`.bin`) is created for undecoded contents.
- Added Doxygen documentation
- Added an example to show how to use the `lytroio` library to split a Lytro file, displaying its format and saving it.