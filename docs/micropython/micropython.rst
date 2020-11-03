MicroPYTHON
===========

.. note:: 

   This assumes you have a virtualenv/Python and ESPTools installed and you are within a virtualenv environment. 

Tools Installation
------------------

Please install some tools to interact with Micropython once installed.
If using ``virtualenv`` make sure you perform this from within.

.. code-block:: bash 

   (ENV38) $ pip3 install rshell 

More Infos on rshell, visit  
`rshell on github <https://github.com/dhylands/rshell>`_


Verify Installation

.. code-block:: bash 

   (ENV38) $ rshell --version


Flashing Micropython 
--------------------

Download Micropython from https://micropython.org/download 
for the ESP32 Platform (GENERIC).
`Github Link for Source and Docs  <https://github.com/micropython/micropython>`_

At the time of writing this is `Micropython 1.12 <https://micropython.org/resources/firmware/esp32-idf3-20191220-v1.12.bin>`_


Flash the downloaded Micropython Firmware to FortiThing:

.. code-block:: bash 

   (ENV38) $ esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 460800 --erase-all write_flash -z 0x1000 esp32-idf3-20191220-v1.12.bin


