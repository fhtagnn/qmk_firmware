# The puq variant layout for kissboard

A minimalistic ergonomic keyboard layout for fast and efficient typing in English and German with easy access to characters and accents for western languages. It is operational from the keyboard controller without additional software drivers, programmed in QMK and works for Linux, Android¹, Windows² and IOS. Basic OS layout setting is German (DE) or German with Tilde. 

[![PUQ Layout](https://user-images.githubusercontent.com/16945782/50550486-03bc7c00-0c72-11e9-8fca-22db85fef475.png)](http://www.keyboard-layout-editor.com/#/gists/a7e90b22a3bd994868389277b32144ea)

Layout explanation
* Middle label: standard tap output
* Bottom Label: double tap output
* Corner labels: Layers


### Diacritics Key ❖
Press »o,a,u,s + ❖« once  >  German umlaut (diaeresis) u > ü, a > ä, o > ö, s > ß. 
Those characters are handled by old style/deprecated QMK macros which utilize the system language. It keeps the keyboard usable for German language in case unicode input is not available on a system.
All other diacritics are sent as unicodes. The general ranking is: diaeresis > acute > grave > circumflex > tilde > other. It simplifies the usage when acute accent always requires two keypresses and circumflex accent four. There are up to seven diacritics available per letter.

basechar|normal|shifted
----|----|----
o/O  |ö ó ò ô õ œ ø  |Ö Ó Ò Ô Õ Œ Ø
a/A  |ä á à â ã æ å  |Ä Á À Â Ã Æ Å
u/U  |ü ú ù û 		|Ü Ú Ù Û
s/S  |ß 			    |ẞ
e/E  |ë é è ê 		|Ë É È Ê
i/I  |ï í ì î ĳ ÿ ý  |Ï Í Ì Î Ĳ Ÿ Ý
n/N  |ñ ¡ ¿ º ª 	    |Ñ
c/C  |ç © ® ™ 🄯		|Ç

The accents cover most latin western charsets. PUQ is made for German (DE) keylayout setting, so diaeresis ranks first. For the usage with different languages or language sets it could be suitable to replace diacritics or adjust the order of accents within the macros. 
Diacritics key ❖ utilizes a delicate set of layers and macros that call layers to call specific macros. Two new functions were added to QMK (»send_diacritica« und »reset_diac_cycle«) to send different unicode characters by repeated keypresses.

### Compose Key (double tap del key)
Double tap delete key, then input keys of the combination. Compose function must be enabled within the OS. With Windows »WinCompose²« must be installed. Compose is not available with Android. Defined trigger key is right Gui/right Windows key. Useful with rarer characters not covered by diacritics key or direct key input (þ,ð,×,ċ,Ł,š,Ş). The display of characters is dependent on their presence in the font.

### NMB (numbers and navigation)
Tap and hold: plain numerals on right hand, navigation keys on left hand. Double tap toggles lock.
CUTP > hold = Cut, 	tap = Paste     (min. hold ¼ sec)
COPP > hold = Copy, 	tap = Paste
RDUD > hold = Redo, 	tap = Undo

### FNB Layer (function keys and textmarking)
Tap and hold: function keys (F1-F12) on right hand, textmarking on left hand. Double tap toggles lock. 
SCUTP > Shift+Cut, 	tap = Shift+Paste (shell mode)
SCOPP > Shift+Copy, 	tap = Shift+Paste (shell mode)

### NUB Layer (FNB+p)
Same as NMB layer with numberpad numerals. Useful for some programs like Blender. »FNB+p« activates the layer. In case numlock state is off it can be activated/toggled by pressing »q«. While layer NUB is active, press »p« or »FNB+p« to switch off again.

### OS Key (FNB+f)
Switches unicode input modes for different operating systems. Preset on boot is LINUX (IBUS). »FNB+f« toggles: 1. Android¹; 2. Windows with WinCompose²; 3. IOS (untested); 4. back to Linux.

### SC1 Layer (Special characters 1)
Most common special characters.

### SC2 Layer (Special characters 2)
More special characters, dead keys, gimmicks.

### Known limitations
Input of unicodes does not work with capslock active.
The layout is mainly designed for relaxed typing, it might not be perfect for other tasks which require complex key combinations.

### Credits
Layout concept and QMK implementation by dassuan

Calculated for German and English with the optimizer of Andreas Wettstein

Layout and optimizer originate from »Aus der Neo Welt – ADNW«, and the ADNW discussion forum

The ergonomics design is based on the Kissboard concept by Urac

The hardware for wireless Kissboard is designed by fhtagnn, https://github.com/fhtagnn/kissboard


¹ Unicodes up to 0xFFFF can be sent directly by USB keyboard to rooted Android devices. To enable it, editing the relevant *.kcm files on the device is mandatory. The space + alt entry must be complemented with 0xef00, a reserved unicode. It allows Android to recognize and translate raw unicode input. Tested with Samsung SM-P600 tablet with Android 5.5.1 and Sony smartphones. The controller should connect by OTG adapter. The free app “NulInputMethod” can be utilized to represent the USB keyboard. More info

² Use latest version of WinCompose 
