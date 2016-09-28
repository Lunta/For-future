from pico2d import *
from Scene import *


class GameoverScene(Scene):
    DRAW_TIME = 5
    _m_Timer = 0.0

    def __init__(self, scene_name='Gameover'):
        Scene.__init__(self, scene_name)

    def build_object(self, framework, BKImagePath=None):
        Scene.build_object(self, framework, 'Resource\Graphics\Background\Gameover.png')

    def update(self, TimeElapsed):
        self._m_Timer += TimeElapsed
        if self._m_Timer > self.DRAW_TIME:
            self._m_Timer = 0.0
            Scene.change_scene(self, 'Title')  # TODO: Ranking 구현 후 변경


