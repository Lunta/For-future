from pico2d import *
from Scene import *


class RankingScene(Scene):
    def __init__(self, scene_name='Ranking'):
        Scene.__init__(self, scene_name)
        self.Ranking = []

    def build_object(self, framework, image_manager, sound_manager):
        Scene.build_object(self, framework, image_manager, sound_manager)
        self.OutPut_Font = Font('Resource\Font\HoonMakdaeyunpilR.ttf', 60)

    def release(self):
        Scene.release(self)

    def update(self, TimeElapsed):
        self.read()

    def draw(self):
        self._m_BKImage.clip_draw(0, 0, self._m_BKImage.w, self._m_BKImage.h,
                                  self._m_framework.WINDOW_WIDTH / 2 , self._m_framework.WINDOW_HEIGHT / 2,
                                  self._m_framework.WINDOW_WIDTH , self._m_framework.WINDOW_HEIGHT)
        i = 0
        self.Ranking = self.Ranking[:5]
        for data in self.Ranking:
            self.OutPut_Font.draw(100, 580 - 100 * i, '%2d - Player %2d   Score: %6d   Time: %3.2f' %
                                  (i + 1, data['Player'], data['Score'], data['Time']), (255, 25, 41))
            i += 1
            if i is 10:
                break

    def read(self):
        f = open('ranking.txt', 'r')
        self.Ranking = json.load(f)
        f.close()

    def handle_events(self):
        events = get_events()
        for event in events:
            if event.type == SDL_QUIT:
                self._m_framework.quit()
            elif event.type == SDL_KEYDOWN:
                self._m_framework.change_scene('Title')
                self._m_SoundManager.BGM_Title.play(-1)
