#!/usr/bin/bash

(cd cmakefiles/ && cmake . && make) &&
./ProtoPaint
