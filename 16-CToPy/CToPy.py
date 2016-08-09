#!/usr/bin/env python

import CToPy as example

assert(type(example.make_object("spam")) is example.Spam)
assert(type(example.make_object("egg")) is example.Egg)
assert(example.make_object("bogus") is None)
