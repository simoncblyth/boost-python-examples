#!/usr/bin/env python

"""

In [1]: a = prop.Prop("check")
---------------------------------------------------------------------------
RuntimeError                              Traceback (most recent call last)
<ipython-input-1-d2f31965d1d6> in <module>()
----> 1 a = prop.Prop("check")

RuntimeError: This class cannot be instantiated from Python


"""


import prop

class A(prop.Prop):
    pass


a = A()   # RuntimeError: This class cannot be instantiated from Python

 



