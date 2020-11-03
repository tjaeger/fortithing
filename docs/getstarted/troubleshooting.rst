Troubleshooting
-------------------

Typically you'll connect to FortiThing by USB. It uses a CP2102N Chipset for USB->UART which you need to install the VCP drivers for. The CP2102N is a very well supported Chip and provides Drivers for all major OS and also is quick in updates for new OS Releases.

`Download Silabs CP2102N Driver <https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers>`_

Once driver has been installed and you plug in FortiThing you should see it recognised:

**Linux/OSX**

.. code-block:: bash 

   $ ls /dev/cu*
   /dev/cu.SLAB_USBtoUART

