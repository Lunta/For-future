from pico2d import *
from Scene import *


class RankingScene(Scene):
    def __init__(self, scene_name='Ranking'):
        Scene.__init__(self, scene_name)

    def build_object(self, framework, image_manager, sound_manager):
        Scene.build_object(self, framework, image_manager, sound_manager)

    def release(self):
        Scene.release(self)

    def update(self, TimeElapsed):
        pass

    def draw(self):
        self._m_BKImage.draw(self._m_framework.WINDOW_WIDTH / 2, self._m_framework.WINDOW_HEIGHT / 2 )

    def handle_events(self):
        events = get_events()
        for event in events:
            if event.type == SDL_QUIT:
                self._m_framework.quit()
            elif event.type == SDL_KEYDOWN and event.key == SDLK_ESCAPE:
                self._m_framework.change_state('Title')
                self._m_SoundManager.BGM_Title.play(-1)
