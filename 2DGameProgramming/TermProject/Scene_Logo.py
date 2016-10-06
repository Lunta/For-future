from pico2d import *
from Scene import *


class LogoScene(Scene):
    DRAW_TIME = 3
    _m_Timer = 0.0

    def __init__(self, scene_name='Logo'):
        Scene.__init__(self, scene_name)

    def get_scene(self):
        return self.get_name()

    def build_object(self, framework, BKImagePath=None):
        Scene.build_object(self, framework, 'Resource\Graphics\Background\Logo.png')

    def update(self, TimeElapsed):
        self._m_Timer += TimeElapsed
        if self._m_Timer > self.DRAW_TIME:
            self._m_Timer = 0.0
            self._m_framework.change_scene('Title')


