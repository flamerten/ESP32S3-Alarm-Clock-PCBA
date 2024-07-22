# JLCPCB Files
Files in this folder are sent to JLCPCB for manufacturing. This file also includes the BOM and their respective LCSC parts. However, I sourced for the through hole components myself and soldered them.

- [Battery Holder](https://www.aliexpress.com/item/1005006254465094.html?spm=a2g0o)
- [OLED Breakout](https://www.aliexpress.com/item/1005005973981064.html?spm=a2g0o)
- [SMD Pin Header 02x12](https://www.aliexpress.com/item/33056177154.html?spm=a2g0o)
- [PS1240 Passive Buzzer](https://www.aliexpress.com/item/1005005731967986.html?spm=a2g0o)

## Ordering
I designed the PCB with KiCAD, and installed the [kicad-jlcpcb-tools](https://github.com/bouni/kicad-jlcpcb-tools) plugin which automatically generates the neccessary files. The [Gerber Files](./production_files/GERBER-AlarmClockProjV1.zip) are used first, followed by the [BOM File](./production_files/BOM-AlarmClockProjV1.csv) and [CPL File](./production_files/CPL-AlarmClockProjV1.csv). 

To reduce cost, I opted for single sided assembly, with no through hole components. The assembly was **standard** because of the ESP32 module and the WS2812B. 

I was recommended by JLCPCB to bake the WS2812-2020 component as it was moisture sensitive, which increased the assembly by $7.54.

Note that component rotation is mandatory. I had to check all the components and rotate them myself, not too sure why. Resistors and Capacitors were okay, but the MOSFETS, ICs and LEDs had to be rotated.