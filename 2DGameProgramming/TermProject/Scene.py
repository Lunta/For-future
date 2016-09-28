from pico2d import *


class Scene:
    name = None
    _m_framework = None
    _m_BKImage = None

    def __init__(self, scene_name='Scene'):
        self.name = scene_name

    def build_object(self, framework, BKImagePath='Resource\Graphics\Background\Logo.png'):
        self._m_framework = framework
        self._m_BKImage = load_image(BKImagePath)

    def release(self):
        del self._m_BKImage

    def update(self, TimeElapsed):
        self._handle_events()

    def draw(self):
        self._m_BKImage.draw(self._m_framework.WINDOW_WIDTH / 2, self._m_framework.WINDOW_HEIGHT / 2)

    def change_scene(self, change_to_scene):
        self._m_framework.change_scene(change_to_scene)

    def exit_game(self):
        self._m_framework.quit()

    def _handle_events(self):
        events = get_events()
        for event in events:
            if event.type == SDL_QUIT:
                self._m_framework.quit()





