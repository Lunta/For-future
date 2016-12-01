from pico2d import *
import time
import Scene_Play
import Scene_Logo
import Scene_Ranking
import Scene_Title
import Scene_GameOver
import ImageManager
import SoundManager


class Framework:
    def __init__(self):
        # Canvas Setting
        self.WINDOW_WIDTH = 1200
        self.WINDOW_HEIGHT = 800
        self.CAPTION = 'Meteor Crash'

        self._m_bRun = False

        # Frame Control
        self.MAX_FPS = 1 / 60  # 1 / FPS

        self._m_PrevTime = 0.0
        self._m_CurrentTime = 0.0
        self._m_AccumulatedTime = 0.0

        # Scene
        self._m_CurrentScene = None

        self._m_SceneName_List = []
        self._m_Scene_List = \
            [
               Scene_Logo.LogoScene(),
               Scene_Title.TitleScene(),
               Scene_Play.PlayScene(),
               Scene_GameOver.GameoverScene(),
               Scene_Ranking.RankingScene()
            ]

        # Image
        self._m_ImageManager = None

        # Sound
        self._m_SoundManager = None

    def _create(self):
        open_canvas(self.WINDOW_WIDTH, self.WINDOW_HEIGHT, self.CAPTION)
        self._m_ImageManager = ImageManager.ImageManager()
        self._m_SoundManager = SoundManager.SoundManager()
        self._build_scene()
        self._m_bRun = True

    def _build_scene(self):
        for idx in range(len(self._m_Scene_List)):
            self._m_Scene_List[idx].build_object(self, self._m_ImageManager, self._m_SoundManager)
            self._m_SceneName_List.append(self._m_Scene_List[idx].get_name())

        self._m_CurrentScene = self._m_Scene_List[0]
        self._m_SoundManager.BGM_Logo.play()

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
        del self._m_CurrentScene
        del self._m_SceneName_List
        del self._m_Scene_List
        del self._m_SoundManager
        close_canvas()

    def change_scene(self, scene_name):
        self._m_CurrentScene = self._m_Scene_List[self._m_SceneName_List.index(scene_name)]
        if scene_name is 'Play':
            self._m_CurrentScene.reset()

    def run(self):
        self._create()
        self._m_PrevTime = time.time()
        while self._m_bRun:
            self._m_CurrentTime = time.time()
            self._m_AccumulatedTime += self._m_CurrentTime - self._m_PrevTime
            self._m_PrevTime = self._m_CurrentTime
            if self._m_AccumulatedTime > self.MAX_FPS:
                print_fps(1 / self._m_AccumulatedTime)  # FPS = 1 / ( 1 / 60 )
                self._m_CurrentScene.handle_events()
                self._update(self._m_AccumulatedTime)
                self._draw()
                # self._m_AccumulatedTime -= self.MAX_FPS
                self._m_AccumulatedTime = 0

        self._exit()

    def quit(self):
        self._m_bRun = False



