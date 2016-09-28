from pico2d import *
from Scene import *


class TitleScene(Scene):
    _m_framework = None
    _m_BKImage_Start = None
    _m_BKImage_Exit = None
    _m_Start = True

    def __init__(self, scene_name='Title'):
        Scene.__init__(self, scene_name)

    def build_object(self, framework, BKImagePath=None):
        self._m_framework = framework
        self._m_BKImage_Start = load_image('Resource\Graphics\Background\Title_Start.png')
        self._m_BKImage_Exit = load_image('Resource\Graphics\Background\Title_Exit.png')

    def release(self):
        del self._m_BKImage_Start
        del self._m_BKImage_Exit

    def update(self, TimeElapsed):
        self._handle_events()

    def draw(self):
        if self._m_Start:
            self._m_BKImage_Start.draw(self._m_framework.WINDOW_WIDTH / 2, self._m_framework.WINDOW_HEIGHT / 2)
        else:
            self._m_BKImage_Exit.draw(self._m_framework.WINDOW_WIDTH / 2, self._m_framework.WINDOW_HEIGHT / 2)

    def _handle_events(self):
        events = get_events()
        for event in events:
            if event.type == SDL_QUIT:
                self._m_framework.quit()
            elif event.type == SDL_KEYDOWN:
                if event.key == SDLK_RETURN:
                    if self._m_Start:
                        Scene.change_scene(self, 'Logo')
                    else:
                        Scene.exit_game(self)
                if event.key == SDLK_UP:
                    self._m_Start = True
                elif event.key == SDLK_DOWN:
                    self._m_Start = False

