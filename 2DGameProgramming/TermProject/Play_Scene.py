from pico2d import *


class PlayScene:
    name = 'Play'
    _m_framework = None
    _m_BKImage = None

    def build_object(self, framework):
        self._m_framework = framework
        self._m_BKImage = load_image('Resource\Graphics\Background\Logo.jpg')

    def release(self):
        del self._m_BKImage

    def update(self, TimeElapsed):
        self._handle_events()

    def draw(self):
        self._m_BKImage.draw(400, 300)

    def _handle_events(self):
        events = get_events()
        for event in events:
            if event.type == SDL_QUIT:
                self._m_framework.quit()
            elif event.type == SDL_KEYDOWN and event.key == SDLK_ESCAPE:
                self._m_framework.change_state()
