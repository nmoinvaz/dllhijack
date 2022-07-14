Adapted from:

* https://gracefulsecurity.com/privesc-dll-hijacking/
* https://posts.specterops.io/automating-dll-hijack-discovery-81c4295904b0
* https://github.com/slyd0g/DLLHijackTest

## Build Instructions

```
cmake -S . -B build -A Win32
cmake --build build --config Release
```