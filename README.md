# simple-interaction
This repository contains some simple modules for human-robot interaction using port arbitration.

Requirements
------------
* [*Yarp LUA binding.*](http://www.yarp.it/yarp_swig.html#yarp_swig_lua)

* [*Port monitor carrier.*](http://www.yarp.it/portmonitor.html)

* [*The icub-contrib-common meta-package.*](https://github.com/robotology/icub-contrib-common)


Installation
------------
The installation is easy, straightforward and uses the CMake build system.
```
    $ git clone https://github.com/robotology-playground/simple-interaction.git
    $ cd simple-interaction
    $ mkdir build; cd build
    $ cmake ../; make
    $ make install
```

Modules
-------
* _wonderAround_ (moves robot head to randomly look around) 
* _simpleFaceDetector_ (a simple human face detector using open-cv)
* _tocuhDetector_ (detects and report the 3D contact point using the iCub skin. *under development!* )


Applications
------------
* _Search and track human face_ (see `simple-interaction/app/scripts/SimpleInteraction.xml.template`)


Authors
-------
* Ali Paikan ([*personal page*](http://alipaikan.com))

