from pico2d import *
from Scene import *


class LogoScene(Scene):
    def __init__(self, scene_name='Logo'):
        Scene.__init__(self, scene_name)
        self.DRAW_TIME = 3
        self._m_Timer = 0.0

    def get_scene(self):
        return self.get_name()

    def build_object(self, framework, sound_manager, BKImagePath=None):
        Scene.build_object(self, framework, sound_manager, 'Resource\Graphics\Background\Logo.png')

    def update(self, TimeElapsed):
        self._m_Timer += TimeElapsed
        if self._m_Timer > self.DRAW_TIME:
            self._m_Timer = 0.0
            self._m_framework.change_scene('Title')


