# photo_renamer
simple tool to rename all files from camera - names will contain data/time from EXIF

## 

It renames all .jpg files in the current directory in the following way:

YYYY_MM_DD__hh_mm_ss-<original name>.jpg

where YYYY, MM, DD, hh, mm, ss - year, month, da, hour, minute, seconds from DateTimeOriginal field of EXIF data.

The only purpuse of this tool - make possible to store all my photos from camera in one directory and sort 
them by time of shooting.
(camera uses DSC_XXXX.jpg names and XXXX number starts from 0001 every time after memory card clean up)

Tool uses 'easyexif' library https://github.com/mayanklahiri/easyexif.git

## Build

Install build tools: gcc, g++, cmake.

```bash
cmake .
make
```

easyexif should be cloned automatically by CMake
If there is problem like "easy exif files are not found" try to run cmake/make again.

## Run

./photo_rename

Do not run it twice! Names will be longer and longer after every run :)


## Contact
timofey.turenko@fruct.org

but do not expect quick reply or comments: this tool is only personal use and 
I do not want to improve/fix it.
