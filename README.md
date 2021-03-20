# osxinj - MacOS Library Injection Framework/Toolchain
![Unbenannt-1](https://user-images.githubusercontent.com/33968601/111804327-44932080-88d0-11eb-98d6-3b4314a85258.png)
====
A dynamic macOS dylib injector. This method uses a bootstrapping module since `mach_inject` doesn't fully emulate library loading and crashes when loading complex modules.

- `mach_inject` was taken from `rentzsch/mach_inject`. Thanks!
- `testapp` is a sample app to inject into
- `testdylib` is a sample dylib to inject into an app
- `bootstrap` is a dylib that is initially injected to load another dylib (e.g. `testdylib`)

## Installation
You can compile osxinject by running the following set of commands.
```
git clone https://github.com/RPwnage/osxinject/
cd osxinject
cd Source
xcodebuild -project osxinj/osxinj.xcodeproj/ -scheme osxinj build
xcodebuild -project bootstrap/bootstrap.xcodeproj/ -scheme bootstrap build
```

## Examples

### Simple Executable Sample
You'll be given a small executable, with 2 shown hardcoded memory addresses, leading to an integer and a boolean object in memory (`/Samples/SimpleExecutable/testapp/`). Keep in mind that this executable was configured to be built without address randomization, so to do this kind of patching on your own executables/projects might require modifications in the build process.
![image](https://user-images.githubusercontent.com/33968601/111888580-008e4180-89de-11eb-83a6-99ea5a0f48f6.png)
Using the given dylib source (`/Samples/SimpleApplication/testdylib`) you'll be able to hook into the program, create a reference to the integer and boolean objects by creating a pointer to the shown addresses, and then printing out the values.
![image](https://user-images.githubusercontent.com/33968601/111888616-51059f00-89de-11eb-812c-10ca36fd8369.png)
