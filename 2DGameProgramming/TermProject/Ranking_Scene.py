from pico2d import *


class RankingScene:
    _m_framework = None
    _m_BKImage = None

    def build_object(self, framework):
        self._m_framework = framework
        self._m_BKImage = load_image('logo.jpg')

    def release(self):
        del self._m_BKImage

    def update(self):
        pass

    def draw(self):
        self._m_BKImage.draw(400, 300)

