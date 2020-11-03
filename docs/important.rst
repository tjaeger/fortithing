Important notes
================

FortiThing has been design with care and is tolerant to many circumstances.
However basic measures should be applied and basic rules being followed to avoid damage to both FortiThing or connected Devices.

.. warning::
   It's unlikely you destroy the Hardware "easy" but the external IO nor other ports (eg USB) are ESD protected. It's recommended to apply basic ESD measure to avoid damage. For Example ground yourself (touch Laptop) before touching the board.

.. warning::
   It's unlikely you destroy the Hardware "easy" but the external IO nor other ports (eg USB) are ESD protected. It's recommended to apply basic ESD measure to avoid damage. For Example ground yourself (touch Laptop) before touching the board.

.. warning::
   3.3V Power on IO is directly connected to Main Power net off LDO. There is no Fuse. If you create a short-circuit it may damage the LDO or other components.

.. important::
   The main power (5V from USB) is protected with a PTC Fuse. A short on the board should not damage a connected Laptop.

.. important::
  You should not draw more than 30mA per GPIO from the external connectors as they’re directly connected to MCU. Drawing more may damage the MCU. Treat them as Digital-IO or low-power PWM.


