from pico2d import *


class LogoScene:
    _m_framework = None
    _m_BKImage = None
    _m_timer = None

    def build_object(self, framework):
        self._m_framework = framework
        self._m_BKImage = load_image('logo.jpg')

    def release(self):
        del self._m_BKImage

    def update(self):
        if self._m_timer > 1.0:
            self._m_timer = 0

        self._m_timer += 0.01

    def draw(self):
        self._m_BKImage.draw(400, 300)



