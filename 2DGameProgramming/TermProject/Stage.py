from Object_Meteor import *


class Stage:
    BOSS_TIMER = 10
    _m_Timer = 0
    _m_MeteorList = []

    def __init__(self):
        pass

    def build_object(self):
        pass

    def draw(self):
        pass

    def update(self, TimeElapsed):
        self._m_Timer += TimeElapsed

    def release(self):
        del self._m_MeteorList



