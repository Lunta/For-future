from pico2d import *
import Logo_Scene
import Title_Scene
import Play_Scene
import GameOver_Scene
import Ranking_Scene


class Framework:
    UPDATE_DELAY = 0.01

    _m_Logo = Logo_Scene.LogoScene()
    _m_Title = Title_Scene.TitleScene()
    _m_Play = Play_Scene.PlayScene()
    _m_Gameover = GameOver_Scene.GameoverScene()
    _m_Ranking = Ranking_Scene.RankingScene()

    _m_CurrentScene = None
    _m_SoundManager = None

    def create(self):
        open_canvas()
        self.build_scene()

    def build_scene(self):
        self._m_Logo.build_object(self)
        self._m_Title.build_object(self)
        self._m_Play.build_object(self)
        self._m_Gameover.build_object(self)
        self._m_Ranking.build_object(self)

        self._m_CurrentScene = self._m_Logo

    def update(self):
        self._m_CurrentScene.update()

    def draw(self):
        clear_canvas()
        self._m_CurrentScene.draw()
        update_canvas()

    def change_scene(self, tag):
        pass

    def run(self):
        self.create()
        while True:
            self.draw()
            self.update()
            delay(self.UPDATE_DELAY)
        self.exit()

    def release_scene(self):
        self._m_Logo.release()
        self._m_Title.release()
        self._m_Play.release()
        self._m_Gameover.release()
        self._m_Ranking.release()

        self._m_CurrentScene = None
        self._m_SoundManager = None

    def exit(self):
        self.release_scene()
        close_canvas()
