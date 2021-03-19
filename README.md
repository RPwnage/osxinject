# osxinj - MacOS Library Injection Framework/Toolchain
![Unbenannt-1](https://user-images.githubusercontent.com/33968601/111804327-44932080-88d0-11eb-98d6-3b4314a85258.png)
====
A dynamic macOS dylib injector. This method uses a bootstrapping module since `mach_inject` doesn't fully emulate library loading and crashes when loading complex modules.

- `mach_inject` was taken from `rentzsch/mach_inject`. Thanks!
- `testapp` is a sample app to inject into
- `testdylib` is a sample dylib to inject into an app
- `bootstrap` is a dylib that is initially injected to load another dylib (e.g. `testdylib`)
