from pico2d import *
from Scene import *


class LogoScene(Scene):
    DRAW_TIME = 3
    _m_Timer = 0.0

    def __init__(self, scene_name='Logo'):
        Scene.__init__(self, scene_name)

    def build_object(self, framework, BKImagePath=None):
        Scene.build_object(framework, 'Resource\Graphics\Background\Logo.png')

    def update(self, TimeElapsed):
        self._m_Timer += TimeElapsed
        if self._m_Timer > self.DRAW_TIME:
            self._m_Timer = 0.0
            Scene.change_scene(self, 'Title')



