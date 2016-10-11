from pico2d import *


class Scene:
    def __init__(self, scene_name='Scene'):
        self._m_name = scene_name
        self._m_framework = None
        self._m_BKImage = None
        self._m_SoundManager = None

    def get_name(self):
        return self._m_name

    def build_object(self, framework, sound_manager, BKImagePath=False):
        self._m_framework = framework
        self._m_SoundManager = sound_manager
        if BKImagePath:
            self._m_BKImage = load_image(BKImagePath)

    def release(self):
        del self._m_name
        del self._m_framework
        del self._m_BKImage

    def update(self, TimeElapsed):
        pass

    def draw(self):
        self._m_BKImage.draw(self._m_framework.WINDOW_WIDTH / 2, self._m_framework.WINDOW_HEIGHT / 2)

    def handle_events(self):
        events = get_events()
        for event in events:
            if event.type == SDL_QUIT:
                self._m_framework.quit()





