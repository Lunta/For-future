from Scene import *
from Stage import *


class PlayScene(Scene):
    def __init__(self, scene_name='Play'):
        Scene.__init__(self, scene_name)
        # Set Stage
        self._m_StageName_List = []
        self._m_Stage_List = []
        self._m_CurrentStage = None

        # Set Player
        self._m_Player = None
        self._m_SHAKE_TIME = 0.2
        self._m_pulse_power = 5
        self._m_Shack_pulse = 0.0
        self._m_ShackTimer = 0.0
        self._m_bShake = False
        self.b = None

    def build_object(self, framework, sound_manager, BKImagePath=None):
        Scene.build_object(self, framework, sound_manager)
        self._m_BKImage = load_image('Resource\Graphics\Background\Play.png')
        self._m_Player = Player(self._m_SoundManager, self._m_framework.WINDOW_WIDTH / 2, self._m_framework.WINDOW_HEIGHT / 2)
        self.b = Meteor(self._m_framework.WINDOW_WIDTH, (random.random() * 10000) % self._m_framework.WINDOW_HEIGHT, 50,
                        'Small', self._m_framework.WINDOW_WIDTH, self._m_framework.WINDOW_HEIGHT)
        self._m_Player.targeting(self.b)

    def release(self):
        del self._m_BKImage

    def update(self, TimeElapsed):
        if self._m_Player.crash_check():
            self._m_bShake = True
            self._m_Shack_pulse = 0.0
            self._m_ShackTimer = 0.0

        if self._m_bShake:
            self._m_ShackTimer += TimeElapsed
            self._m_Shack_pulse = self._m_pulse_power * math.sin(self._m_ShackTimer * 100) * math.pow(0.5, self._m_ShackTimer)
            if self._m_ShackTimer > self._m_SHAKE_TIME:
                self._m_Shack_pulse = 0.0
                self._m_ShackTimer = 0.0
                self._m_bShake = False
                print('stop shake')

        self._m_Player.update(TimeElapsed)
        self.b.update(TimeElapsed)
        if self._m_Player.isGameover():
            self._m_framework.change_state('Gameover')
        if self._m_Player.isQuit():
            self._m_framework.quit()

    def draw(self):
        self._m_BKImage.draw(self._m_framework.WINDOW_WIDTH / 2, self._m_framework.WINDOW_HEIGHT / 2 + self._m_Shack_pulse)
        self.b.draw(self._m_Shack_pulse)
        self._m_Player.draw(self._m_Shack_pulse)

    def reset(self):
        pass

    def handle_events(self):
        self._m_Player.handle_events()
