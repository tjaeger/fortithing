Environment/ESPTools
---------------------

It makes sense to install a basic environment for tools like ESPTool, micropython and others. If you only plan to work with Arduino IDE this step can be skipped

# Virtualenv for Python


To not mess up your system Python environment it's recommened to install virtualenv.
Also istall a recent Version of python, 3.7/3.8 [#]_

`Python download from python.org <https://www.python.org/downloads/>`_

`virtualenv download from pypa.io <https://virtualenv.pypa.io/en/latest/installation.html>`_

Footnote 2 [#]_

.. code-block:: bash
   :emphasize-lines: 1, 7

   $ virtualenv -p python3.8 env38
   Running virtualenv with interpreter /Library/Frameworks/Python.framework/Versions/3.8/bin/python3.8
   Also creating executable in /private/tmp/env38/bin/python
   Installing setuptools, pip, wheel...
   done.

   $ source env38/bin/activate
   (env38) $ python -V
   Python 3.8.2


Install ESPTools directly
-------------------------

.. code-block:: bash

   (env38) $ pip install esptools
   [...]
   (env38) $ esptool.py version‚

.. note::

   ESPTools are needed to flash Firmware (unless you use Arduino) to FortiThing. For Example if you need to flash Micropython Firmware.


Install ESPTools in Docker
-------------------------

.. code-block:: bash

$ docker pull espressif/idf:latest
Status: Downloaded newer image for espressif/idf:latest
docker.io/espressif/idf:latest

.. note::

This pulls "latest" IDF. You also can specify a specific Version, see https://hub.docker.com/r/espressif/idf/tags
for available images.

.. [#] Footnote test.
.. [#] Footnote2 test.
