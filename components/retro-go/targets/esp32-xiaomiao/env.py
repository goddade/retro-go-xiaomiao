# This file is injected late into rg_tool.py, you can run arbitrary python code here
# For example override python variables or set environment variables with os.putenv

# Espressif chip in the device
IDF_TARGET = "esp32"
# .fw file format, if supported by the device
FW_FORMAT = "odroid"
# Default apps to build (4MB flash limit)
DEFAULT_APPS = "launcher retro-core"
