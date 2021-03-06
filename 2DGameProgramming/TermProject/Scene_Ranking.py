from pico2d import *
from Scene import *


class RankingScene(Scene):
    def __init__(self, scene_name='Ranking'):
        Scene.__init__(self, scene_name)
        self.Ranking = []
        self.current_player = 0
        self.input_timer = 0.0
        self.INPUT_TIME = 5
        self.title_scene_bgm_play = False

    def build_object(self, framework, image_manager, sound_manager):
        Scene.build_object(self, framework, image_manager, sound_manager)
        self.OutPut_Font = Font('Resource\Font\HoonMakdaeyunpilR.ttf', 50)

    def release(self):
        Scene.release(self)

    def update(self, TimeElapsed):
        self.input_timer += TimeElapsed
        self.read()

    def draw(self):
        self._m_BKImage.clip_draw(0, 0, self._m_BKImage.w, self._m_BKImage.h,
                                  self._m_framework.WINDOW_WIDTH / 2 , self._m_framework.WINDOW_HEIGHT / 2,
                                  self._m_framework.WINDOW_WIDTH , self._m_framework.WINDOW_HEIGHT)
        i = 0
        self.Ranking = self.Ranking[:5]
        for data in self.Ranking:
            self.OutPut_Font.draw(180, 580 - 100 * i, '%2d - Player %2d   Score: %6d   Time: %3.2f' %
                                  (i + 1, data['Player'], data['Score'], data['Time']), (255, 25, 41))
            if self.current_player is data['Player']:
                self.OutPut_Font.draw(20, 580 - 100 * i, 'YOUR >>', (255, 255, 0))
            i += 1

    def read(self):
        f = open('ranking.txt', 'r')
        self.Ranking = json.load(f)
        f.close()
        i = 0
        for idx in self.Ranking:
            i += 1
        self.current_player = i - 1

    def handle_events(self):
        if self.input_timer < self.INPUT_TIME:
            return None
        events = get_events()
        for event in events:
            if event.type == SDL_QUIT:
                self._m_framework.quit()
            elif event.type == SDL_KEYDOWN:
                self._m_framework.change_scene('Title')
                if not self.title_scene_bgm_play:
                    self._m_SoundManager.BGM_Title.play(-1)
                    self.title_scene_bgm_play = True
