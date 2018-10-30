#!/bin/sh

###-----------------------------------------------------------------------------
###
### Post-build step to produce OTA DFU GBL files and a consolidated Flash image file
###
### Copyright (c) Uncannier Software 2018
###
###-----------------------------------------------------------------------------

# Extract S-record files for the apploader and application individually
arm-none-eabi-objcopy -O srec -j .text_apploader* "${1}/${2}.axf" "${1}/apploader.srec" >/dev/null
arm-none-eabi-objcopy -O srec -j .text_application* "${1}/${2}.axf" "${1}/application.srec" >/dev/null

# Create a combined image HEX file - bootloader (first and second stage), apploader and application - this is flashable
commander convert ../utr-bootloader/Release/utr-bootloader-combined.s37 ./$1/apploader.srec ./$1/application.srec --outfile ./$1/utr-image.hex

# Create (unsigned & unencrypted) GBL files for OTA updates
commander gbl create "${1}/utr-apploader.gbl" --app "${1}/apploader.srec" >/dev/null
commander gbl create "${1}/utr-application.gbl" --app "${1}/application.srec" >/dev/null

# Clean up the intermediate files
rm ${1}/*.srec
