# TC-LOGO   [![Build Status](https://travis-ci.org/PhilippeGeek/TC-LOGO.png)](https://travis-ci.org/PhilippeGeek/TC-LOGO)
This is a school project done in INSA Lyon. The main goal is to implement a simple LOGO compilator to SVG format.

## How it works
The compiler uses flex and bison to parse and interprets the code. It represents it in a C struct to be able to easily 
navigate in the program. After representation, the compiler writes the SVG on the output.

### What can it do ?
- Simple instructions like FORWARD, LEFT, RIGHT or REPEAT
- Manage the pen by PU (pen up) and PD (pen down)

### It can be better
- Implements macro for circle and square
- Optimize SVG output

## GNU GPL V3.0 (Licencing stuff)
[![GNU GPL v3.0](http://www.gnu.org/graphics/gplv3-127x51.png)](http://www.gnu.org/licenses/gpl.html)

&copy; 2015 Philippe VIENNE

### Notice if you are in INSA Lyon - TC department
My work is under GNU GPL V3. So if you are currently in TC, you can use it but you have to write down that the code comes
from Philippe VIENNE ; teachers will surely not agree.

### Other licences
My work can also be used under the CeCILL Licence Agreement on its last version.