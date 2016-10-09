from Scene import *
from Stage import *


class PlayScene(Scene):
    name = None
    _m_framework = None
    _m_BKImage = None

    _m_StageName_List = []
    _m_Stage_List = []
    _m_CurrentStage = None
    a = None

    def __init__(self, scene_name='Play'):
        Scene.__init__(self, scene_name)

    def build_object(self, framework, BKImagePath=None):
        Scene.build_object(self, framework)
        self._m_BKImage = load_image('Resource\Graphics\Background\Play.png')
        self.a = Player(self._m_framework.WINDOW_WIDTH / 2, self._m_framework.WINDOW_HEIGHT / 2)

    def release(self):
        del self._m_BKImage

    def update(self, TimeElapsed):
        self.a.update(TimeElapsed)
        if self.a.isGameover():
            self._m_framework.change_state('Gameover')
        if self.a.isQuit():
            self._m_framework.quit()

    def draw(self):
        self._m_BKImage.draw(self._m_framework.WINDOW_WIDTH / 2, self._m_framework.WINDOW_HEIGHT / 2)
        self.a.draw()

    def reset(self):
        pass

    def handle_events(self):
        self.a.handle_events()
