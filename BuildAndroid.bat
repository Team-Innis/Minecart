@echo off

C:
chdir C:/Users/tti12sjuhos/Programs/cygwin/bin

::Cygwin and NDK path must be defined here.
bash --login -i -c 'cd /cygdrive/c/Users/tti12sjuhos/Desktop/Minecart/UtHEngine/android; ../../../android-ndk-r9/ndk-build; bash'