import os
import sys

# NOTE: it still need to copy DLLs from vcpkg into the pyd folder

# Add the folder where rubberband.dll is located
os.environ['PATH'] = os.pathsep.join([r'C:\\Users\\sharow\\projects\\vcpkg\\installed\\x64-windows\\bin\\', os.environ['PATH']])

# Add the folder where rubberband_wrapper.pyd is located to sys.path
sys.path.append(r'C:\\Users\\sharow\\projects\\tts\\pitch-shift\\rubberband\\build-x64-rel\\')

import ctypes
ctypes.CDLL(r'C:\\Users\\sharow\\projects\\tts\\pitch-shift\\rubberband\\build-x64-rel\\lv2-rubberband.dll')

from rubberband_wrapper import RubberBandStretcher

# Example usage
stretcher = RubberBandStretcher(sample_rate=44100, channels=2)
#stretcher.reset()
print(stretcher.get_library_version())
