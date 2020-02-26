# The puq variant layout for kissboard

A minimalistic ergonomic keyboard layout for fast and efficient typing in English and German with easy access to characters and accents for western languages. It is operational from the keyboard controller without additional software drivers, programmed in QMK and works for Linux, Android¹, Windows² and IOS. Basic OS layout setting is German or German with Tilde. 
The layout is mainly designed for relaxed typing, it might not be perfect for other tasks which require complex key combinations.

[![PUQ Layout](https://user-images.githubusercontent.com/16945782/50550486-03bc7c00-0c72-11e9-8fca-22db85fef475.png)](http://www.keyboard-layout-editor.com/#/gists/a7e90b22a3bd994868389277b32144ea)

Layout explanation
* Middle label: standard tap output
* Bottom Label: double tap output
* Corner labels: Layers


### Diacritics Key ❖
Press »o,a,u,s + ❖« once  >  German umlaut (diaeresis) u > ü, a > ä, o > ö, s > ß. 
Those characters are handled by old style/deprecated QMK macros which utilize the system language. It keeps the keyboard usable for German language in case unicode input is not available on a system.
All other diacritics are sent as unicodes. The general ranking is: diaeresis > acute > grave > circumflex > tilde > other. It simplifies the usage when acute accent always requires two keypresses and circumflex accent four. There are up to seven diacritics available per letter.
