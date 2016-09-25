from pico2d import *


class TitleScene:
    _m_framework = None
    _m_BKImage = None
    _m_select = None

    def build_object(self, framework):
        self._m_framework = framework
        self._m_BKImage = load_image('logo.jpg')

    def release(self):
        del self._m_BKImage

    def update(self):
        pass

    def draw(self):
        self._m_BKImage.draw(400, 300)

