import math


def enum(*sequential, **named):
    enums = dict(zip(sequential, range(len(sequential))), **named)
    return type('Enum', (), enums)
# ex) enum("ant","cat","cow")


class POINT(dict):
    def __getattr__(self, name):
        if name.startswith('_'):
            return dict.__getattr__(self, name)
        else:
            return self[name]

    def __setattr__(self, name, value):
        if name.startswith('_'):
            dict.__setattr__(self, name, value)
        else:
            self[name] = value


'''
 ex) ptPos = POINT()
 ptPos.x = 1
 ptPos.y = 1
'''


class Vector2D:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def normalize(self):
        self.x /= self.length()
        self.y /= self.length()

    def length(self):
        return math.sqrt(self.x * self.x + self.y * self.y)


def dot_product_2d(vector_a, vector_b):
    return vector_a.x * vector_b.x + vector_a.y * vector_b.y

