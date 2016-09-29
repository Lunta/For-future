from pico2d import *
from Scene import *


class PlayScene(Scene):
    name = None
    _m_framework = None
    _m_BKImage = None
    _m_select = None

    def __init__(self, scene_name='Play'):
        Scene.__init__(self, scene_name)

    def build_object(self, framework, BKImagePath=None):
        Scene.build_object(self, framework)
        self._m_BKImage = load_image('Resource\Graphics\Background\Play.png')

    def release(self):
        del self._m_BKImage

    def update(self, TimeElapsed):
        self._handle_events()

    def draw(self):
        self._m_BKImage.draw(self._m_framework.WINDOW_WIDTH / 2, self._m_framework.WINDOW_HEIGHT / 2)

    def _handle_events(self):
        events = get_events()
        for event in events:
            if event.type == SDL_QUIT:
                self._m_framework.quit()
            elif event.type == SDL_KEYDOWN and event.key == SDLK_ESCAPE:
                self._m_framework.change_state('Gameover')
