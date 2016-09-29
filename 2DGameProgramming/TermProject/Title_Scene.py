from pico2d import *
from Scene import *


class TitleScene(Scene):
    _m_BKImage_Start = None
    _m_BKImage_Exit = None
    _m_ObjImage_Cursor = None
    _m_Cursor_Radian = 0.0
    _m_Cursor_Pos_Start = 875, 225
    _m_Cursor_Pos_Exit = 875, 125
    _m_Start = True

    def __init__(self, scene_name='Title'):
        Scene.__init__(self, scene_name)

    def get_scene(self):
        return Scene.get_name(self)

    def build_object(self, framework, BKImagePath=None):
        Scene.build_object(self, framework)
        self._m_BKImage_Start = load_image('Resource\Graphics\Background\Title_Start.png')
        self._m_BKImage_Exit = load_image('Resource\Graphics\Background\Title_Exit.png')
        self._m_ObjImage_Cursor = load_image('Resource\Graphics\Object\Stone_Small.png')

    def release(self):
        del self._m_BKImage_Start
        del self._m_BKImage_Exit

    def update(self, TimeElapsed):
        self._handle_events()
        self._m_Cursor_Radian += TimeElapsed

    def draw(self):
        if self._m_Start:
            self._m_BKImage_Start.draw(self._m_framework.WINDOW_WIDTH / 2, self._m_framework.WINDOW_HEIGHT / 2)
        else:
            self._m_BKImage_Exit.draw(self._m_framework.WINDOW_WIDTH / 2, self._m_framework.WINDOW_HEIGHT / 2)
        self._m_ObjImage_Cursor.rotate_draw(self._m_Cursor_Radian, 875, 125)

    def _handle_events(self):
        events = get_events()
        for event in events:
            if event.type == SDL_QUIT:
                Scene.exit(self)
            elif event.type == SDL_KEYDOWN:
                if event.key == SDLK_RETURN:
                    if self._m_Start:
                        self._m_framework.change_scene('Play')
                    else:
                        self._m_framework.quit()
                if event.key == SDLK_UP:
                    self._m_Start = True
                elif event.key == SDLK_DOWN:
                    self._m_Start = False

