& $PSScriptRoot\buildBMBF.ps1
& adb push libs/arm64-v8a/libnoodleextensions.so /sdcard/Android/data/com.beatgames.beatsaber/files/mods/libnoodleextensions.so
& adb shell am force-stop com.beatgames.beatsaber
& adb shell am start com.beatgames.beatsaber/com.unity3d.player.UnityPlayerActivity
& adb logcat -c
& adb logcat > log.log