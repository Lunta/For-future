from pico2d import *
import time
import Play_Scene
import Logo_Scene
import Ranking_Scene
import Title_Scene
import GameOver_Scene


class Framework:
    # Canvas Setting
    WINDOW_WIDTH = 1200
    WINDOW_HEIGHT = 800
    CAPTION = 'Block Crash'

    _m_bRun = False

    # Frame Control
    MAX_FPS = 1 / 60  # 1 / FPS

    _m_PrevTime = 0.0
    _m_CurrentTime = 0.0
    _m_AccumulatedTime = 0.0

    # Scene
    _m_CurrentScene = None

    _m_SceneName_List = []
    _m_Scene_List = \
        [
           Logo_Scene.LogoScene(),
           Title_Scene.TitleScene(),
           Play_Scene.PlayScene(),
           GameOver_Scene.GameoverScene(),
           Ranking_Scene.RankingScene()
        ]
    # Sound
    _m_SoundManager = None

    def _create(self):
        open_canvas(self.WINDOW_WIDTH, self.WINDOW_HEIGHT, self.CAPTION)
        self._build_scene()
        self._m_bRun = True

    def _build_scene(self):
        for idx in range(len(self._m_Scene_List)):
            self._m_Scene_List[idx].build_object(self)
            self._m_SceneName_List.append(self._m_Scene_List[idx].get_name())

        self._m_CurrentScene = self._m_Scene_List[0]

    def _update(self, TimeElapsed):
        self._m_CurrentScene.update(TimeElapsed)

    def _draw(self):
        clear_canvas()
        self._m_CurrentScene.draw()
        update_canvas()

    def _release_scene(self):
        for idx in range(len(self._m_Scene_List)):
            self._m_Scene_List[idx].release()

    def _exit(self):
        self._release_scene()
        self._m_CurrentScene = None
        self._m_SoundManager = None
        close_canvas()

    def change_scene(self, scene_name):
        self._m_CurrentScene = self._m_Scene_List[self._m_SceneName_List.index(scene_name)]

    def run(self):
        self._create()
        self._m_PrevTime = time.time()
        while self._m_bRun:
            self._m_CurrentTime = time.time()
            self._m_AccumulatedTime += self._m_CurrentTime - self._m_PrevTime
            self._m_PrevTime = self._m_CurrentTime
            if self._m_AccumulatedTime > self.MAX_FPS:
                print_fps(1 / self._m_AccumulatedTime)  # FPS = 1 / ( 1 / 60 )
                self._update(self._m_AccumulatedTime)
                self._draw()
                self._m_AccumulatedTime = 0

        self._exit()

    def quit(self):
        self._m_bRun = False



