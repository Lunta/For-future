from pico2d import *


class Scene:
    def __init__(self, scene_name='Scene'):
        self._m_name = scene_name
        self._m_framework = None
        self._m_BKImage = None
        self._m_BKImage_Start = None
        self._m_BKImage_Exit = None
        self._m_SoundManager = None
        self._m_ImageManager = None

    def get_name(self):
        return self._m_name

    def build_object(self, framework, image_manager, sound_manager):
        self._m_framework = framework
        self._m_SoundManager = sound_manager
        self._m_ImageManager = image_manager
        if self._m_name is 'Logo':
            self._m_BKImage = image_manager.Image_SceneBK_Logo
        elif self._m_name is 'Title':
            self._m_BKImage_Start = image_manager.Image_SceneBK_Title_Start
            self._m_BKImage_Exit = image_manager.Image_SceneBK_Title_Exit
        elif self._m_name is 'Play':
            self._m_BKImage = image_manager.Image_SceneBK_Play
        elif self._m_name is 'Gameover':
            self._m_BKImage = image_manager.Image_SceneBK_Gameover
        elif self._m_name is 'Ranking':
            self._m_BKImage = image_manager.Image_SceneBK_Ranking

    def release(self):
        del self._m_name
        del self._m_framework
        del self._m_BKImage
        del self._m_BKImage_Start
        del self._m_BKImage_Exit

    def update(self, TimeElapsed):
        pass

    def draw(self):
        self._m_BKImage.draw(self._m_framework.WINDOW_WIDTH / 2, self._m_framework.WINDOW_HEIGHT / 2)

    def handle_events(self):
        events = get_events()
        for event in events:
            if event.type == SDL_QUIT:
                self._m_framework.quit()





