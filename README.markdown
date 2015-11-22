rlutil
======

[![Build Status](https://travis-ci.org/tapio/rlutil.svg)](https://travis-ci.org/tapio/rlutil)

_RLUTIL_ is simple utility collection to aid the creation of cross-platform
console-mode roguelike games with C++ and C. At least that was the original idea.
In reality, it mostly just contains functions to position and colorize text as well as
reading keyboard input.

## QUICK START ##
Just `#include "rlutil.h"` in your source code. It automagically detects if you
are using C++ or C and adjusts the code accordingly (e.g. `std::string` vs. `char*`).

## DOCUMENTATION ##
See the API reference in [docs/HTML/](docs/HTML/index.html "API Reference")
or the source code comments for documentation.

## DOWNLOAD ##
You can download this project in either
[zip](http://github.com/tapio/rlutil/zipball/master "zip") or
[tar](http://github.com/tapio/rlutil/tarball/master "tar") formats.

You can also clone the project with [Git](http://git-scm.com "Git") by running:

    $ git clone git://github.com/tapio/rlutil

## LICENSE ##
See [docs/License.txt][] or [API Documentation][].

[docs/License.txt]: docs/License.txt "Raw license text"
[API Documentation]: docs/HTML/files/docs/License-txt.html "HTML license text"
