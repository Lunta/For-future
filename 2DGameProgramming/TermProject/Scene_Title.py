from Utility import *
from Scene import *


class TitleScene(Scene):
    def __init__(self, scene_name='Title'):
        Scene.__init__(self, scene_name)
        self._m_ObjImage_Cursor = None
        self._m_Cursor_Radian = 0.0
        self._m_Cursor_Pos_Start = POINT(x=875, y=205)
        self._m_Cursor_Pos_Exit = POINT(x=875, y=105)
        self._m_Start = True

    def get_scene(self):
        return Scene.get_name(self)

    def build_object(self, framework, image_manager, sound_manager):
        Scene.build_object(self, framework, image_manager, sound_manager)
        self._m_ObjImage_Cursor = image_manager.Image_Meteor_Small

    def release(self):
        Scene.release(self)
        del self._m_ObjImage_Cursor

    def update(self, TimeElapsed):
        self._m_Cursor_Radian += TimeElapsed
        if self._m_Cursor_Radian >= math.pi * 2:
            self._m_Cursor_Radian = 0.0

    def draw(self):
        if self._m_Start:
            self._m_BKImage_Start.draw(self._m_framework.WINDOW_WIDTH / 2, self._m_framework.WINDOW_HEIGHT / 2)
            self._m_ObjImage_Cursor.rotate_draw(self._m_Cursor_Radian, self._m_Cursor_Pos_Start.x, self._m_Cursor_Pos_Start.y)
        else:
            self._m_BKImage_Exit.draw(self._m_framework.WINDOW_WIDTH / 2, self._m_framework.WINDOW_HEIGHT / 2)
            self._m_ObjImage_Cursor.rotate_draw(self._m_Cursor_Radian, self._m_Cursor_Pos_Exit.x, self._m_Cursor_Pos_Exit.y)

    def handle_events(self):
        events = get_events()
        for event in events:
            if event.type == SDL_QUIT:
                self._m_framework.quit()
            elif event.type == SDL_KEYDOWN:
                if event.key == SDLK_RETURN:
                    if self._m_Start:
                        self._m_framework.change_scene('Play')
                        self._m_SoundManager.BGM_Title.stop()
                        self._m_SoundManager.BGM_Play.play(-1)
                    else:
                        self._m_framework.quit()
                if event.key == SDLK_UP:
                    self._m_Start = True
                elif event.key == SDLK_DOWN:
                    self._m_Start = False

