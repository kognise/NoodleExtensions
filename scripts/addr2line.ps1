$NDKPath = Get-Content ndkpath.txt

$script = "$NDKPath\toolchains\llvm\prebuilt\windows-x86_64\bin\aarch64-linux-android-addr2line.exe"

& $script -e .\obj\local\arm64-v8a\libnoodleextensions.so $args[0]