from pico2d import *


class Scene:
    _name = None
    _m_framework = None
    _m_BKImage = None

    def __init__(self, scene_name='Scene'):
        self._name = scene_name

    def get_name(self):
        return self._name

    def build_object(self, framework, BKImagePath=False):
        self._m_framework = framework
        if BKImagePath:
            self._m_BKImage = load_image(BKImagePath)

    def release(self):
        del self._name
        del self._m_framework
        del self._m_BKImage

    def update(self, TimeElapsed):
        self._handle_events()

    def draw(self):
        self._m_BKImage.draw(self._m_framework.WINDOW_WIDTH / 2, self._m_framework.WINDOW_HEIGHT / 2)

    def handle_events(self):
        events = get_events()
        for event in events:
            if event.type == SDL_QUIT:
                self._m_framework.quit()





