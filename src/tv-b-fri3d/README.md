# TV B Fri3d

Aangezien de [TV B Gone](http://cornfieldelectronics.com/tvbgone/tvbg.home.php) één van de spreekwoordelijks ouders is van de Fri3d Badge, kan een implementatie van deze software niet ontbreken.

Het gebruiken van een Arduino om een "TV B Gone" te maken, is ook het onderwerp van een workshop van Mitch Altman zelf (zie: [http://cornfieldelectronics.com/cfe/projects/tvbg_arduino/tvbg_arduino_workshop.php](http://cornfieldelectronics.com/cfe/projects/tvbg_arduino/tvbg_arduino_workshop.php) voor meer info).

Deze versie is gebaseerd op eerder werk door Ken Shirriff. Mitch Altman heeft de code verder aangepast voor meerdere Arduino platformen, o.a. voor de "Adafruit's Flora", welke ook werkt op basis van de ATMega32u4.

Op een recente versie van de Arduino IDE (1.6.9) geeft deze implementatie nog problemen, maar die gaan we snel oplossen ;-)

```
Arduino: 1.6.9 (Mac OS X), Board: "LilyPad Arduino USB"

In file included from sketch/main.h:1:0,
                 from sketch/worldcodes.cpp:12:
worldcodes.cpp:8506: error: variable 'NApowerCodes' must be const in order to be put into read-only section by means of '__attribute__((progmem))'
 const struct IrCode *NApowerCodes[] PROGMEM = {

                                     ^
worldcodes.cpp:8646: error: variable 'EUpowerCodes' must be const in order to be put into read-only section by means of '__attribute__((progmem))'
 const struct IrCode *EUpowerCodes[] PROGMEM = {

                                     ^
exit status 1
variable 'NApowerCodes' must be const in order to be put into read-only section by means of '__attribute__((progmem))'

This report would have more information with
"Show verbose output during compilation"
option enabled in File -> Preferences.
```

Als deze code compileert, moeten we nog wel enkele aanpassingen doen, omdat we andere pinnen gebruiken om de IR leds aan te sturen.

Mitch Altman komt met zijn "Arduino for newbies" naar Fri3d Camp, en wie weet werken jullie wel met jullie eigen badge tijdens deze workshop ;-) We sturen onze aanpassingen in ieder geval naar hem door ;-)
