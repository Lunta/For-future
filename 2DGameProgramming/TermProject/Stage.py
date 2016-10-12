from Object_Meteor import *
from Object_Player import *
from Utility import *


class Stage:

    def __init__(self):
        self.BOSS_TIMER = 10
        self._m_Timer = 0
        self._m_MeteorList = []

    def build_object(self):
        pass

    def draw(self, purse_y):
        pass

    def update(self, TimeElapsed):
        self._m_Timer += TimeElapsed

    def release(self):
        del self._m_MeteorList



