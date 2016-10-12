from pico2d import *
import math
import random


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


class Rect:
    def __init__(self, left=0, bottom=0, right=0, top=0):
        self.left = left
        self.bottom = bottom
        self.right = right
        self.top = top

    def set_parameter(self, left=0, bottom=0, right=0, top=0):
        self.left = left
        self.bottom = bottom
        self.right = right
        self.top = top

    def draw(self, purse_y=0):
        draw_rectangle(self.left, self.bottom + purse_y, self.right, self.top + purse_y)


def check_rect_crash(rect1, rect2):
    return rect1.left < rect2.right and rect1.top > rect2.bottom and rect1.right > rect2.left and rect1.bottom < rect2.top


class Vector2D:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def normalize(self):
        length = self.length()
        self.x /= length
        self.y /= length

    def length(self):
        return math.sqrt(self.x * self.x + self.y * self.y)


def dot_product_2d(vector_a, vector_b):
    return vector_a.x * vector_b.x + vector_a.y * vector_b.y

