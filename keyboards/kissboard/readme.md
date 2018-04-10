Mitosis
=======

A wireless split compact keyboard.

Keyboard Maintainer: [@fhtagnn](https://github.com/fhtagnn)
Hardware Supported: kissboard PCB
Hardware Availability: tbd

Make example for this keyboard (after setting up your build environment):

    make kissboard:default

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.

## Mitosis Notes

These configuration files were based off the Atreus keyboard. It assumes a Pro Micro is being used, however retains the 'make upload' feature from the Atreus branch. This keyboard uses a completely different 'matrix scan' system to other keyboards, it relies on an external nRF51822 microcontroller maintaining a matrix of keystates received from the keyboard halves. The matrix.c file contains the code to poll the external microcontroller for the key matrix. As long as this file is not changed, all other QMK features are supported.

Build log of the keyboard can be found (tbd)

Hardware design files can be found [here](https://github.com/fhtagnn/kissboard)

Firmware for the nordic MCUs can be found [here](https://github.com/fhtagnn/mitosis)
